//
// Created by andrew on 6.5.15.
//

#ifndef LOCKFREE_BENCH_OPTIMISTICLOCKLISTSET_H
#define LOCKFREE_BENCH_OPTIMISTICLOCKLISTSET_H

#include <iostream>
#include <assert.h>
#include <atomic>
#include "ListSet.h"

template<typename Item, typename GC, typename Lock>
class OptimisticLockListSet {
private:

    struct ListNode {
        Item data;
        std::atomic<ListNode*> nxt;
        Lock lk;

        ListNode() {
            nxt.store(nullptr);
        }

        void lock() {
            lk.lock();
        }

        void unlock() {
            lk.unlock();
        }
    };

    ListNode *head;
    ListNode *dummyHead, *dummyTail;


    bool validate(ListNode *pred, ListNode *curr) {
        auto v = head;
        setGuard(2, v);

        do {
            if (v == pred) {
                return v->nxt.load(std::memory_order_acquire) == curr;
            }
            v = v->nxt.load(std::memory_order_acquire);
            setGuard(2, v);
        } while (!(v == dummyTail || v->data > pred->data));

        return false;
    }

    std::pair<ListNode*, ListNode*> find(Item x) {
        auto v = head;
        auto u = v->nxt.load(std::memory_order_acquire);
        setGuard(0, v);
        setGuard(1, u);

        while (!(u == dummyTail || u->data >= x)) {
            v = u;
            u = u->nxt.load(std::memory_order_acquire);
            setGuard(0, u);
            setGuard(1, v);
        }

        return std::make_pair(v, u);
    }

    void setGuard(int idx, ListNode *p) {
        GC::getInstance()->getGuards()[idx].store(p, std::memory_order_release);
    }

    void releaseGuards() {
        for (int i = 0; i < 3; i++) {
            setGuard(0, nullptr);
        }
    }

public:

    OptimisticLockListSet() {
        head = new ListNode();
        head->nxt = new ListNode();
        dummyHead = head, dummyTail = head->nxt;
    }

    ~OptimisticLockListSet() {
        auto v = head;
        while (v) {
            auto nxt = v->nxt.load(std::memory_order_acquire);
            delete v;
            v = nxt;
        }
    }

    bool add(Item x) {

        while (true) {

            ListNode *v, *u;
            auto p = find(x);
            v = p.first;
            u = p.second;

            v->lock();
            u->lock();

            if (validate(v, u)) {
                bool res = false;

                if (u != dummyTail && u->data == x) {
                    res = false;
                } else {
                    ListNode *newNode = new ListNode();
                    newNode->data = x;
                    newNode->nxt.store(u, std::memory_order_release);
                    v->nxt.store(newNode, std::memory_order_release);
                    res = true;
                }

                u->unlock();
                v->unlock();

                releaseGuards();

                return res;
            }

            u->unlock();
            v->unlock();
        }
    }

    bool remove(Item x) {

        while (true) {
            ListNode *v, *u;
            auto p = find(x);
            v = p.first;
            u = p.second;


            v->lock();
            u->lock();

            if (validate(v, u)) {
                bool res = false;

                if (u != dummyTail && u->data == x) {
                    v->nxt.store(u->nxt.load(std::memory_order_acquire), std::memory_order_release);

                    u->unlock();
                    v->unlock();

                    GC::getInstance()->retirePtr(u, [](void *p) { delete (ListNode*)p; });

                    releaseGuards();

                    return true;
                } else {
                    u->unlock();
                    v->unlock();

                    releaseGuards();

                    return false;
                }
            }

            u->unlock();
            v->unlock();
        }
    }

    bool contains(Item x) {

        while (true) {
            ListNode *v, *u;
            auto p = find(x);
            v = p.first;
            u = p.second;


            v->lock();
            u->lock();

            if (validate(v, u)) {
                u->unlock();
                v->unlock();

                if (u != dummyTail && u->data == x) {
                    releaseGuards();
                    return true;
                } else {
                    releaseGuards();
                    return false;
                }
            }

            u->unlock();
            v->unlock();
        }
    }
};


#endif //LOCKFREE_BENCH_OPTIMISTICLOCKLISTSET_H
