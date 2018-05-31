cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
project(Photogrammetry)

# enable testing
enable_testing()

# add sub directories
add_subdirectory(Core)
add_subdirectory(Bundle_Adjustment)

