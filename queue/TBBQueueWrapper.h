//
// Created by andrew on 5/21/15.
//

#ifndef LOCKFREE_BENCH_TBBQUEUEWRAPPER_H
#define LOCKFREE_BENCH_TBBQUEUEWRAPPER_H

#include <tbb/concurrent_queue.h>
#include <tbb/scalable_allocator.h>

template<typename Item, typename Allocator=tbb::scalable_allocator<Item>>
class TBBQueueWrapper {
private:
    tbb::concurrent_queue<Item, Allocator> q;

public:

    void push(Item x) {
        q.push(x);
    }

    bool pop(Item &res) {
        return q.try_pop(res);
    }
};


#endif //LOCKFREE_BENCH_TBBQUEUEWRAPPER_H
