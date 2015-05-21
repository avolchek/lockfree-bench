//
// Created by andrew on 18.5.15.
//

#ifndef LOCKFREE_BENCH_MICHAELHASHTABLE_H
#define LOCKFREE_BENCH_MICHAELHASHTABLE_H

#include "../list-based-set/LockFreeListSetWithPool.h"
#include "../hp/HP.h"
#include "../helpers/ExponentialBackoff.h"

template< typename Item, typename ListSet = LockFreeListSetWithPool<Item, HP, ExponentialBackoff<>>>
class MichaelHashTable {
private:
    ListSet *buckets;
    std::hash<Item> hasher;

    size_t maxItemsCount, maxLoadFactor;
    size_t bucketsCnt;

    size_t bIdx(Item x) {
        return hasher(x) & (bucketsCnt - 1);
    }

public:
    MichaelHashTable(size_t maxItemsCount, size_t maxLoadFactor)
        :maxItemsCount(maxItemsCount), maxLoadFactor(maxLoadFactor) {
        bucketsCnt = maxItemsCount / maxLoadFactor + 1;
        size_t p = 1;
        while (p < bucketsCnt) {
            p *= 2;
        }
        bucketsCnt = p;

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
