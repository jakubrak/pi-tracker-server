cmake_minimum_required(VERSION 3.1)
project(PiTracker)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED COMPONENTS thread system)

add_executable(pitracker main.cpp)

target_link_libraries(pitracker Boost::thread Boost::system)
