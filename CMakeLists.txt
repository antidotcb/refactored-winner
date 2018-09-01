cmake_minimum_required(VERSION 3.5)

set(APP_NAME g5task)
project(${APP_NAME})

set(gtest_disable_pthreads ON CACHE BOOL "Disable uses of pthreads in gtest.")
add_subdirectory(external/googletest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT MSVC)
    set(GCC_PEDANTIC_COMPILE_FLAGS "-Weffc++ -Wall -Werror -Wextra -Wpedantic -ansi -pedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_PEDANTIC_COMPILE_FLAGS}")
endif ()

add_executable(${APP_NAME}
        src/CArray.h
        src/main.cpp
        )

target_compile_features(${APP_NAME} INTERFACE cxx_std_11)

set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${APP_NAME} PROPERTY CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(tests)
