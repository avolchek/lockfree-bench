//
// Created by andrew on 5.5.15.
//

#ifndef LOCKFREE_BENCH_COARSELOCKLISTSET_H
#define LOCKFREE_BENCH_COARSELOCKLISTSET_H

#include <limits>
#include <mutex>
#include "ListSet.h"

template<typename Item, typename Lock>
class CoarseLockListSet  {
private:
    typedef long long Key;
    struct ListNode {
        ListNode *nxt;
        Item data;

        ListNode() {
            nxt = nullptr;
        }
    };

    ListNode *head;
    Lock lock;

    ListNode *dummyHead, *dummyTail;

public:

    typedef Item ItemType;

    CoarseLockListSet() {
        head = new ListNode();
        head->nxt = new ListNode();

        dummyHead = head;
        dummyTail = head->nxt;
    }

    ~CoarseLockListSet() {
        auto v = head;
        while (v) {
            auto nxt = v->nxt;
            delete v;
            v = nxt;
        }
    }

    bool add(Item x) {
        std::lock_guard<Lock> grd(lock);

        auto v = head, u = head->nxt;

        while (true) {
            if ((v == dummyHead || v->data < x) && (u == dummyTail || x <= u->data)) {
                if (u != dummyTail && u->data == x) {
                    return false;
                }

                ListNode *newNode = new ListNode();
                newNode->nxt = u;
                newNode->data = x;

                v->nxt = newNode;

                return true;
            }

            v = v->nxt;
            u = u->nxt;
        }
    }

    bool contains(Item x) {
        std::lock_guard<Lock> grd(lock);

        auto v = head, u = head->nxt;

        while (true) {
            if ((v == dummyHead || v->data < x) && (u == dummyTail || x <= u->data)) {
                if (u != dummyTail && u->data == x) {
                    return true;
                } else {
                    return false;
                }
            }

            v = v->nxt;
            u = u->nxt;
        }
    }

    bool remove(Item x) {
        std::lock_guard<Lock> grd(lock);

        auto v = head, u = head->nxt;

        while (true) {
            if ((v == dummyHead || v->data < x) && (u == dummyTail || x <= u->data)) {
                if (u != dummyTail && u->data == x) {
                    v->nxt = u->nxt;
                    //GC::getInstance()->retirePtr(u, [](void *p) { delete (ListNode*)p; });
                    delete u;
                    return true;
                } else {
                    return false;
                }
            }

            v = v->nxt;
            u = u->nxt;
        }
    }

};


#endif //LOCKFREE_BENCH_COARSELOCKLISTSET_H
