#
# MIT Licence
# Copyright (c) 2022 Corentin Godeau (@Corendos)
# More details a https://github.com/Corendos/Reborn
#

cmake_minimum_required(VERSION 3.15)
project(Reborn LANGUAGES C CXX)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(PLATFORM_DEFINES "-DPLATFORM_WIN")
else()
    message(FATAL_ERROR "Missing platform defines for platform \"${CMAKE_SYSTEM_NAME}\"")
endif()

#Actual library definition
add_library(libreborn)

target_include_directories(libreborn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(libreborn PRIVATE ${PLATFORM_DEFINES})

set_target_properties(libreborn PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (DEFINED CMAKE_BUILD_TYPE)
    set_target_properties(libreborn PROPERTIES
                                    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug
                                    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release)
endif()

add_subdirectory(include/reborn)
add_subdirectory(src)
add_subdirectory(executable)

#Tests
add_subdirectory(tests)