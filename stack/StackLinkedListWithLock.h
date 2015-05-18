//
// Created by andrew on 5.5.15.
//

#ifndef LOCKFREE_BENCH_STACKWITHLOCK_H
#define LOCKFREE_BENCH_STACKWITHLOCK_H


#include <mutex>
#include "Stack.h"

template <typename T, typename Lock >
class StackLinkedListWithLock {
private:
    struct StackNode {
        T data;
        StackNode *nxt;
    };

    Lock lock;
    StackNode *head = nullptr;

    std::vector<StackNode*> pool;

    StackNode* allocNode() {
        if (pool.empty()) {
            for (int i = 0; i < 2000; i++) {
                pool.push_back(new StackNode());
            }
        }

        auto res = pool.back();
        pool.pop_back();
        return res;
    }

public:

    ~StackLinkedListWithLock() {
        for (auto x : pool)
            delete x;
    }

    void push(T x) {
        lock.lock();
        StackNode *v = allocNode();
        v->data = x;
        v->nxt = head;
        head = v;
        lock.unlock();
    }

    bool pop(T &res) {
        bool r;

        lock.lock();
        if (head) {
            res = head->data;
            auto t = head;
            head = head->nxt;
            delete t;
            r = true;
        } else {
            r = false;
        }
        lock.unlock();

        return r;
    }
};


#endif //LOCKFREE_BENCH_STACKWITHLOCK_H
