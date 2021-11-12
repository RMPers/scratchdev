cmake_minimum_required(VERSION 3.18.0)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

project(sandbox VERSION 1.0)

add_executable(${PROJECT_NAME} main.cpp)

#Enable intrumentation
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finstrument-functions")
#message(${CMAKE_CXX_FLAGS})
#message(${CMAKE_BUILD_TYPE})
