cmake_minimum_required(VERSION 4.2.3)

project(loggirus VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/loggirus/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)

# Target to test loggirus
add_executable(main_loggirus main.cpp)
target_link_libraries(main_loggirus PRIVATE ${PROJECT_NAME}::${PROJECT_NAME})        

target_compile_options(
  main_loggirus
  PRIVATE
  -pedantic-errors
  -Wall
  -Weffc++
  -Wextra
  -Wconversion
  -Wsign-conversion
  -Werror
)

