//
// Created by andrew on 5.5.15.
//

#include <iostream>
#include <cstdio>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <fstream>
#include "../hp/HP.h"
#include "../stack/Stack.h"
#include "../stack/LockfreeStack.h"
#include "../locks/SpinLock.h"
#include "../stack/StackLinkedListWithLock.h"
#include "../stack/StackArrayWithLock.h"
#include "../list-based-set/CoarseLockListSet.h"
#include "../list-based-set/FineGrainedLockListSet.h"
#include "../list-based-set/OptimisticLockListSet.h"
#include "../list-based-set/LockFreeListSet.h"
#include "../queue/StdQueueWithLock.h"
#include "../queue/MichaelScottQueue.h"
#include "../queue/BoostLockfreeQueueWrapper.h"
#include "../queue/MSQueueWithPool.h"
#include "../list-based-set/LockFreeListSetWithPool.h"
#include "../list-based-set/LibCDSMichaelListWrapper.h"
#include "../helpers/ExponentialBackoff.h"
#include "../helpers/RandomBackoff.h"
#include "../queue/TBBQueueWrapper.h"
#include "../hash-table/MichaelHashTable.h"
#include "../hash-table/StdUnorderedSetWrapper.h"
#include "../hash-table/TBBConcurentHashSetWrapper.h"
#include <cds/init.h>
#include <cds/gc/hp.h>
#include <cds/container/msqueue.h>
#include <cds/container/fcqueue.h>
#include <cds/urcu/general_buffered.h>
#include <tbb/concurrent_queue.h>
#include <cds/container/michael_set.h>
#include "../hash-table/CDSMichaelSetWrapper.h"
#include <ctime>

std::atomic<bool> isRunning;


template<typename ST>
void workerStackProc(ST *s, int *operationsCnt) {
    HP::getInstance()->attachThread();

    while (!isRunning.load(std::memory_order_acquire));

    while (isRunning.load(std::memory_order_acquire)) {
        if (rand() & 1) {
            s->push(rand());
        } else {
            int res;
            s->pop(res);
        }

        (*operationsCnt)++;
    }
}


template<typename ST>
double testStack(int threadsCount) {

    double res = 0.0;
    const int iterCnt = 3;
    const int runtime = 2;

    for (int iter = 0; iter < iterCnt; iter++) {
        HP::getInstance()->attachThread();

        ST *s = new ST();

        std::vector<int> opCnt(threadsCount, 0);
        std::vector<std::thread> th;

        isRunning.store(false, std::memory_order_release);

        for (int i = 0; i < threadsCount; i++) {
            th.push_back(std::thread(workerStackProc<ST>, s, &opCnt[i]));
        }

        isRunning.store(true, std::memory_order_release);
        sleep(runtime);
        isRunning.store(false, std::memory_order_release);

        for (int i = 0; i < threadsCount; i++) {
            th[i].join();
            res += opCnt[i];
        }

        delete s;

        HP::getInstance()->detachAllThreads();
    }

    return res / iterCnt / runtime;
}

template<typename Container>
void workerListProc(Container *c, int *operationsCount) {
    HP::getInstance()->attachThread();
    cds::threading::Manager::attachThread();

    while (!isRunning.load(std::memory_order_acquire));

    std::vector<int> added;
    int a = 0;
    while (isRunning.load(std::memory_order_acquire)) {
        int op = rand() % 100;
        int x = rand() % 20000000;
        if (op < 5) {
            //std::cerr << "add" << std::endl;
            c->add(x);
            added.push_back(x);
        } else if (op < 10) {
            //std::cerr << "remove" << std::endl;
            if (!added.empty()) {
                c->remove(added.back());
                added.pop_back();
            }
        } else {
            c->contains(x);
        }

        (*operationsCount)++;
    }

    cds::threading::Manager::detachThread();
}

template<typename Container>
double testList(int threadsCnt) {
    const int testIter = 2;
    const int runtime = 2;

    double res = 0.0;

    for (int iter = 0; iter < testIter; iter++) {
        HP::getInstance()->attachThread();

        Container *c = new Container();

        for (int i = 0; i < 0; i++) {
            c->add(rand());
        }

        isRunning.store(false, std::memory_order_release);

        std::vector<std::thread> th;
        std::vector<int> opCnt(threadsCnt, 0);
        for (int i = 0; i < threadsCnt; i++) {
            th.push_back(std::thread(workerListProc<Container>, c, &opCnt[i]));
        }

        isRunning.store(true, std::memory_order_release);
        sleep(runtime);
        isRunning.store(false, std::memory_order_release);

        for (int i = 0; i < threadsCnt; i++) {
            th[i].join();
            res += opCnt[i];
        }

        delete c;
        HP::getInstance()->detachAllThreads();
    }

    return res / runtime / testIter;
}

