//
// Created by andrew on 4.5.15.
//

#include <assert.h>
#include <iostream>
#include <map>
#include "HP.h"

HP* HP::instance = nullptr;
thread_local HP::HPThreadNode* HP::currentThreadNode = nullptr;

void HP::scan(HPThreadNode *rec) {
        std::vector<void*> hp;
        hp.reserve(pointersPerThread * maxThreadsCnt);

        HPThreadNode *p = tListHead.load(std::memory_order::memory_order_acquire);
        int _iter = 0;
        while (p) {
            for (int i = 0; i < pointersPerThread; i++) {
                void* c = p->ptrs[i].load(std::memory_order_acquire);
                if (c) {
                    hp.push_back(c);
                }
            }

            p = p->nxt;
            _iter++;

            assert(_iter <= maxThreadsCnt);
        }

        std::sort(hp.begin(), hp.end());
        std::sort(rec->retiredPointers.begin(), rec->retiredPointers.end());
        rec->retiredPointers.resize(
                std::unique(rec->retiredPointers.begin(), rec->retiredPointers.end()) -
                                 rec->retiredPointers.begin()
        );

        size_t newSz = 0;

        std::map<void*, std::string> alreadyFreed;

        for (auto p : rec->retiredPointers) {
            if (std::binary_search(hp.begin(), hp.end(), p.ptr)) {
                rec->retiredPointers[newSz++] = p;
            } else {
                if (rec->freePtrs.size() < 100) {
                    rec->freePtrs.push_back(p.ptr);
                } else {
                    p.deleteCallback(p.ptr);
                }
            }
        }

        rec->retiredPointers.resize(newSz);
    }

HP::HP(
        int pointersPerThread = 8,
        int maxThreadsCnt = 512
) : pointersPerThread(pointersPerThread),
    maxThreadsCnt(maxThreadsCnt),
    batchSize(pointersPerThread * maxThreadsCnt * 2) {
    tListHead.store(nullptr, std::memory_order::memory_order_release);
}

HP::~HP() {
    auto p = tListHead.load(std::memory_order::memory_order_acquire);
    int _iter = 0;
    while (p) {
        auto *nxt = p->nxt;
        delete p;
        p = nxt;
        _iter++;
        assert(_iter <= maxThreadsCnt);
    }
}

void HP::attachThread() {
    HPThreadNode *newNode = new HPThreadNode();
    newNode->ptrs = new std::atomic<void*>[pointersPerThread];
    for (int i = 0; i < pointersPerThread; i++) {
        newNode->ptrs->store(nullptr, std::memory_order_release);
    }

    do {
        newNode->nxt = tListHead.load(std::memory_order::memory_order_relaxed);
    } while (!tListHead.compare_exchange_strong(newNode->nxt, newNode, std::memory_order::memory_order_release));

    currentThreadNode = newNode;
}

void HP::detachAllThreads() {
    auto p = tListHead.load(std::memory_order::memory_order_acquire);
    int _iter = 0;
    while (p) {
        for (int i = 0; i < pointersPerThread; i++) {
            p->ptrs[i].store(nullptr, std::memory_order_release);
        }
        p = p->nxt;
        _iter++;
        assert(_iter <= maxThreadsCnt);
    }
    p = tListHead.load(std::memory_order::memory_order_acquire);
    _iter = 0;
    while (p) {

        scan(p);
        //std::cerr << p->freePtrs.size() << std::endl;
        for (auto f : p->freePtrs) {
            free(f); // TODO fix me
        }
        p = p->nxt;
        _iter++;
        assert(_iter <= maxThreadsCnt);
    }

    p = tListHead.load(std::memory_order_acquire);
    _iter = 0;
    while (p) {
        auto nxt = p->nxt;
        delete p;
        p = nxt;
        assert(_iter <= maxThreadsCnt);
    }

    tListHead.store(nullptr, std::memory_order_release);
}

std::atomic<void*> *HP::getGuards() {
    return currentThreadNode->ptrs;
}

void HP::retirePtr(void *ptr, std::function<void(void*)> deleteCallback) {
    currentThreadNode->retiredPointers.emplace_back(ptr, deleteCallback);
    if (currentThreadNode->retiredPointers.size() == batchSize) {
        scan(currentThreadNode);
    }
}

void HP::initInstance() {
    instance = new HP();
}

HP *HP::getInstance() {
    return instance;
}

void *HP::tryGetFreePtr() {
    void* res = nullptr;
    if (!currentThreadNode->freePtrs.empty()) {
        res = currentThreadNode->freePtrs.back();
        currentThreadNode->freePtrs.pop_back();
    }
    return res;
}

void HP::destroyInstance() {
    delete instance;
}
