cmake_minimum_required(VERSION 3.5)
project(CoreLib)

# find Eigen
find_package(Eigen3 REQUIRED)
# check if Eigen was found
if(Eigen3_FOUND)
    message("Eigen3 found")
else()
    message(FATAL_ERROR "Cannot find Eigen3")
endif()

add_library(${PROJECT_NAME}
            src/Point.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${EIGEN3_LIBRARIES})

# add sub-folders
add_subdirectory(include)
add_subdirectory(Test)
