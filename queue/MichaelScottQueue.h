//
// Created by andrew on 11.5.15.
//

#ifndef LOCKFREE_BENCH_LOCKFREEQUEUE_H
#define LOCKFREE_BENCH_LOCKFREEQUEUE_H

#include <atomic>
#include <iostream>
#include <assert.h>
#include "Queue.h"
#include "../helpers/NoBackoff.h"

template<typename Item, typename GC, typename Backoff = NoBackoff>
class MichaelScottQueue {
private:

    struct ListNode {
        std::atomic<ListNode*> nxt;
        Item data;

        ListNode() {
            nxt.store(nullptr, std::memory_order_release);
        }
    };

    std::atomic<ListNode*> head, tail;

    void setGuard(int idx, ListNode *v) {
        GC::getInstance()->getGuards()[idx].store(v, std::memory_order_release);
    }

    void releaseGuards() {
        for (int i = 0; i < 2; i++) {
            setGuard(i, nullptr);
        }
    }

public:

    MichaelScottQueue() {
        assert(std::atomic<ListNode*>().is_lock_free());
        tail = head = new ListNode();
    }

    ~MichaelScottQueue() {
        ListNode *v = head.load(std::memory_order_acquire);
        while (v) {
            auto nxt = v->nxt.load(std::memory_order_acquire);
            delete v;
            v = nxt;
        }
    }

    void push(Item x) {
        ListNode *newNode = (ListNode*)GC::getInstance()->tryGetFreePtr();
        if (!newNode) {
            newNode = new ListNode();
        } else {
            newNode = new(newNode) ListNode();
        }
        newNode->data = x;

        Backoff bkf;

        while (true) {
            auto lst = tail.load(std::memory_order_acquire);
            setGuard(0, lst);

            auto nxt = lst->nxt.load(std::memory_order_relaxed);

            do {
                nxt = lst->nxt.load(std::memory_order_relaxed);
                setGuard(1, nxt);
            } while (nxt != lst->nxt.load(std::memory_order_acquire));

            if (lst == tail.load(std::memory_order_acquire)) {
                if (nxt == nullptr) {
                    if (lst->nxt.compare_exchange_weak(nxt, newNode, std::memory_order_release, std::memory_order_relaxed)) {
                        tail.compare_exchange_strong(lst, newNode, std::memory_order_release, std::memory_order_relaxed);
                        releaseGuards();
                        return;
                    }
                } else {
                    tail.compare_exchange_strong(lst, nxt, std::memory_order_release, std::memory_order_relaxed);
                    //bkf.backoff();
                }
            }

            bkf.backoff();
        }
    }

    bool pop(Item &res) {
        Backoff bkf;
        while (true) {
            auto lst = tail.load(std::memory_order_acquire);
            setGuard(0, lst);
            auto fst = head.load(std::memory_order_acquire);
            auto nxt = fst->nxt.load(std::memory_order_relaxed);

            do {
                nxt = fst->nxt.load(std::memory_order_relaxed);
                setGuard(1, nxt);
            } while (nxt != fst->nxt.load(std::memory_order_acquire));

            if (fst == head.load(std::memory_order_acquire)) {
                if (fst == lst) {
                    if (nxt == nullptr) {
                        releaseGuards();
                        return false;
                    } else {
                        tail.compare_exchange_strong(lst, nxt, std::memory_order_release, std::memory_order_relaxed);
                        //bkf.backoff();
                    }
                } else {
                    if (nxt == nullptr) {
                        std::cerr << "nxt is null" << std::endl;
                        continue;
                    }

                    res = nxt->data;
                    if (head.compare_exchange_weak(fst, nxt, std::memory_order_release, std::memory_order_relaxed)) {
                        GC::getInstance()->retirePtr(fst, [](void *p) { delete (ListNode*)p; });
                        releaseGuards();
                    }

                    return true;
                }
            }

            bkf.backoff();
        }
    }
};


#endif //LOCKFREE_BENCH_LOCKFREEQUEUE_H
