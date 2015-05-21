//
// Created by andrew on 5.5.15.
//

#ifndef LOCKFREE_BENCH_BACKOFF_H
#define LOCKFREE_BENCH_BACKOFF_H


#include <unistd.h>
#include <algorithm>
#include <thread>

template<int duration = 250>
class ConstantBackoff {

public:


    void backoff() {
        usleep(duration);
    }
};


#endif //LOCKFREE_BENCH_BACKOFF_H
