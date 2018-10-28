cmake_minimum_required(VERSION 3.1)
project(server)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED COMPONENTS thread system)

add_executable(server main.cpp)

target_link_libraries(server Boost::thread Boost::system)
