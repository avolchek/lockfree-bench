//
// Created by andrew on 18.5.15.
//

#ifndef LOCKFREE_BENCH_EXPONENTIALBACKOFF_H
#define LOCKFREE_BENCH_EXPONENTIALBACKOFF_H


#include <unistd.h>
#include <algorithm>

class ExponentialBackoff {
private:
    int duration = 20;
public:
    void backoff() {
        usleep(duration);
        duration = std::min(duration * 2, 250);
    }
};


#endif //LOCKFREE_BENCH_EXPONENTIALBACKOFF_H
