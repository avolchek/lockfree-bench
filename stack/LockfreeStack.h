//
// Created by andrew on 5.5.15.
//

#ifndef LOCKFREE_BENCH_LOCKFREESTACK_H
#define LOCKFREE_BENCH_LOCKFREESTACK_H

#include <atomic>
#include "Stack.h"
#include "../helpers/ConstantBackoff.h"

template < typename T, typename GC >
class LockfreeStack {
private:
    struct StackNode {
        StackNode *nxt;
        T data;
    };

    std::atomic<StackNode*> head;
public:

    LockfreeStack() {
        head.store(nullptr, std::memory_order_release);
    }

    ~LockfreeStack() {
        StackNode *v = head.load(std::memory_order_acquire);
        while (v) {
            auto nxt = v->nxt;
            GC::getInstance()->retirePtr(v, [](void *p) { delete (StackNode*)p; });
            v = nxt;
        }
    }

    void push(T x) {
        StackNode *newNode = (StackNode*)GC::getInstance()->tryGetFreePtr();
        if (!newNode) {
            newNode = new StackNode();
        }
        newNode->data = x;

        ConstantBackoff bkf;

        while (true) {
            StackNode *cHead;

            do {
                cHead = head.load(std::memory_order_relaxed);
                GC::getInstance()->getGuards()[0].store(cHead, std::memory_order_release);
            } while (cHead != head.load(std::memory_order_acquire));

            newNode->nxt = cHead;

            if (head.compare_exchange_strong(cHead, newNode, std::memory_order_acquire))
                break;

            bkf.backoff();
        }

        GC::getInstance()->getGuards()[0].store(nullptr, std::memory_order_release);
    }

    bool pop(T &res) {
        ConstantBackoff bfk;

        while (true) {
            StackNode *cHead;

            do {
                cHead = head.load(std::memory_order_relaxed);
                GC::getInstance()->getGuards()[0].store(cHead, std::memory_order_release);
            } while (cHead != head.load(std::memory_order_acquire));

            if (!cHead) {
                return false;
            }

            if (head.compare_exchange_strong(cHead, cHead->nxt, std::memory_order_acquire)) {
                res = cHead->data;
                GC::getInstance()->getGuards()[0].store(nullptr, std::memory_order_relaxed);
                GC::getInstance()->retirePtr(cHead, [](void *v) { delete (StackNode*)v; });
                return true;
            }

            bfk.backoff();
        }
    }

};


#endif //LOCKFREE_BENCH_LOCKFREESTACK_H
