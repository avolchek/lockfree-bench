//
// Created by andrew on 18.5.15.
//

#ifndef LOCKFREE_BENCH_MICHAELHASHTABLE_H
#define LOCKFREE_BENCH_MICHAELHASHTABLE_H

#include "../list-based-set/LockFreeListSetWithPool.h"
#include "../hp/HP.h"
#include "../helpers/ExponentialBackoff.h"

template< typename Item, int bucketsCnt = 256, typename ListSet = LockFreeListSetWithPool<Item, HP, ExponentialBackoff<>>>
class MichaelHashTable {
private:
    ListSet *buckets;
    std::hash<Item> hasher;

    int bIdx(Item x) {
        return hasher(x) % bucketsCnt;
    }

public:
    MichaelHashTable() {

        buckets = new ListSet[bucketsCnt];
    }

    ~MichaelHashTable() {
        delete[] buckets;
    }

    void insert(Item x) {
        buckets[bIdx(x)].add(x);
    }

    void erase(Item x) {
        buckets[bIdx(x)].remove(x);
    }

    bool contains(Item x) {
        return buckets[bIdx(x)].contains(x);
    }
};


#endif //LOCKFREE_BENCH_MICHAELHASHTABLE_H
