cmake_minimum_required(VERSION 3.0.2)
project(lockfree_bench)


add_subdirectory(./libcds)

include_directories("./boost-lockfree")
include_directories("./boost-atomic")
include_directories(./libcds)


find_package(Boost COMPONENTS thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

if(Boost_FOUND)

else(Boost_FOUND)
  message(FATAL_ERROR "Cannot find boost.")
endif(Boost_FOUND)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -mtune=native -fno-strict-aliasing -march=native -O3 -pthread")



add_executable(lockfree_bench ${SOURCE_FILES} hp/HP.cpp hp/HP.h stack/Stack.cpp stack/Stack.h stack/StackLinkedListWithLock.cpp stack/StackLinkedListWithLock.h bench/benchmark.cpp stack/LockfreeStack.cpp stack/LockfreeStack.h locks/SpinLock.cpp locks/SpinLock.h helpers/ConstantBackoff.cpp helpers/ConstantBackoff.h list-based-set/ListSet.cpp list-based-set/ListSet.h list-based-set/CoarseLockListSet.cpp list-based-set/CoarseLockListSet.h stack/StackArrayWithLock.cpp stack/StackArrayWithLock.h list-based-set/FineGrainedLockListSet.cpp list-based-set/FineGrainedLockListSet.h list-based-set/OptimisticLockListSet.cpp list-based-set/OptimisticLockListSet.h list-based-set/OptimisticWithLazyRemoveListSet.cpp list-based-set/OptimisticWithLazyRemoveListSet.h list-based-set/LockFreeListSet.cpp list-based-set/LockFreeListSet.h list-based-set/StdUnorderedSet.cpp list-based-set/StdUnorderedSet.h queue/StdQueueWithLock.cpp queue/StdQueueWithLock.h queue/Queue.cpp queue/Queue.h queue/MichaelScottQueue.cpp queue/MichaelScottQueue.h queue/BoostLockfreeQueueWrapper.cpp queue/BoostLockfreeQueueWrapper.h queue/MSQueueWithPool.cpp queue/MSQueueWithPool.h list-based-set/LockFreeListSetWithPool.cpp list-based-set/LockFreeListSetWithPool.h helpers/TaggedPtr.cpp helpers/TaggedPtr.h list-based-set/LibCDSMichaelListWrapper.cpp list-based-set/LibCDSMichaelListWrapper.h helpers/NoBackoff.cpp helpers/NoBackoff.h helpers/RandomBackoff.cpp helpers/RandomBackoff.h helpers/ExponentialBackoff.cpp helpers/ExponentialBackoff.h)

target_link_libraries(lockfree_bench cds)
target_link_libraries(lockfree_bench ${Boost_LIBRARIES})