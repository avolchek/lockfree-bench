//
// Created by andrew on 21.5.15.
//

#ifndef LOCKFREE_BENCH_TBBHASHTABLEWRAPPER_H
#define LOCKFREE_BENCH_TBBHASHTABLEWRAPPER_H

#include <tbb/concurrent_hash_map.h>

template<typename Item>
class TBBConcurentHashTableWrapper {
private:
    tbb::concurrent_hash_map<Item, int> s;
public:

    void insert(Item x) {
        typename tbb::concurrent_hash_map<Item, int>::accessor a;
        s.insert(a, x);
    }

    void erase(Item x) {
        s.erase(x);
    }

    bool contains(Item x) {
        return s.count(x) > 0;
    }
};


#endif //LOCKFREE_BENCH_TBBHASHTABLEWRAPPER_H
