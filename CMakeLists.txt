cmake_minimum_required(VERSION 3.14)
project(spisok_2)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(SOURCE_LIB class_connect.cpp class_myqueue.cpp class_deque.cpp)
add_library(my_library STATIC ${SOURCE_LIB})

add_executable(spisok_2 main.cpp Logger.h Structure.h my_exceptions.h server.h client.h enum_commands.h class_myqueue class_deque class_connect class_myqueue class_deque)