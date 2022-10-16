cmake_minimum_required(VERSION 3.16)

# select c compiler
set(CMAKE_C_COMPILER gcc)

# target
project(c-object LANGUAGES C)

# error code target
set(ERR_SRC err.c)
set(ERR_TOOLS error-generator)

# c sources
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/lib/src C_SOURCES)
list(APPEND C_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/error/src/err.c main.c)

# c includes
set(C_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/lib/inc
${CMAKE_CURRENT_SOURCE_DIR}/error/ErrorGenerator/common)

# compile tools
add_custom_target(${ERR_TOOLS})
add_custom_target(${ERR_SRC} ALL DEPENDS ${ERR_TOOLS})
add_custom_command(TARGET ${ERR_TOOLS}
    COMMAND make DIR_BUILD:=${CMAKE_CURRENT_BINARY_DIR}/${ERR_TOOLS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/error/ErrorGenerator
)

# generate code
add_custom_command(TARGET ${ERR_SRC}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${ERR_TOOLS}/${ERR_TOOLS}
    -i="${CMAKE_CURRENT_SOURCE_DIR}/error/ErrorGenerator/common/err.h" 
    -o="${CMAKE_CURRENT_SOURCE_DIR}/error/src/err.c"
    -input-begin="//error-code-begin" 
    -input-end="//error-code-end" 
    -output-begin="//generate-begin" 
    -output-end="//generate-end"
)

# executable
add_executable(${CMAKE_PROJECT_NAME} ${C_SOURCES})

# compile option
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE 
$<$<CONFIG:DEBUG>:-g>
$<$<CONFIG:RELEASE>:-O3>
)

# link option
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE 
$<$<CONFIG:DEBUG>:-fsanitize=address>)

# include path
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${C_INCLUDES})