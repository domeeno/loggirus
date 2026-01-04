cmake_minimum_required(VERSION 3.20)

project(loggirus)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp loggirus.cpp)

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE
  -pedantic-errors
  -Wall
  -Weffc++
  -Wextra
  -Wconversion
  -Wsign-conversion
  # -Werror
)

