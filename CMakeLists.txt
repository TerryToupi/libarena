cmake_minimum_required(VERSION 3.20)

project(ORBIT_ARENA_TEST LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

set(TEST_TARGETS "")

foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME "${TEST_FILE}" NAME_WE)
    add_executable("${TEST_NAME}" "${TEST_FILE}")
    list(APPEND TEST_TARGETS "${TEST_NAME}")
endforeach()
