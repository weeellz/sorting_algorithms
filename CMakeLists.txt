cmake_minimum_required(VERSION 3.13.4)
project(algoritgms LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(ALGO_DEPS_PREFIX ${CMAKE_BINARY_DIR}/deps)
set(ALGO_DEPS_SOURCES_PREFIX ${ALGO_DEPS_PREFIX}/sources)
set(ALGO_DEPS_BINARIES_PREFIX ${ALGO_DEPS_PREFIX}/build)
set(ALGO_DEPS_INSTALL_PREFIX ${ALGO_DEPS_PREFIX}/install)

set(DEPS_LIBRARY_DIR ${ALGO_DEPS_INSTALL_PREFIX}/lib)
set(DEPS_INCLUDE_DIR ${ALGO_DEPS_INSTALL_PREFIX}/include)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
include(cmake/install-gtest.cmake)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${DEPS_INCLUDE_DIR})

add_library(algo_c SHARED src/c_api.cpp)
install(TARGETS algo_c DESTINATION lib)
install(FILES include/algo/c_api.h DESTINATION include)

if (ENABLE_TESTS)
    add_subdirectory(tests)
endif()