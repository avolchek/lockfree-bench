//
// Created by andrew on 6.5.15.
//

#ifndef LOCKFREE_BENCH_LOCKFREELISTSET_H
#define LOCKFREE_BENCH_LOCKFREELISTSET_H

#include <atomic>
#include <iostream>
#include <assert.h>
#include <sstream>
#include "ListSet.h"
#include "../helpers/ConstantBackoff.h"
#include "../helpers/NoBackoff.h"

template<typename Item, typename GC, typename Backoff = ConstantBackoff<>>
class LockFreeListSet {
private:

    struct ListNode {
        Item data;
        std::atomic<ListNode*> nxt;
        ListNode() {
            nxt = nullptr;
        }
    };

    ListNode* getPointer(ListNode* x) {
        return (ListNode*)((long(x) >> 1) << 1);
    }

    bool getMark(ListNode *x) {
        return bool((long)x & 1);
    }

    ListNode *head;
    ListNode *dummyHead, *dummyTail;

    void setGuard(int idx, void* ptr) {
        GC::getInstance()->getGuards()[idx].store(ptr, std::memory_order_release);
    }

    void retireNode(ListNode *ptr) {
        GC::getInstance()->retirePtr(ptr, [](void *v) { delete (ListNode*)v; });
    }

    // TODO optimize me
    std::pair<ListNode*, ListNode* > find(Item x) {
        int iter = 0;
        Backoff bkf;
        while (true) {
            retry:
            ListNode *prev = head;
            setGuard(4, prev);

            ListNode *curr;

            do {
                curr = getPointer(prev->nxt.load(std::memory_order_relaxed));
                setGuard(5, curr);
            } while (curr != getPointer(prev->nxt.load(std::memory_order_acquire)));


            while (true) {

                ListNode *next = curr->nxt.load(std::memory_order_relaxed);
                setGuard(6, getPointer(next));

                if (next != curr->nxt.load(std::memory_order_acquire)) {
                    bkf.backoff();
                    goto retry;
                }

                if (curr != getPointer(prev->nxt.load(std::memory_order_acquire))) {
                    bkf.backoff();
                    goto retry;
                }


                if (getMark(next)) {

                    if (prev->nxt.compare_exchange_strong(curr,
                                                          getPointer(next),
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
                    setGuard(4, prev);
                }


                curr = getPointer(next);
                setGuard(5, curr);
            }
        }
    }

public:

    LockFreeListSet() {
        head = new ListNode;
        ListNode *tail = new ListNode;
        head->nxt.store(tail, std::memory_order_release);
        dummyHead = head, dummyTail = tail;
    }

    ~LockFreeListSet() {
        auto v = head;
        while (v) {
            auto nxt = getPointer(v->nxt.load(std::memory_order_acquire));
            delete v;
            v = nxt;
        }
    }

    bool add(Item x) {
        ListNode *newNode = new ListNode;
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
                delete newNode;
            } else {
                newNode->nxt.store(pos.second, std::memory_order_release);

                if (pos.first->nxt.compare_exchange_strong(pos.second, newNode,
                                                           std::memory_order_release)) {
                    res = true;
                    done = true;
                }

            }

            if (done) {
                setGuard(4, nullptr);
                setGuard(5, nullptr);
                setGuard(6, nullptr);
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

                auto mNxt = (ListNode*)((long)pNxt | 1);

                auto cp = getPointer(pNxt);
                if (!pos.second->nxt.compare_exchange_strong(cp,
                                                             mNxt,
                                                             std::memory_order_release)) {
                    bkf.backoff();
                    continue;
                }


                if (pos.first->nxt.compare_exchange_weak(pos.second,
                                                           getPointer(pNxt), std::memory_order_release)) {
                    retireNode(pos.second);
                }

                res = true;
                done = true;
            } else {
                done = true;
                res = false;
            }

            if (done) {
                setGuard(4, nullptr);
                setGuard(5, nullptr);
                setGuard(6, nullptr);
                return res;
            }

            bkf.backoff();
        }
    }

    bool contains(Item x) {

        auto pos = find(x);
        bool res = pos.second != dummyTail &&
                   !getMark(pos.second->nxt.load(std::memory_order_acquire)) &&
                   pos.second->data == x;
        setGuard(4, nullptr);
        setGuard(5, nullptr);
        setGuard(6, nullptr);
        return res;
    }
};


#endif //LOCKFREE_BENCH_LOCKFREELISTSET_H
