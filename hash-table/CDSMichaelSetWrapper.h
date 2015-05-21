//
// Created by andrew on 21.5.15.
//

#ifndef LOCKFREE_BENCH_CDSMICHAELSETWRAPPER_H
#define LOCKFREE_BENCH_CDSMICHAELSETWRAPPER_H


#include <cds/container/michael_set.h>
#include <cds/gc/impl/hp_decl.h>
#include <cds/container/michael_list_hp.h>


namespace cc = cds::container;

template<typename Item>
class CDSMichaelSetWrapper {
private:

    struct cmp {
        int operator ()(Item const& v1, Item const& v2) const
        {
            if (v1 < v2)
                return -1;
            return v2 < v1 ? 1 : 0;
        }
    };


    struct hash {
        size_t operator ()(int i) const
        {
            return std::hash<int>()(i);
        }

        size_t operator()(Item const& i) const
        {
            return std::hash<Item>()(i);
        }
    };



    typedef cc::MichaelList<cds::gc::HP, Item,  typename cc::michael_list::make_traits<
            cc::opt::compare< cmp >
    >::type > hlist;

    cc::MichaelHashSet<cds::gc::HP, hlist, typename  cc::michael_set::make_traits<
                                               cc::opt::hash< hash >
    >::type > s;

public:

    CDSMichaelSetWrapper(size_t maxItemsCount, size_t maxLoadFactor)
        : s(maxItemsCount, maxLoadFactor){

    }

    void insert(Item x) {
        s.insert(x);
    }

    void erase(Item x) {
        s.erase(x);
    }

    bool contains(Item x) {
        return s.find(x);
    }
};


#endif //LOCKFREE_BENCH_CDSMICHAELSETWRAPPER_H
