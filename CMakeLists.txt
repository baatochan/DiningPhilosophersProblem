cmake_minimum_required(VERSION 3.9)
project(DiningPhilosophersProblem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

if (CMAKE_BUILD_TYPE MATCHES "Rel")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static -lpthread")
endif (CMAKE_BUILD_TYPE MATCHES "Rel")

#if(CMAKE_BUILD_TYPE STREQUAL Debug)

add_executable(DiningPhilosophersProblem main.cpp Program.cpp Program.h Philosopher.cpp Philosopher.h)