cmake_minimum_required(VERSION 3.10)

project(netlib)

add_library(netlib SHARED
    cmsgsimple.cpp
    cmsgwriter.cpp
    cmsgreader.cpp
    cmsgfactory.cpp

    ctcpfactory.cpp
    cnetstreamconn.cpp
    ctcpconn.cpp

    cmuxfactory.cpp
    cmux.cpp

    clogger.cpp
)

target_link_libraries(netlib
    
)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)
