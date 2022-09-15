cmake_minimum_required(VERSION 3.16)

# select c compiler
set(CMAKE_C_COMPILER gcc)

# target
project(c-object LANGUAGES C)

# c sources
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} C_SOURCES)

# c includes
set(C_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

# target
add_executable(${CMAKE_PROJECT_NAME} ${C_SOURCES})

# include path
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${C_INCLUDES})