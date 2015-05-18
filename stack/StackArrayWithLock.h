//
// Created by andrew on 5.5.15.
//

#ifndef LOCKFREE_BENCH_STACKARRAYWITHLOCK_H
#define LOCKFREE_BENCH_STACKARRAYWITHLOCK_H

#include "Stack.h"

template<typename T, typename Lock>
class StackArrayWithLock {
private:
    std::vector<T> st;
    Lock lock;

public:
    void push(T x) {
        lock.lock();
        st.push_back(x);
        lock.unlock();
    }

    bool pop(T &res) {
        bool r;
        lock.lock();
        if (st.empty()) {
            r = false;
        } else {
            res = st.back();
            st.pop_back();
            r = true;
        }
        lock.unlock();
        return r;
    }
};


#endif //LOCKFREE_BENCH_STACKARRAYWITHLOCK_H
