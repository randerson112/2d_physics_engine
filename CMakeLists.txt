cmake_minimum_required(VERSION 3.10)

project(engine)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(engine src/main.cpp)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

target_link_libraries(engine sfml-graphics sfml-window sfml-system)