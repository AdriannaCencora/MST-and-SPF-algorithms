cmake_minimum_required(VERSION 3.15.7)

project(sdizo2)

include_directories(include utilities)

set (CMAKE_CXX_FLAGS "-g -Wall -W -ggdb3")

file(GLOB SOURCES "src/*.cpp")
add_executable(sdizo2 ${SOURCES})
