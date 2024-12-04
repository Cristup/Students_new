cmake_minimum_required(VERSION 3.31)
project(Students_App)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(Students_App ${SOURCES})
