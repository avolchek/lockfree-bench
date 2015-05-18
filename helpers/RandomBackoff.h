//
// Created by andrew on 18.5.15.
//

#ifndef LOCKFREE_BENCH_RANDOMBACKOFF_H
#define LOCKFREE_BENCH_RANDOMBACKOFF_H


#include <unistd.h>
#include <stdlib.h>

class RandomBackoff {
public:
    void backoff() {
        usleep(5 + (rand() % 250));
    }
};


#endif //LOCKFREE_BENCH_RANDOMBACKOFF_H
