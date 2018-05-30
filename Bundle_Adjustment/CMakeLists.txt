cmake_minimum_required(VERSION 3.5)
project(BundleAdjustmentLib)

# find ceres
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

# set source files
set (BundleAdjustmentLib_SRC
     include/BundleAdjustmentModel.h include/BundleAdjustmentModel.hpp

     src/BundleAdjustmentModel.cpp)

 add_library(${PROJECT_NAME} SHARED ${BundleAdjustmentLib_SRC})
 target_include_directories(BundleAdjustmentLib PUBLIC
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
     PRIVATE src)

 target_link_libraries(${PROJECT_NAME} PRIVATE CoreLib ${CERES_LIBRARIES})

 # add sub-folders
 add_subdirectory(Test)
