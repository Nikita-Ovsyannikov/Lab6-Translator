cmake_minimum_required(VERSION 3.10)

option(BUILD_SAMPLES ON)

set(PROJECT_NAME translator)
project(${PROJECT_NAME})

include(CTest)
enable_testing()

set(TRANSLATOR_TESTS "test_${PROJECT_NAME}")
set(TRANSLATOR_CUSTOM_PROJECT "${PROJECT_NAME}")
set(TRANSLATOR_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(include)

if(BUILD_SAMPLES)
    add_subdirectory(samples)
endif()

if(BUILD_TESTING)
    add_subdirectory(gtest)
    add_subdirectory(test)
endif()

# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")