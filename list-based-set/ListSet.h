//
// Created by andrew on 5.5.15.
//

#ifndef LOCKFREE_BENCH_LISTBASEDSET_H
#define LOCKFREE_BENCH_LISTBASEDSET_H

#include <functional>

template<typename Item, typename GC>
class ListSet {
public:
    virtual bool add(Item x) = 0;
    virtual bool remove(Item x) = 0;
    virtual bool contains(Item x) = 0;

    typedef Item ItemType;
};


#endif //LOCKFREE_BENCH_LISTBASEDSET_H
