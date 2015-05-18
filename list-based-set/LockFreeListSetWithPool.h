//
// Created by andrew on 12.5.15.
//

#ifndef LOCKFREE_BENCH_LOCKFREELISTSETWITHPOOL_H
#define LOCKFREE_BENCH_LOCKFREELISTSETWITHPOOL_H

#include <atomic>
#include <algorithm>
#include <boost/lockfree/detail/tagged_ptr.hpp>
#include "../helpers/TaggedPtr.h"
#include "../helpers/ConstantBackoff.h"
#include "../helpers/NoBackoff.h"

template<typename Item, typename GC, typename Backoff = NoBackoff>
class LockFreeListSetWithPool {
    struct ListNode;

    typedef TaggedPtr<ListNode> TNodePtr;

    struct ListNode {
        Item data;
        std::atomic<TNodePtr> nxt;
        ListNode() {
            nxt.store(TNodePtr(nullptr), std::memory_order_release);
        }
    };

    TNodePtr head;
    TNodePtr dummyHead, dummyTail;

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
        }
    }


    // TODO optimize me
    std::pair<TNodePtr, TNodePtr> find(Item x) {

        Backoff bkf;
        while (true) {
            retry:
            TNodePtr prev = head;

            TNodePtr curr = prev->nxt.load(std::memory_order_acquire);

            while (true) {

                TNodePtr next = curr->nxt.load(std::memory_order_relaxed);

                if (next != curr->nxt.load(std::memory_order_acquire)) {
                    bkf.backoff();
                    goto retry;
                }

                if (curr != prev->nxt.load(std::memory_order_acquire)) {
                    bkf.backoff();
                    goto retry;
                }


                if (next.getMark()) {
                    TNodePtr nNext = next;
                    nNext.setMark(false);
                    if (prev->nxt.compare_exchange_strong(curr,
                                                          nNext,
                                                          std::memory_order_acq_rel)) {
                        retireNode(curr);
                    } else {
                        bkf.backoff();
                        goto retry;
                    }
                } else {
                    if (curr == dummyTail || curr->data >= x) {
                        return std::make_pair(prev, curr);
                    }

                    prev = curr;
                }


                curr = next;
            }
        }
    }

public:

    LockFreeListSetWithPool()
        :head(nullptr), dummyHead(nullptr), dummyTail(nullptr) {
        poolHead.store(TNodePtr(nullptr));
        head.setPtr(new ListNode);
        TNodePtr tail(new ListNode);
        head->nxt.store(tail, std::memory_order_release);
        dummyHead = head, dummyTail = tail;
    }

    ~LockFreeListSetWithPool() {
        auto v = head;
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

    bool add(Item x) {
        TNodePtr newNode = getNewNode();
        newNode->data = x;

        int iter = 0;

        Backoff bkf;

        while (true) {
            auto pos = find(x);

            bool res = false;
            bool done = false;

            if (pos.second != dummyTail && pos.second->data == x) {
                res = false;
                done = true;
                retireNode(newNode);
            } else {
                newNode->nxt.store(pos.second, std::memory_order_release);

                if (pos.first->nxt.compare_exchange_strong(pos.second, newNode,
                                                           std::memory_order_release)) {
                    res = true;
                    done = true;
                }

            }

            if (done) {
                return res;
            }

            bkf.backoff();
        }
    }


    bool remove(Item x) {
        int iter = 0;

        Backoff bkf;
        while (true) {
            auto pos = find(x);

            bool res = false;
            bool done = false;

            if (pos.second != dummyTail && pos.second->data == x) {
                auto pNxt = pos.second->nxt.load(std::memory_order_relaxed);

                auto mNxt = pNxt;
                mNxt.setMark(true);

                auto cp = pNxt;
                cp.setMark(false);
                if (!pos.second->nxt.compare_exchange_strong(cp,
                                                             mNxt,
                                                             std::memory_order_release)) {
                    bkf.backoff();
                    continue;
                }

                pNxt.setMark(false);
                if (pos.first->nxt.compare_exchange_weak(pos.second,
                                                           pNxt, std::memory_order_release)) {
                    retireNode(pos.second);
                }

                res = true;
                done = true;
            } else {
                done = true;
                res = false;
            }

            if (done) {
                return res;
            }

            bkf.backoff();
        }
    }

    bool contains(Item x) {

        auto pos = find(x);
        bool res = pos.second != dummyTail &&
                   !pos.second->nxt.load(std::memory_order_acquire).getMark() &&
                   pos.second->data == x;
        return res;
    }
};


#endif //LOCKFREE_BENCH_LOCKFREELISTSETWITHPOOL_H
