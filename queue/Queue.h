//
// Created by andrew on 11.5.15.
//

#ifndef LOCKFREE_BENCH_QUEUE_H
#define LOCKFREE_BENCH_QUEUE_H

template<typename Item, typename GC>
class Queue {
public:
    typedef Item ItemType;

    virtual void push(Item x) = 0;
    virtual bool pop(Item &res) = 0;
};


#endif //LOCKFREE_BENCH_QUEUE_H
