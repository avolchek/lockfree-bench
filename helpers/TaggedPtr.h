//
// Created by andrew on 12.5.15.
//

#ifndef LOCKFREE_BENCH_TAGGEDPTR_H
#define LOCKFREE_BENCH_TAGGEDPTR_H

#include <type_traits>
#include <cstdint>
#include <limits>
#include <assert.h>

template<typename T>
class TaggedPtr {
private:
    typedef std::uint16_t tagT;
    typedef std::uint64_t compressedPtrT;

    static const compressedPtrT ptrMask = 0xffffffffffffUL;//(1LL << 48) - 1;

    union ptrS {
        compressedPtrT p;
        tagT t[4];
    };

    // TODO is static faster?

    compressedPtrT pack(T *p, tagT tag, bool mark) const {
        ptrS res;
        res.p = (compressedPtrT)p;
        assert((res.p & 1) == 0);
        res.t[3] = tag;
        res.p |= mark;
        return res.p;
    }

    T* extractPtr(compressedPtrT p) const {
        return (T*)(((p & ptrMask) >> 1) << 1);
    }

    tagT extractTag(compressedPtrT p) const {
        ptrS res;
        res.p = p;
        return res.t[3];
    }

    bool extractMark(compressedPtrT p) const {
        return bool(p & 1);
    }

    compressedPtrT ptr;

public:

    TaggedPtr() noexcept {

    }

    explicit TaggedPtr(T *p, tagT tag = 0, bool mark = false)
        :ptr(pack(p, tag, mark)) {

    }

    TaggedPtr(const TaggedPtr &other) = default;

    TaggedPtr& operator= (const TaggedPtr &other) = default;

    bool operator == (const TaggedPtr &other) const {
        return ptr == other.ptr;
    }

    bool operator != (const TaggedPtr &other) const {
        return ptr != other.ptr;
    }

    T& operator*() const {
        return *getPtr();
    }

    T* operator->() const {
        return getPtr();
    }

    operator bool(void) const {
        return getPtr() != nullptr;
    }

    T* getPtr() const {
        return extractPtr(ptr);
    }

    void setPtr(T *p) {
        ptr = pack(p, extractTag(ptr), extractMark(ptr));
    }

    tagT getTag() const {
        return extractTag(ptr);
    }

    bool getMark() const {
        return extractMark(ptr);
    }

    void setMark(bool v) {
        ptr = pack(extractPtr(ptr), extractTag(ptr), v);
    }

    tagT getNextTag() const {
        return (extractTag(ptr) + 1) & std::numeric_limits<tagT>::max();
    }

    void setTag(tagT t) {
        ptr = pack(extractPtr(ptr), t, extractMark(ptr));
    }
};


#endif //LOCKFREE_BENCH_TAGGEDPTR_H
