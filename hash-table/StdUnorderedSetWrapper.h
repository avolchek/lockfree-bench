//
// Created by andrew on 21.5.15.
//

#ifndef LOCKFREE_BENCH_STDUNORDEREDSETWRAPPER_H
#define LOCKFREE_BENCH_STDUNORDEREDSETWRAPPER_H

#include <unordered_set>

template<typename Item, typename Lock>
class StdUnorderedSetWrapper {
private:
    std::unordered_set<Item> s;
    Lock lk;

public:

    void insert(Item x) {
        lk.lock();
        s.insert(x);
        lk.unlock();
    }

    void erase(Item x) {
        lk.lock();
        s.erase(x);
        lk.unlock();
    }

    bool contains(Item x) {
        bool res = false;
        lk.lock();
        res = s.count(x);
        lk.unlock();
        return res;
    }
};


#endif //LOCKFREE_BENCH_STDUNORDEREDSETWRAPPER_H
