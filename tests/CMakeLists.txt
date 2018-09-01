cmake_minimum_required(VERSION 3.5)

set(APP_NAME g5task_tests)

enable_testing()
project(${APP_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT MSVC)
    set(GCC_PEDANTIC_COMPILE_FLAGS "-Weffc++ -Wall -Werror -Wextra -Wpedantic -ansi -pedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_PEDANTIC_COMPILE_FLAGS}")
endif ()

add_executable(${APP_NAME}
        carray_int_other_tests.cpp
        carray_int_tests.cpp
        carray_obj_tests.cpp
        carray_str_tests.cpp
        carray_tests.cpp
        carray_tests.h
        carray_performance_tests.cpp
        )

include_directories(
        SYSTEM ${g5task_SOURCE_DIR}
        SYSTEM ${gtest_SOURCE_DIR}/include
        SYSTEM ${gmock_SOURCE_DIR}/include
)

target_link_libraries(${APP_NAME} gtest gmock gtest_main)

target_compile_features(${APP_NAME} INTERFACE cxx_std_14)

set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${APP_NAME} PROPERTY CMAKE_CXX_EXTENSIONS OFF)
