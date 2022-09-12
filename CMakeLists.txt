cmake_minimum_required(VERSION 3.13)

project(Drawer VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(drawer STATIC "")
add_executable(tester main.cpp)

target_include_directories(tester PUBLIC include)
target_include_directories(drawer PUBLIC include)

add_subdirectory(include/michelansciilo)
add_subdirectory(src)

target_link_libraries(tester PUBLIC drawer)