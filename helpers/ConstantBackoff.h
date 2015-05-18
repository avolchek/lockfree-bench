//
// Created by andrew on 5.5.15.
//

#ifndef LOCKFREE_BENCH_BACKOFF_H
#define LOCKFREE_BENCH_BACKOFF_H


#include <unistd.h>
#include <algorithm>
#include <thread>

class ConstantBackoff {
    int duration;
public:
    ConstantBackoff() {
        duration = 25;
    }

    void backoff();
};


#endif //LOCKFREE_BENCH_BACKOFF_H
