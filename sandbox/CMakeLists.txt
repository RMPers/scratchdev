cmake_minimum_required(VERSION 3.16.4)

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
message(${CMAKE_C_FLAGS_DEBUG})

#To use threads one need to find and link the project with thread lib
find_package(Threads REQUIRED)
find_package(LTTngUST REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads LTTng::UST)
