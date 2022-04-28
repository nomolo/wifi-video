cmake_minimum_required(VERSION 3.23)
project(test)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})

add_executable(send send.cpp server.c)
add_executable(receive receive.cpp)
target_link_libraries(receive ${OpenCV_LIBS})
target_link_libraries(send ${OpenCV_LIBS})