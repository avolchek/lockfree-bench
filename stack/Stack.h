//
// Created by andrew on 5.5.15.
//

#ifndef LOCKFREE_BENCH_STACK_H
#define LOCKFREE_BENCH_STACK_H

#include "../hp/HP.h"

template < typename T, typename GC >
class Stack {
public:
    virtual void push(T x) = 0;
    virtual bool pop(T &res) = 0;

    typedef T ItemType;
};


#endif //LOCKFREE_BENCH_STACK_H
