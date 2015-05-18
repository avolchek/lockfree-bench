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
#include "../list-based-set/StdUnorderedSet.h"
#include "../queue/StdQueueWithLock.h"
#include "../queue/MichaelScottQueue.h"
#include "../queue/BoostLockfreeQueueWrapper.h"
#include "../queue/MSQueueWithPool.h"
#include "../list-based-set/LockFreeListSetWithPool.h"
#include "../list-based-set/LibCDSMichaelListWrapper.h"
#include "../helpers/ExponentialBackoff.h"
#include "../helpers/RandomBackoff.h"
#include <cds/init.h>
#include <cds/gc/hp.h>
#include <cds/container/msqueue.h>
#include <cds/container/fcqueue.h>
#include <cds/urcu/general_buffered.h>

std::atomic<bool> isRunning;

template<typename ST>
void workerStackProc(ST *s, int *operationsCnt) {
    HP::getInstance()->attachThread();

    while (!isRunning.load(std::memory_order_acquire));

    while (isRunning.load(std::memory_order_relaxed)) {
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

    while (!isRunning.load(std::memory_order_seq_cst));

    // TODO remove only previously added items
    int a = 0;
    while (isRunning.load(std::memory_order_seq_cst)) {
        int op = rand() % 100;
        int x = rand() % 20000;
        if (op < 20) {
            //std::cerr << "add" << std::endl;
            c->add(x);
        } else if (op < 40) {
            //std::cerr << "remove" << std::endl;
            c->remove(x);
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
    const int runtime = 5;

    double res = 0.0;

    for (int iter = 0; iter < testIter; iter++) {
        HP::getInstance()->attachThread();

        Container *c = new Container();

        isRunning.store(false, std::memory_order_release);

        std::vector<std::thread> th;
        std::vector<int> opCnt(threadsCnt, 0);
        for (int i = 0; i < threadsCnt; i++) {
            th.push_back(std::thread(workerListProc<Container>, c, &opCnt[i]));
        }

        isRunning.store(true, std::memory_order_seq_cst);
        sleep(runtime);
        isRunning.store(false, std::memory_order_seq_cst);

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

    while (!isRunning.load(std::memory_order_seq_cst));

    while (isRunning.load(std::memory_order_seq_cst)) {
        int op = rand() & 1;
        int x = rand() % 10000;
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
    const int runtime = 3;

    double res = 0.0;

    for (int iter = 0; iter < testIter; iter++) {
        std::cerr << "iter " << iter << std::endl;
        HP::getInstance()->attachThread();

        Container *c = new Container();

        isRunning.store(false, std::memory_order_release);

        std::vector<std::thread> th;
        std::vector<int> opCnt(threadsCnt, 0);
        for (int i = 0; i < threadsCnt; i++) {
            th.push_back(std::thread(workerQueueProc<Container>, c, &opCnt[i]));
        }

        sleep(1);

        isRunning.store(true, std::memory_order_seq_cst);
        sleep(runtime);
        isRunning.store(false, std::memory_order_seq_cst);

        for (int i = 0; i < threadsCnt; i++) {
            th[i].join();
            res += opCnt[i];
        }

        delete c;
        HP::getInstance()->detachAllThreads();
    }

    return res / runtime / testIter;
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

/*
void benchmarkListSet() {
    for (int threadsCnt = 16; threadsCnt <= 128; threadsCnt) {
        printf("lock-free list with pool - %lf\n",
               testList<LockFreeListSetWithPool<int, HP>>(threadsCnt));
        printf("lock-free list - %lf\n",
               testList<LockFreeListSet<int, HP>>(threadsCnt));
        printf("cds::container::michaellist - %lf\n",
                testList<LibCDSMichaelListWrapper<int>>(threadsCnt));

        printf("%d threads:\n", threadsCnt);

        printf("coarse-lock list - %lf\n", testList<CoarseLockListSet<int, std::mutex>>(threadsCnt));
        printf("coarse-lock list with spin-lock - %lf\n",
               testList<CoarseLockListSet<int, SpinLock>>(threadsCnt));

        printf("lock-free list - %lf\n",
               testList<LockFreeListSet<int, HP>>(threadsCnt));
        printf("lock-free list with pool - %lf\n",
               testList<LockFreeListSetWithPool<int, HP>>(threadsCnt));


        printf("optimistic-lock list - %lf\n", testList<OptimisticLockListSet<int, HP, std::mutex>>(threadsCnt));
        printf("optimistic-lock with spin-lock list - %lf\n",
               testList<OptimisticLockListSet<int, HP, SpinLock>>(threadsCnt));

        // TODO add atomics?
        printf("optimistic-lock lazy delete list - %lf\n",
               testList<OptimisticLockListSet<int, HP, std::mutex>>(threadsCnt));
        printf("optimistic-lock lazy delete with spin-lock list - %lf\n",
               testList<OptimisticLockListSet<int, HP, SpinLock>>(threadsCnt));
        printf("\n");
    }
}*/

void benchmarkListSet() {
    using namespace std;

    ofstream cvsFile("list-set-results-backoff.cvs");

    vector< pair<string, function<double(int)>>> testData {
            make_pair("lock-free list with pool", testList<LockFreeListSetWithPool<int, HP>>),
            make_pair("cds::container::michaellist", testList<LibCDSMichaelListWrapper<int>>),
            /*make_pair("coarse-lock list", testList<CoarseLockListSet<int, std::mutex>>),
            make_pair("coarse-lock list with spin-lock", testList<CoarseLockListSet<int, SpinLock>>),
            make_pair("lock-free list", testList<LockFreeListSet<int, HP>>),
            make_pair("lock-free list with pool", testList<LockFreeListSetWithPool<int, HP>>),
            make_pair("cds::container::michaellist", testList<LibCDSMichaelListWrapper<int>>),
            make_pair("optimistic-lock list", testList<OptimisticLockListSet<int, HP, std::mutex>>),
            make_pair("optimistic-lock with spin-lock list", testList<OptimisticLockListSet<int, HP, SpinLock>>),
            make_pair("optimistic-lock lazy delete", testList<OptimisticLockListSet<int, HP, std::mutex>>),
            make_pair("optimistic-lock lazy delete with spin-lock list", testList<OptimisticLockListSet<int, HP, SpinLock>>),
            /*make_pair("[no backoff]lock-free list", testList<LockFreeListSet<int, HP>>),
            make_pair("[constant backoff]lock-free list", testList<LockFreeListSet<int, HP, ConstantBackoff>>),
            make_pair("[exponential backoff]lock-free list", testList<LockFreeListSet<int, HP, ExponentialBackoff>>),
            make_pair("[random backoff]lock-free list", testList<LockFreeListSet<int, HP, RandomBackoff>>),
            make_pair("[no backoff]lock-free list with pool", testList<LockFreeListSetWithPool<int, HP>>),
            make_pair("[constant backoff]lock-free list with pool", testList<LockFreeListSetWithPool<int, HP, ConstantBackoff>>),
            make_pair("[exponential backoff]lock-free list with pool", testList<LockFreeListSetWithPool<int, HP, ExponentialBackoff>>),
            make_pair("[random backoff]lock-free list with pool", testList<LockFreeListSetWithPool<int, HP, RandomBackoff>>),*/
    };

    cvsFile << '\"' << "threads cnt" << '\"';
    for (auto item : testData) {
        cvsFile << "," << item.first << "\"";
    }
    cvsFile << endl;


    for (int threadCnt = 2; threadCnt <= 128; threadCnt += 3) {
        printf("thread cnt - %d\n", threadCnt);
        cvsFile << threadCnt;

        for (auto item : testData) {
            printf("testing %s...\n", item.first.c_str());
            double res = item.second(threadCnt);
            cvsFile << ',' << res;
        }

        cvsFile << endl;
    }

    cvsFile.close();
}

void benchmarkQueue() {
    using namespace std;

    ofstream cvsFile("queue-results.cvs");

    vector< pair<string, function<double(int)>>> testData {
            make_pair("lock-free queue with pool", testQueue<MSQueueWithPool<int, HP, ExponentialBackoff>>),
            make_pair("boost::lockfree::queue", testQueue<BoostLockfreeQueueWrapper<int>>),
            make_pair("cds::container::msqueue", testQueue<cds::container::MSQueue<cds::gc::HP, int>>),
            make_pair("cds::container::fcqueue", testQueue<cds::container::FCQueue<int>>),
            make_pair("std::queue with mutex", testQueue<StdQueueWithLock<int, std::mutex>>),
            make_pair("std::queue with spin-lock", testQueue<StdQueueWithLock<int, SpinLock>>),
            /*make_pair("lock-free queue", testQueue<MichaelScottQueue<int, HP>>),
            make_pair("lock-free queue with pool", testQueue<MSQueueWithPool<int, HP>>),
            make_pair("boost::lockfree::queue", testQueue<BoostLockfreeQueueWrapper<int>>),
            make_pair("cds::container::msqueue", testQueue<cds::container::MSQueue<cds::gc::HP, int>>),
            make_pair("cds::container::fcqueue", testQueue<cds::container::FCQueue<int>>),
            make_pair("std::queue with mutex", testQueue<StdQueueWithLock<int, std::mutex>>),
            make_pair("std::queue with spin-lock", testQueue<StdQueueWithLock<int, SpinLock>>),

            make_pair("[no backoff]lock-free queue with pool", testQueue<MSQueueWithPool<int, HP>>),
            make_pair("[constant backoff]lock-free queue with pool", testQueue<MSQueueWithPool<int, HP, ConstantBackoff>>),
            make_pair("[exponential backoff]lock-free queue with pool", testQueue<MSQueueWithPool<int, HP, ExponentialBackoff>>),
            make_pair("[random backoff]lock-free queue with pool", testQueue<MSQueueWithPool<int, HP, RandomBackoff>>),*/
    };

    cvsFile << '\"' << "threads cnt" << '\"';
    for (auto item : testData) {
        cvsFile << "," << item.first << "\"";
    }
    cvsFile << endl;


    for (int threadCnt = 2; threadCnt <= 90; threadCnt += 3) {
        printf("thread cnt - %d\n", threadCnt);
        cvsFile << threadCnt;

        for (auto item : testData) {
            printf("testing %s...\n", item.first.c_str());
            double res = item.second(threadCnt);
            cvsFile << ',' << res;
        }

        cvsFile << endl;
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


        // TODO compare_exchange_weak is fast!!!
        //benchmarkListSet();
        benchmarkQueue();


    }

    cds::Terminate();

    return 0;
}