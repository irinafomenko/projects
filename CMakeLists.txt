cmake_minimum_required(VERSION 3.14)
project(spisok_2)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(spisok_2 main.cpp myqueue.h newqueue.h myqueue.cpp newqueue.cpp Logger.h Structure.h my_exceptions.h)