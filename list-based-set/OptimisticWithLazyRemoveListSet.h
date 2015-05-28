//
// Created by andrew on 6.5.15.
//

#ifndef LOCKFREE_BENCH_OPTIMISTICWITHLAZYREMOVELISTSET_H
#define LOCKFREE_BENCH_OPTIMISTICWITHLAZYREMOVELISTSET_H

#include <atomic>
#include "ListSet.h"




template<typename Item, typename Lock>
class OptimisticWithLazyRemoveListSet {
private:

    struct ListNode {
        Item data;
        ListNode *nxt;
        Lock lk;
        std::atomic<bool> mark;

        ListNode() {
            nxt = nullptr;
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

    bool verify(ListNode *pred, ListNode *curr) {
        return !pred->mark.load(std::memory_order_acquire) &&
                !curr->mark.load(std::memory_order_acquire)
               && pred->nxt == curr;
    }

public:

    OptimisticWithLazyRemoveListSet() {
        head = new ListNode;
        head->nxt = new ListNode;
        dummyHead = head;
        dummyTail = head->nxt;
    }

    ~OptimisticWithLazyRemoveListSet() {
        auto v = head;
        while (v) {
            auto nxt = v->nxt;
            delete v;
            v = nxt;
        }
    }

    bool add(Item x) {

        while (true) {
            auto v = head;
            auto u = v->nxt;

            while (!(u == dummyTail || u->data >= x)) {
                v = u;
                u = u->nxt;
            }

            v->lock();
            u->lock();

            if (verify(v, u)) {
                if (u != dummyTail && u->data == x) {
                    u->unlock();
                    v->unlock();

                    return false;
                }

                ListNode *newNode = new ListNode();
                newNode->data = x;
                newNode->nxt = u;
                v->nxt = newNode;

                u->unlock();
                v->unlock();

                return true;
            }

            u->unlock();
            v->unlock();
        }
    }

    bool remove(Item x) {

        while (true) {
            auto v = head;
            auto u = v->nxt;

            while (!(u == dummyTail || u->data >= x)) {
                v = u;
                u = u->nxt;
            }

            v->lock();
            u->lock();

            if (verify(v, u)) {
                if (u != dummyTail && u->data == x) {
                    u->mark.store(true, std::memory_order_release);
                    v->nxt = u->nxt;

                    u->unlock();
                    v->unlock();

                    delete u;
                    //GC::getInstance()->retirePtr(u);

                    return true;
                } else {
                    return false;
                }
            }

            u->unlock();
            v->unlock();
        }
    }

    bool contains(Item x) {
        ListNode *v = head->nxt;

        while (!(v == dummyTail || v->data < x)) {
            v = v->nxt;
        }

        return v != dummyTail && v->data == x && !v->mark.load(std::memory_order_acquire);
    }
};


#endif //LOCKFREE_BENCH_OPTIMISTICWITHLAZYREMOVELISTSET_H
