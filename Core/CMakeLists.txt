cmake_minimum_required(VERSION 3.5)
project(CoreLib)

# find Eigen
find_package(Eigen3 REQUIRED)
if(Eigen3_FOUND)
    message("Eigen3 found")
else()
    message(FATAL_ERROR "Cannot find Eigen3")
endif()

#find Boost
find_package(BOOST REQUIRED)
if (Boost_FOUND)
    message("BOOST found")
else()
    message(FATAL_ERROR "Cannot find BOOST")
endif()

# set source files
set(CoreLib_SRC
    include/Camera.h include/Camera.hpp
    include/ExteriorOrientation.h include/ExteriorOrientation.hpp
    include/Image.h include/Image.hpp
    include/ImageBlock.h include/ImageBlock.hpp
    include/InteriorOrientation.h include/InteriorOrientation.hpp
    include/Point.h include/Point.hpp
    include/PointCloud.h include/PointCloud.hpp
    include/RandomNumber.h include/RandomNumber.hpp

    src/Point.cpp)

add_library(${PROJECT_NAME} SHARED ${CoreLib_SRC})
target_include_directories(CoreLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE ${EIGEN3_LIBRARIES} ${BOOST_LIBRARIES})

# add sub-folders
add_subdirectory(Test)
