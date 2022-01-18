cmake_minimum_required(VERSION 3.18.0)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_CXX_FLAGS  "-save-temps=cwd")

project(move VERSION 1.0)

add_executable(${PROJECT_NAME} main.cpp)
