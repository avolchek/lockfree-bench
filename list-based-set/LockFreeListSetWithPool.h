//
// Created by andrew on 12.5.15.
//

#ifndef LOCKFREE_BENCH_LOCKFREELISTSETWITHPOOL_H
#define LOCKFREE_BENCH_LOCKFREELISTSETWITHPOOL_H

//#include <atomic>
#include <boost/atomic/atomic.hpp>
#include <algorithm>
#include <boost/lockfree/detail/tagged_ptr.hpp>
#include "../helpers/TaggedPtr.h"
#include "../helpers/ConstantBackoff.h"
#include "../helpers/NoBackoff.h"
#include "../helpers/ExponentialBackoff.h"

namespace atm = boost;

template<typename Item, typename GC, typename Backoff = NoBackoff>
class LockFreeListSetWithPool {

    struct ListNode;

    typedef TaggedPtr<ListNode> TNodePtr;

    struct ListNode {
        Item data;
        atm::atomic<TNodePtr> nxt;
        ListNode() {
            nxt.store(TNodePtr(nullptr), atm::memory_order_release);
        }
    };

    TNodePtr head;
    TNodePtr dummyHead, dummyTail;

    atm::atomic<TNodePtr> poolHead;

    void spawnNodes() {
        const int cnt = 25;
        for (int i = 0; i < cnt; i++) {
            retireNode(TNodePtr(new ListNode));
        }
    }

    TNodePtr getNewNode() {
        Backoff bkf;
        while (true) {
            TNodePtr v = poolHead.load(atm::memory_order_relaxed);

            if (v) {
                TNodePtr nxt = v->nxt.load(atm::memory_order_relaxed);

                if (poolHead.compare_exchange_weak(v, nxt, atm::memory_order_release, atm::memory_order_relaxed)) {
                    return TNodePtr(v.getPtr(), v.getNextTag());
                }
            } else {
                return TNodePtr(new ListNode());
            }

            bkf.backoff();
        }
    }

    void retireNode(TNodePtr p) {
        Backoff bkf;
        while (true) {
            TNodePtr v = poolHead.load(atm::memory_order_relaxed);
            p->nxt.store(v, atm::memory_order_relaxed);

            if (poolHead.compare_exchange_weak(v, p, atm::memory_order_release, atm::memory_order_relaxed)) {
                break;
            }

            bkf.backoff();
        }
    }


    // TODO optimize me
    std::pair<TNodePtr, TNodePtr> find(Item x) {

        Backoff bkf;
        while (true) {
            retry:
            TNodePtr prev = head;

            TNodePtr curr = prev->nxt.load(atm::memory_order_acquire);

            while (true) {

                TNodePtr next = curr->nxt.load(atm::memory_order_relaxed);

                if (next != curr->nxt.load(atm::memory_order_acquire)) {
                    bkf.backoff();
                    goto retry;
                }

                if (curr != prev->nxt.load(atm::memory_order_acquire)) {
                    bkf.backoff();
                    goto retry;
                }


                if (next.getMark()) {
                    TNodePtr nNext = next;
                    nNext.setMark(false);
                    if (prev->nxt.compare_exchange_strong(curr,
                                                          nNext,
                                                          atm::memory_order_release,
                                                          atm::memory_order_relaxed
                    )) {
                        retireNode(curr);
                    } else {
                        bkf.backoff();
                        goto retry;
                    }
                } else {
                    if (curr == dummyTail || curr->data >= x) {
                        return std::make_pair(prev, curr);
                    }

                    prev = curr;
                }


                curr = next;
            }
        }
    }

public:

    LockFreeListSetWithPool()
        :head(nullptr), dummyHead(nullptr), dummyTail(nullptr) {
        assert(atm::atomic<TNodePtr>().is_lock_free());

        poolHead.store(TNodePtr(nullptr));
        head.setPtr(new ListNode);
        TNodePtr tail(new ListNode);
        head->nxt.store(tail, atm::memory_order_release);
        dummyHead = head, dummyTail = tail;
    }

    ~LockFreeListSetWithPool() {
        auto v = head;
        while (v) {
            auto nxt = v->nxt.load(atm::memory_order_acquire);
            delete v.getPtr();
            v = nxt;
        }

        v = poolHead.load(atm::memory_order_acquire);
        while (v) {
            auto nxt = v->nxt.load(atm::memory_order_acquire);
            delete v.getPtr();
            v = nxt;
        }
    }

    bool add(Item x) {
        TNodePtr newNode = getNewNode();
        newNode->data = x;

        int iter = 0;

        Backoff bkf;

        while (true) {
            auto pos = find(x);

            bool res = false;
            bool done = false;

            if (pos.second != dummyTail && pos.second->data == x) {
                res = false;
                done = true;
                retireNode(newNode);
            } else {
                newNode->nxt.store(pos.second, atm::memory_order_relaxed);

                if (pos.first->nxt.compare_exchange_strong(pos.second, newNode,
                                                           atm::memory_order_release,
                                                           atm::memory_order_relaxed)) {
                    res = true;
                    done = true;
                }

            }

            if (done) {
                return res;
            }

            bkf.backoff();
        }
    }


    bool remove(Item x) {
        int iter = 0;

        Backoff bkf;
        while (true) {
            auto pos = find(x);

            bool res = false;
            bool done = false;

            if (pos.second != dummyTail && pos.second->data == x) {
                auto pNxt = pos.second->nxt.load(atm::memory_order_relaxed);

                auto mNxt = pNxt;
                mNxt.setMark(true);

                auto cp = pNxt;
                cp.setMark(false);
                if (!pos.second->nxt.compare_exchange_strong(cp,
                                                             mNxt,
                                                             atm::memory_order_release,
                                                             atm::memory_order_relaxed
                )) {
                    bkf.backoff();
                    continue;
                }

                pNxt.setMark(false);
                if (pos.first->nxt.compare_exchange_strong(pos.second,
                                                         pNxt, atm::memory_order_release,
                                                           atm::memory_order_relaxed
                )) {
                    retireNode(pos.second);
                }

                res = true;
                done = true;
            } else {
                done = true;
                res = false;
            }

            if (done) {
                return res;
            }

            bkf.backoff();
        }
    }

    bool contains(Item x) {

        auto pos = find(x);
        bool res = pos.second != dummyTail &&
                   !pos.second->nxt.load(atm::memory_order_acquire).getMark() &&
                   pos.second->data == x;
        return res;
    }
};


#endif //LOCKFREE_BENCH_LOCKFREELISTSETWITHPOOL_H
