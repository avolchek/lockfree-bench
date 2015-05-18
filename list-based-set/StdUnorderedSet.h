//
// Created by andrew on 6.5.15.
//

#ifndef LOCKFREE_BENCH_STDUNORDEREDSET_H
#define LOCKFREE_BENCH_STDUNORDEREDSET_H

#include <unordered_set>
#include <mutex>
#include "ListSet.h"

template<typename Item>
class StdUnorderedSet {
private:
    std::unordered_set<Item> s;
    std::mutex mtx;
public:

    bool add(Item x) {
        std::lock_guard<std::mutex> lk(mtx);
        if (s.count(x))
            return false;
        s.insert(x);
        return true;
    }

    bool remove(Item x) {
        std::lock_guard<std::mutex> lk(mtx);
        if (!s.count(x))
            return false;
        s.erase(x);
        return true;
    }

    bool contains(Item x) {
        std::lock_guard<std::mutex> lk(mtx);
        return s.count(x);
    }

};


#endif //LOCKFREE_BENCH_STDUNORDEREDSET_H
