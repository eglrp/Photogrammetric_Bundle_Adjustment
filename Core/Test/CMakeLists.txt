cmake_minimum_required(VERSION 3.5)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(TestPoint TestPoint.cpp)
target_link_libraries(TestPoint ${GTEST_BOTH_LIBRARIES} CoreLib)

add_test(AllTestsInCoreLib TestPoint)
