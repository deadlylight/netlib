cmake_minimum_required(VERSION 3.10)

project(netlib)

add_library(netlib SHARED
    cmuxgeneral.cpp
    cmuxepoll.cpp
    cmuxfactory.cpp
    cmuxpipeevent.cpp
    ctcpconnection.cpp
    ctcpserver.cpp
    cctlmsg.cpp
    clogger.cpp
)

target_link_libraries(netlib
    pthread
)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)
