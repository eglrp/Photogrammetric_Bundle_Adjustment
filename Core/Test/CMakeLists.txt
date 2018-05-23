cmake_minimum_required(VERSION 3.5)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# enable testing
enable_testing()

add_executable(TestPoint TestPoint.cpp)
target_link_libraries(TestPoint ${GTEST_BOTH_LIBRARIES} CoreLib)
add_test(NAME TestPoint COMMAND TestPoint)

add_executable(TestPointCloud TestPointCloud.cpp)
target_link_libraries(TestPointCloud ${GTEST_BOTH_LIBRARIES} CoreLib)
add_test(NAME TestPointCloud COMMAND TestPointCloud)

add_executable(TestImage TestImage.cpp)
target_link_libraries(TestImage ${GTEST_BOTH_LIBRARIES} CoreLib)
add_test(NAME TestImage COMMAND TestImage)
