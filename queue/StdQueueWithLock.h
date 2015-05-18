//
// Created by andrew on 11.5.15.
//

#ifndef LOCKFREE_BENCH_STDQUEUEWITHLOCK_H
#define LOCKFREE_BENCH_STDQUEUEWITHLOCK_H

#include <queue>
#include "Queue.h"

template<typename Item, typename Lock>
class StdQueueWithLock {
private:
    std::queue<Item> q;
    Lock lk;
public:

    virtual void push(Item x) {
        lk.lock();
        q.push(x);
        lk.unlock();
    }

    virtual bool pop(Item &res) {
        bool s;
        lk.lock();
        s = !q.empty();
        if (s) {
            res = q.front();
            q.pop();
        }
        lk.unlock();
        return s;
    }
};


#endif //LOCKFREE_BENCH_STDQUEUEWITHLOCK_H
