cmake_minimum_required(VERSION 3.24)
project(datalog_interpreter)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/src/Parser)
include_directories(${PROJECT_SOURCE_DIR}/src/Scanner)
include_directories(${PROJECT_SOURCE_DIR}/src/Database)

add_executable(datalog_interpreter src/main.cpp)