//
// Created by andrew on 6.5.15.
//

#ifndef LOCKFREE_BENCH_FINEGRAINEDLOCKLISTSET_H
#define LOCKFREE_BENCH_FINEGRAINEDLOCKLISTSET_H

#include "ListSet.h"

template<typename Item, typename Lock>
class FineGrainedLockListSet {
private:

    struct ListNode {
        Item data;
        ListNode *nxt;
        Lock lk;

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

public:

    FineGrainedLockListSet() {
        head = new ListNode;
        head->nxt = new ListNode;
        dummyHead = head, dummyTail = head->nxt;
    }

    ~FineGrainedLockListSet() {
        ListNode *v = head;
        while (v) {
            auto nxt = v->nxt;
            delete v;
            v = nxt;
        }
    }

    bool add(Item x) {
        auto v = head;
        v->lock();
        auto u = v->nxt;
        u->lock();

        while (true) {
            if ((v == dummyHead || v->data < x) && (u == dummyTail || x <= u->data)) {
                if (u != dummyTail && u->data == x) {
                    u->unlock();
                    v->unlock();
                    return false;
                }

                ListNode *newNode = new ListNode();
                newNode->nxt = u;
                newNode->data = x;

                v->nxt = newNode;

                u->unlock();
                v->unlock();

                return true;
            }

            v->unlock();
            v = u;
            u = u->nxt;
            u->lock();
        }
    }


    bool remove(Item x) {
        auto v = head;
        v->lock();
        auto u = v->nxt;
        u->lock();

        while (true) {
            if ((v == dummyHead || v->data < x) && (u == dummyTail || x <= u->data)) {
                if (u != dummyTail && u->data == x) {
                    v->nxt = u->nxt;
                    u->unlock();
                    v->unlock();

                    delete u;

                    return true;
                }

                u->unlock();
                v->unlock();

                return true;
            }

            v->unlock();
            v = u;
            u = u->nxt;
            u->lock();
        }
    }

    bool contains(Item x) {
        auto v = head;
        v->lock();
        auto u = v->nxt;
        u->lock();

        while (true) {
            if ((v == dummyHead || v->data < x) && (u == dummyTail || x <= u->data)) {
                u->unlock();
                v->unlock();
                if (u != dummyTail && u->data == x) {
                    return true;
                } else {
                    return false;
                }
            }

            v->unlock();
            v = u;
            u = u->nxt;
            u->lock();
        }
    }
};


#endif //LOCKFREE_BENCH_FINEGRAINEDLOCKLISTSET_H
