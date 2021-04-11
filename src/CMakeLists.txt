cmake_minimum_required(VERSION 3.10)

project(netlib)

add_library(netlib SHARED
    cstreamconn.cpp
    cstreamconnhelper.cpp
    ctcpconn.cpp
    ctcpconnimpl.cpp
    
    cnetlibmux.cpp
    cnetlibmuximpl.cpp
    
    cnetliblogger.cpp
)

target_link_libraries(netlib
    
)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)
