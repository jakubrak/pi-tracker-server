cmake_minimum_required(VERSION 3.1)
project(pi-tracker-server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(toolchain.cmake)

find_package(PkgConfig)

pkg_check_modules(GStreamer REQUIRED IMPORTED_TARGET
    gstreamer-1.0
    gstreamer-app-1.0)

message(STATUS ${GStreamer_INCLUDE_DIRS})
message(STATUS ${PKG_CONFIG_SYSROOT_DIR})

find_package(Boost REQUIRED COMPONENTS thread system)

add_executable(${PROJECT_NAME}
    main.cpp
    messagehandler.cpp
    messagehandler.h
    messageparser.cpp
    messageparser.h
    imessagehandler.h
    imessageparser.h
    irequestmessage.h
    iresponsemessage.h
    startstreamingrequest.cpp
    startstreamingrequest.h
    tcpserver.cpp
    tcpserver.h
    pipeline.cpp
    pipeline.h
    streamsettingsrequest.cpp
    streamsettingsrequest.h
    streamsettingsresponse.cpp
    streamsettingsresponse.h
    settings.cpp
    settings.h)

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::GStreamer Boost::thread Boost::system)
