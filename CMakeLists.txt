cmake_minimum_required(VERSION 3.13.4)
project(algoritgms LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(algo_c SHARED src/c_api.cpp)

install(TARGETS algo_c DESTINATION lib)
install(FILES include/algo/c_api.h DESTINATION include)

