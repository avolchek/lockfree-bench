set(PACKAGE_NAME cdsu-pqueue)

set(CDSUNIT_PQUEUE_SOURCES
    pop.cpp
    push.cpp
    push_pop.cpp)

add_executable(${PACKAGE_NAME} ${CDSUNIT_PQUEUE_SOURCES} $<TARGET_OBJECTS:${TEST_COMMON}>)
target_link_libraries(${PACKAGE_NAME} ${CDS_SHARED_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
add_test(NAME ${PACKAGE_NAME} COMMAND ${PACKAGE_NAME})