template<typename Container>
void workerQueueProc(Container *c, int *operationsCnt) {
    HP::getInstance()->attachThread();
    cds::threading::Manager::attachThread();

    while (!isRunning.load(std::memory_order_acquire));

    using namespace std::chrono;

    while (isRunning.load(std::memory_order_acquire)) {
        int op = rand() & 1;
        int x = rand();

        if (op) {
            c->push(x);
        } else {
            c->pop(x);
        }
        (*operationsCnt)++;
    }

    cds::threading::Manager::detachThread();
}


template<typename Container>
double testQueue(int threadsCnt) {
    const int testIter = 2;
    const int runtime = 2;
    const int initialElementsCount = 10000;

    double resOps = 0.0;

    for (int iter = 0; iter < testIter; iter++) {
        std::cerr << "iter " << iter << std::endl;
        HP::getInstance()->attachThread();

        Container *c = new Container();

        for (int i = 0; i < initialElementsCount; ++i) {
            c->push(rand());
        }

        isRunning.store(false, std::memory_order_release);

        std::vector<std::thread> th;
        std::vector<int> opCnt(threadsCnt, 0);

        for (int i = 0; i < threadsCnt; i++) {
            th.push_back(std::thread(workerQueueProc<Container>, c, &opCnt[i]));
        }

        usleep(300);

        isRunning.store(true, std::memory_order_seq_cst);
        sleep(runtime);
        isRunning.store(false, std::memory_order_seq_cst);

        double opSum = 0.0;
        double latencySum = 0.0;

        for (int i = 0; i < threadsCnt; i++) {
            th[i].join();
            opSum += opCnt[i];
        }

        resOps += opSum;
        delete c;
        HP::getInstance()->detachAllThreads();
    }

    resOps /= runtime * testIter;

    return resOps;
}


template<typename Container>
void workerSetProc(Container *c, int *operationsCnt) {
    HP::getInstance()->attachThread();
    cds::threading::Manager::attachThread();
    std::vector<int> added;

    using namespace std::chrono;

    while (!isRunning.load(std::memory_order_seq_cst));

    while (isRunning.load(std::memory_order_seq_cst)) {
        int op = rand() % 100;
        int x = rand();

        if (op < 5) {
            added.push_back(x);
            c->insert(x);
        } else if (op < 10) {
            if (!added.empty()) {
                c->erase(added.back());
                added.pop_back();
            }
        } else {
            c->contains(x);
        }

        (*operationsCnt)++;
    }

    cds::threading::Manager::detachThread();
}

template<typename Container>
double testSet(int threadsCnt, int maxItemsCount, int maxLoadFactor) {
    const int testIter = 2;
    const int runtime = 2;

    const int initialItemsCount = 100000;


    double resOp = 0.0;

    for (int iter = 0; iter < testIter; iter++) {
        //std::cerr << "iter " << iter << std::endl;
        HP::getInstance()->attachThread();

        Container *c = new Container(maxItemsCount, maxLoadFactor);

        for (int i = 0; i < initialItemsCount; i++) {
            c->insert(rand());
        }

        isRunning.store(false, std::memory_order_release);

        std::vector<std::thread> th;
        std::vector<int> opCnt(threadsCnt, 0);

        for (int i = 0; i < threadsCnt; i++) {
            th.push_back(std::thread(workerSetProc<Container>, c, &opCnt[i]));
        }

        sleep(1);

        isRunning.store(true, std::memory_order_seq_cst);
        sleep(runtime);
        isRunning.store(false, std::memory_order_seq_cst);

        double opSum = 0;
        double latencySum = 0;
        for (int i = 0; i < threadsCnt; i++) {
            th[i].join();
            opSum += opCnt[i];
        }

        resOp += opSum;

        delete c;
        HP::getInstance()->detachAllThreads();
    }

    resOp /= runtime / testIter;


    return resOp;
}


void benchmarkStack() {
    for (int threadsCnt = 1; threadsCnt <= 128; threadsCnt++) {
        printf("lock-free stack: %lf\n", testStack<LockfreeStack<int, HP>>(threadsCnt));
        printf("stack on array with locks: %lf\n", testStack<StackArrayWithLock<int, std::mutex>>(threadsCnt));
        printf("stack on array with spin-locks: %lf\n",
               testStack<StackArrayWithLock<int, SpinLock>>(threadsCnt));
        printf("stack on linked-list with locks: %lf\n",
               testStack<StackLinkedListWithLock<int, std::mutex>>(threadsCnt));
        printf("stack on linked-list with spin-locks: %lf\n",
               testStack<StackLinkedListWithLock<int, SpinLock>>(threadsCnt));
    }
}


