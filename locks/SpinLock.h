//
// Created by andrew on 5.5.15.
//

#ifndef LOCKFREE_BENCH_SPINLOCK_H
#define LOCKFREE_BENCH_SPINLOCK_H


#include <bits/atomic_base.h>
#include "../helpers/ConstantBackoff.h"

class SpinLock {
private:
    std::atomic_flag f;
public:

    SpinLock() {
        f.clear();
    }

    void lock() {
        ConstantBackoff<> bkf;
        while (f.test_and_set(std::memory_order::memory_order_release)) {
            bkf.backoff();
        }
    }

    void unlock() {
        f.clear();
    }
};


#endif //LOCKFREE_BENCH_SPINLOCK_H
