//
// Created by andrew on 18.5.15.
//

#ifndef LOCKFREE_BENCH_EXPONENTIALBACKOFF_H
#define LOCKFREE_BENCH_EXPONENTIALBACKOFF_H


#include <unistd.h>
#include <algorithm>

template <int maxDuration>
class ExponentialBackoff {
private:
    int duration = 20;
public:
    void backoff() {
        usleep(duration);
        duration = std::min(duration * 2, maxDuration);
    }
};


#endif //LOCKFREE_BENCH_EXPONENTIALBACKOFF_H
