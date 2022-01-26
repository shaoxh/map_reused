cmake_minimum_required(VERSION 3.17)
project(map-reused)
#include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

IF(NOT ROS_BUILD_TYPE)
    SET(ROS_BUILD_TYPE Release)
ENDIF()
set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV 3.0 QUIET)
find_package(Eigen3 3.1.0 REQUIRED)

if(NOT OpenCV_FOUND)
    find_package(OpenCV 2.4.3 QUIET)
    if(NOT OpenCV_FOUND)
        message(FATAL_ERROR "OpenCV > 2.4.3 not found.")
    endif()
endif()

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR})


add_executable(map-reused main.cpp src/Converter.cpp include/Converter.h src/MyDb.cpp include/MyDb.h include/MapLoad.h src/MapLoad.cpp src/MapInfoDto.cpp include/MapInfoDto.h src/MyDbHelper.cpp include/MyDbHelper.h src/FeatureDto.cpp include/FeatureDto.h src/MappointDto.cpp include/MappointDto.h include/Constant.h)

# Link your application with OpenCV libraries
target_link_libraries(map-reused ${OpenCV_LIBS})
target_link_libraries(map-reused libmysqlclient.so)
target_link_libraries(map-reused /home/shawn/Documents/map-reused/Thirdparty/DBoW2/lib/libDBoW2.so)