void benchmarkListSet() {
    using namespace std;

    ofstream cvsFile("list-set-results.cvs");

    vector< pair<string, function<double(int)>>> testData {
            make_pair("coarse-lock list", testList<CoarseLockListSet<int, std::mutex>>),
            make_pair("coarse-lock list with spin-lock", testList<CoarseLockListSet<int, SpinLock>>),
            make_pair("lock-free list", testList<LockFreeListSet<int, HP>>),
            make_pair("lock-free list with pool", testList<LockFreeListSetWithPool<int, HP>>),
            make_pair("cds::container::michaellist", testList<LibCDSMichaelListWrapper<int>>),
            make_pair("optimistic-lock lazy delete", testList<OptimisticLockListSet<int, HP, std::mutex>>),
            make_pair("optimistic-lock lazy delete with spin-lock list", testList<OptimisticLockListSet<int, HP, SpinLock>>),
    };

    cvsFile << '\"' << "threads cnt" << '\"';
    for (auto item : testData) {
        cvsFile << "," << item.first << "\"";
    }
    cvsFile << endl;


    for (int threadCnt = 1; threadCnt <= 128; ) {
        printf("thread cnt - %d\n", threadCnt);
        cvsFile << threadCnt;

        for (auto item : testData) {
            printf("testing %s...\n", item.first.c_str());
            double res = item.second(threadCnt);
            std::cerr << res << std::endl;
            cvsFile << ',' << res;
        }

        cvsFile << endl;

        if (threadCnt > 128) {
            threadCnt += 32;
        } else if (threadCnt > 32) {
            threadCnt += 16;
        } else {
            threadCnt += 2;
        }
    }

    cvsFile.close();
}

void benchmarkQueue() {

    using namespace std;

    ofstream cvsFile("queue-results.cvs");

    typedef int ItemType;
    vector< pair<string, function<double(int)>>> testData {
            make_pair("lock-free queue", testQueue<MichaelScottQueue<ItemType, HP, ConstantBackoff<>>>),
            make_pair("lock-free queue with pool", testQueue<MSQueueWithPool<ItemType, HP>>),
            make_pair("boost::lockfree::queue", testQueue<BoostLockfreeQueueWrapper<ItemType>>),
            make_pair("cds::container::msqueue", testQueue<cds::container::MSQueue<cds::gc::HP, ItemType>>),
            make_pair("cds::container::fcqueue", testQueue<cds::container::FCQueue<ItemType>>),
            make_pair("tbb::concurent_queue", testQueue<TBBQueueWrapper<ItemType>>),
            make_pair("std::queue with mutex", testQueue<StdQueueWithLock<ItemType, std::mutex>>),
            make_pair("std::queue with spin-lock", testQueue<StdQueueWithLock<ItemType, SpinLock>>),
    };

    cvsFile << '\"' << "threads cnt" << '\"';
    for (auto item : testData) {
        cvsFile << "," << item.first << "\"";
    }
    cvsFile << endl;


    for (int threadCnt = 1; threadCnt <= 128; ) {
        printf("thread cnt - %d\n", threadCnt);
        cvsFile << threadCnt;

        for (auto item : testData) {
            printf("testing %s...\n", item.first.c_str());
            double res = item.second(threadCnt);
            cerr << res << endl;
            cvsFile << ',' << res;
        }

        cvsFile << endl;

        if (threadCnt > 128) {
            threadCnt += 32;
        } else if (threadCnt > 32) {
            threadCnt += 16;
        } else {
            threadCnt += 4;
        }
    }

    cvsFile.close();
}

void benchmarkSet() {
    using namespace std;

    ofstream cvsFile("set-results.cvs");

    vector< pair<string, function<double(int, int, int)>>> testData {
            make_pair("Michael hash-table", testSet<MichaelHashTable<long>>),
            make_pair("Michael hash-table with coarse locking lists", testSet<MichaelHashTable<long, CoarseLockListSet<long, SpinLock>>>),
            make_pair("std::unordered_set with mutex", testSet<StdUnorderedSetWrapper<long, std::mutex>>),
            make_pair("std::unordered_set with spin-lock", testSet<StdUnorderedSetWrapper<long, SpinLock>>),
            make_pair("tbb::concurent_hash_map", testSet<TBBConcurentHashTableWrapper<long>>),
            make_pair("cds::michael_set", testSet<CDSMichaelSetWrapper<long>>),
    };

    cvsFile << '\"' << "threads cnt" << '\"';
    for (auto item : testData) {
        cvsFile << "," << item.first << "\"";
    }
    cvsFile << endl;

    const int maxItemsCount = 1000000;
    const int maxLoadFactor = 3;

    for (int threadCnt = 1; threadCnt <= 128; ) {
        printf("thread cnt - %d\n", threadCnt);
        cvsFile << threadCnt;

        for (auto item : testData) {
            printf("testing %s...\n", item.first.c_str());
            double res = item.second(threadCnt, maxItemsCount, maxLoadFactor);
            cerr << res << endl;
            cvsFile << ',' << res;
        }

        cvsFile << endl;

        if (threadCnt > 128) {
            threadCnt += 32;
        } else if (threadCnt > 32) {
            threadCnt += 16;
        } else {
            threadCnt += 4;
        }
    }

    cvsFile.close();
}

int main() {
    HP::initInstance();


    cds::Initialize();
    {
        cds::gc::HP hpGC;
        cds::gc::DHP dhpGC;
        cds::urcu::gc<cds::urcu::general_buffered<>> rcuGC;

        cds::threading::Manager::attachThread();


        benchmarkListSet();
        benchmarkQueue();
        benchmarkSet();
    }

    cds::Terminate();

    return 0;
}
