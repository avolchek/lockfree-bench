#SET (CMAKE_C_COMPILER             "/usr/bin/clang")
#SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")

SET (CMAKE_C_COMPILER             "/usr/bin/gcc-4.8")
SET (CMAKE_CXX_COMPILER             "/usr/bin/g++-4.8")


cmake_minimum_required(VERSION 2.8.0)
project(lockfree_bench)


add_subdirectory(./libcds)

include_directories("./boost-lockfree")
include_directories("./boost-atomic")
include_directories(./libcds)
include_directories(./intel-threading-blocks/include/)


find_package(Boost COMPONENTS thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})



file(GLOB TBB_BUILD_DIR ./intel-threading-blocks/build/*_release/)

link_directories(${TBB_BUILD_DIR})

if(Boost_FOUND)

else(Boost_FOUND)
  message(FATAL_ERROR "Cannot find boost.")
endif(Boost_FOUND)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -mtune=native -fno-strict-aliasing -march=native -O0 -pthread")



add_executable(lockfree_bench ${SOURCE_FILES} hp/HP.cpp hp/HP.h stack/Stack.cpp stack/Stack.h stack/StackLinkedListWithLock.cpp stack/StackLinkedListWithLock.h bench/benchmark.cpp stack/LockfreeStack.cpp stack/LockfreeStack.h locks/SpinLock.cpp locks/SpinLock.h helpers/ConstantBackoff.cpp helpers/ConstantBackoff.h list-based-set/ListSet.cpp list-based-set/ListSet.h list-based-set/CoarseLockListSet.cpp list-based-set/CoarseLockListSet.h stack/StackArrayWithLock.cpp stack/StackArrayWithLock.h list-based-set/FineGrainedLockListSet.cpp list-based-set/FineGrainedLockListSet.h list-based-set/OptimisticLockListSet.cpp list-based-set/OptimisticLockListSet.h list-based-set/OptimisticWithLazyRemoveListSet.cpp list-based-set/OptimisticWithLazyRemoveListSet.h list-based-set/LockFreeListSet.cpp list-based-set/LockFreeListSet.h queue/StdQueueWithLock.cpp queue/StdQueueWithLock.h queue/Queue.cpp queue/Queue.h queue/MichaelScottQueue.cpp queue/MichaelScottQueue.h queue/BoostLockfreeQueueWrapper.cpp queue/BoostLockfreeQueueWrapper.h queue/MSQueueWithPool.cpp queue/MSQueueWithPool.h list-based-set/LockFreeListSetWithPool.cpp list-based-set/LockFreeListSetWithPool.h helpers/TaggedPtr.cpp helpers/TaggedPtr.h list-based-set/LibCDSMichaelListWrapper.cpp list-based-set/LibCDSMichaelListWrapper.h helpers/NoBackoff.cpp helpers/NoBackoff.h helpers/RandomBackoff.cpp helpers/RandomBackoff.h helpers/ExponentialBackoff.cpp helpers/ExponentialBackoff.h hash-table/MichaelHashTable.cpp hash-table/MichaelHashTable.h queue/TBBQueueWrapper.cpp queue/TBBQueueWrapper.h hash-table/StdUnorderedSetWrapper.cpp hash-table/StdUnorderedSetWrapper.h hash-table/TBBConcurentHashSetWrapper.cpp hash-table/TBBConcurentHashSetWrapper.h hash-table/CDSMichaelSetWrapper.cpp hash-table/CDSMichaelSetWrapper.h)

target_link_libraries(lockfree_bench cds)
target_link_libraries(lockfree_bench ${Boost_LIBRARIES})
target_link_libraries(lockfree_bench tbb)
target_link_libraries(lockfree_bench tbbmalloc)
