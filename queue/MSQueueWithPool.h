//
// Created by andrew on 12.5.15.
//

#ifndef LOCKFREE_BENCH_MSQUEUEWITHPOOL_H
#define LOCKFREE_BENCH_MSQUEUEWITHPOOL_H


#include <atomic>
#include <boost/lockfree/detail/tagged_ptr.hpp>
#include <iostream>
#include <assert.h>
#include "../helpers/ConstantBackoff.h"
#include "../helpers/TaggedPtr.h"
#include "../helpers/NoBackoff.h"

template<typename Item, typename GC, typename Backoff = NoBackoff>
class MSQueueWithPool {

    struct ListNode;

    typedef TaggedPtr<ListNode> TNodePtr;

    struct ListNode {
        std::atomic<TNodePtr> nxt;
        Item data;

        ListNode() {
            nxt.store(TNodePtr(nullptr), std::memory_order_release);
        }
    };

    std::atomic<TNodePtr> head, tail;
    std::atomic<TNodePtr> poolHead;

    TNodePtr getNewNode() {
        Backoff bkf;

        while (true) {
            TNodePtr v = poolHead.load(std::memory_order_acquire);

            if (v) {
                TNodePtr nxt = v->nxt.load(std::memory_order_acquire);

                if (poolHead.compare_exchange_strong(v, nxt, std::memory_order_release, std::memory_order_relaxed)) {
                    return TNodePtr(v.getPtr(), v.getNextTag());
                }
            } else {
                return TNodePtr(new ListNode());
            }

            bkf.backoff();
        }
    }

    void retireNode(TNodePtr p) {
        Backoff bkf;
        while (true) {
            TNodePtr v = poolHead.load(std::memory_order_acquire);
            p->nxt.store(v, std::memory_order_release);

            if (poolHead.compare_exchange_strong(v, p, std::memory_order_release, std::memory_order_relaxed)) {
                break;
            }

            bkf.backoff();
            //usleep(100);
        }
    }

public:

    MSQueueWithPool() {
        assert(std::atomic<TNodePtr>().is_lock_free());
        ListNode *v = new ListNode();
        tail = head = TNodePtr(v);
        poolHead.store(TNodePtr(nullptr), std::memory_order_release);
    }

    ~MSQueueWithPool() {
        auto v = head.load(std::memory_order_acquire);
        while (v) {
            auto nxt = v->nxt.load(std::memory_order_acquire);
            delete v.getPtr();
            v = nxt;
        }

        v = poolHead.load(std::memory_order_acquire);
        while (v) {
            auto nxt = v->nxt.load(std::memory_order_acquire);
            delete v.getPtr();
            v = nxt;
        }
    }

    void push(Item x) {
        TNodePtr newNode = getNewNode();
        newNode->data = x;
        newNode->nxt.store(TNodePtr(nullptr), std::memory_order_release);

        Backoff bkf;

        while (true) {

            auto lst = tail.load(std::memory_order_acquire);
            auto nxt = lst->nxt.load(std::memory_order_relaxed);

            if (lst == tail.load(std::memory_order_acquire)) {
                if (nxt.getPtr() == nullptr) {
                    if (lst->nxt.compare_exchange_strong(nxt, newNode, std::memory_order_release, std::memory_order_relaxed)) {
                        tail.compare_exchange_weak(lst, newNode, std::memory_order_release, std::memory_order_relaxed);
                        return;
                    }
                } else {
                    tail.compare_exchange_weak(lst, nxt, std::memory_order_release, std::memory_order_relaxed);
                }
            }

            bkf.backoff();
        }
    }

    bool pop(Item &res) {
        Backoff bkf;
        while (true) {
            auto lst = tail.load(std::memory_order_acquire);
            auto fst = head.load(std::memory_order_acquire);
            auto nxt = fst->nxt.load(std::memory_order_relaxed);

            if (fst == head.load(std::memory_order_acquire)) {
                if (fst == lst) {
                    if (nxt.getPtr() == nullptr) {
                        return false;
                    } else {
                        tail.compare_exchange_weak(lst, nxt, std::memory_order_release, std::memory_order_relaxed);
                    }
                } else {
                    if (nxt.getPtr() == nullptr) {
                        continue;
                    }

                    res = nxt->data;
                    if (head.compare_exchange_strong(fst, nxt, std::memory_order_release, std::memory_order_relaxed)) {
                        retireNode(fst);
                        return true;
                    }
                }
            }

            bkf.backoff();
        }
    }
};


#endif //LOCKFREE_BENCH_MSQUEUEWITHPOOL_H
