//
// Created by andrew on 4.5.15.
//

#ifndef LOCKFREE_BENCH_HP_H
#define LOCKFREE_BENCH_HP_H

#include <atomic>
#include <vector>
#include <algorithm>
#include <functional>

class HP {
private:

    typedef std::function<void(void*)> DeleteCallback;

    struct RetiredPointer {
        void *ptr;
        DeleteCallback deleteCallback;

        RetiredPointer() {

        }

        RetiredPointer(void *ptr, DeleteCallback deleteCallback)
            :ptr(ptr), deleteCallback(deleteCallback) {

        }

        bool operator < (const RetiredPointer &other) const {
            return ptr < other.ptr;
        }

        bool operator == (const RetiredPointer &other) const {
            return ptr == other.ptr;
        }
    };

    struct HPThreadNode {
        HPThreadNode *nxt;
        std::atomic<void*> *ptrs;
        std::vector<RetiredPointer> retiredPointers;
        std::vector<void*> freePtrs;

        HPThreadNode() {
            nxt = nullptr;
            ptrs = nullptr;
        }

        ~HPThreadNode() {
            if (ptrs) {
                delete[] ptrs;
                ptrs = nullptr;
            }
        }
    };

    const int pointersPerThread;
    const int maxThreadsCnt;
    const int batchSize;

    std::atomic<HPThreadNode*> tListHead;
    thread_local static HPThreadNode *currentThreadNode;

    void scan(HPThreadNode *rec);

    static HP *instance;

public:

    HP(
              int pointersPerThread,
              int maxThreadsCnt
        );

    ~HP();

    static void initInstance();
    static void destroyInstance();

    static HP * getInstance();

    void attachThread();

    void detachAllThreads();

    static std::atomic<void*> * getGuards();

    void retirePtr(void *ptr, std::function<void(void*)> deleteCallback);

    void * tryGetFreePtr();
};


#endif //LOCKFREE_BENCH_HP_H
