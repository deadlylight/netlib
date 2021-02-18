cmake_minimum_required(VERSION 3.10)

project(netlib)

add_library(netlib SHARED
    cmuxepoll.cpp
    cmuxepollfactory.cpp
    cmuxfactory.cpp
    cmuxfactoryimpl.cpp
    caddrfactory.cpp
    caddrcommon.cpp
    ctcpserverfactory.cpp
    ctcpclientfactory.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)
