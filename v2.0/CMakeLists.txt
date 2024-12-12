cmake_minimum_required(VERSION 3.31)
project(Students_App)

#set(CMAKE_BUILD_TYPE "Release")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
#set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)



set(CMAKE_BUILD_TYPE "Release")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
endif()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

enable_testing()

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(Students_App ${SOURCES})

add_subdirectory(googletest)

file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(Students_App_Tests ${TEST_SOURCES})

target_link_libraries(Students_App_Tests gtest gtest_main)

add_test(NAME Students_App_Tests COMMAND Students_App_Tests --gtest_color=yes)

