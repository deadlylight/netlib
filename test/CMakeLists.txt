cmake_minimum_required(VERSION 3.10)

project(netlib)

add_executable(testnetlib
    testmain.cpp
)

target_link_libraries(testnetlib
    netlib
)

include_directories(${CMAKE_SOURCE_DIR}/include)
