//
// Created by andrew on 11.5.15.
//

#ifndef LOCKFREE_BENCH_BOOSTLOCKFREEQUEUEWRAPPER_H
#define LOCKFREE_BENCH_BOOSTLOCKFREEQUEUEWRAPPER_H


#include <boost/lockfree/queue.hpp>
#include "Queue.h"

template<typename Item>
class BoostLockfreeQueueWrapper {
private:
    boost::lockfree::queue<Item> q;
public:
    BoostLockfreeQueueWrapper()
        :q(0) {

    }

    virtual void push(Item x) {
        q.push(x);
    }

    virtual bool pop(Item &x) {
        return q.pop(x);
    }

};


#endif //LOCKFREE_BENCH_BOOSTLOCKFREEQUEUEWRAPPER_H
