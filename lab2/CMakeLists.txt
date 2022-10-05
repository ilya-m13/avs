cmake_minimum_required(VERSION 3.22)

project(
  Lab2
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

include(FetchContent)
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG v3.0.0
  GIT_SHALLOW TRUE
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}
)
FetchContent_MakeAvailable(cxxopts)

set(target_name app)
add_executable(${target_name})
target_compile_options(${target_name} PRIVATE -Wall -O3)
target_sources(${target_name} PRIVATE
  main.cpp)
target_link_libraries(${target_name} PRIVATE
  cxxopts)