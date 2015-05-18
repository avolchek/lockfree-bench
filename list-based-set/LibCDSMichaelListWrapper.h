//
// Created by andrew on 17.5.15.
//

#ifndef LOCKFREE_BENCH_LIBCDSMICHAELLISTWRAPPER_H
#define LOCKFREE_BENCH_LIBCDSMICHAELLISTWRAPPER_H

#include <cds/container/michael_list_hp.h>

template<typename Item>
class LibCDSMichaelListWrapper {
private:
    cds::container::MichaelList<cds::gc::HP, Item> ls;
public:
    bool add(Item x) {
        return ls.insert(x);
    }

    bool remove(Item x) {
        return ls.erase(x);
    }

    bool contains(Item x) {
        return ls.find(x);
    }
};


#endif //LOCKFREE_BENCH_LIBCDSMICHAELLISTWRAPPER_H
