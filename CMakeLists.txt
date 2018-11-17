#SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
cmake_minimum_required(VERSION 3.2)
message(STATUS "Cmake version ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")
project(swf_batch_log_generator)
add_definitions("-Wall -Wno-unused-variable -Wno-unused-private-field")
set(CMAKE_CXX_STANDARD 13)

# include directories for dependencies and WRENCH libraries
include_directories(src/ /usr/include /usr/local/include)
# source files
set(SOURCE_FILES
        src/main.cpp
        )

# generating the executable
add_executable(swf_batch_log_generator ${SOURCE_FILES})

target_link_libraries(swf_batch_log_generator
        )


install(TARGETS swf_batch_log_generator DESTINATION bin)
