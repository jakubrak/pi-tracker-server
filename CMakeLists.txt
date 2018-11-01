cmake_minimum_required(VERSION 3.1)
project(pi-tracker-server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Boost REQUIRED COMPONENTS thread system)

add_executable(pi-tracker-server
    main.cpp
    messagehandler.cpp
    messagehandler.h
    messageparser.cpp
    messageparser.h
    imessagelistener.h
    imessagehandler.h
    imessagewriter.h
    startstreamingmsg.cpp
    startstreamingmsg.h
    tcpserver.cpp
    tcpserver.h
    getstreamsettingsmsg.cpp
    getstreamsettingsmsg.h)

target_link_libraries(pi-tracker-server Boost::thread Boost::system)
