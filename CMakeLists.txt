#
# MIT Licence
# Copyright (c) 2022 Corentin Godeau (@Corendos)
# More details at https://github.com/Corendos/Reborn
#

cmake_minimum_required(VERSION 3.20)
project(Reborn LANGUAGES C CXX)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(PLATFORM_DEFINES "-DPLATFORM_WIN")
else()
    message(FATAL_ERROR "Missing platform defines for platform \"${CMAKE_SYSTEM_NAME}\"")
endif()

add_subdirectory(third_party)

# Source files declaration
list(APPEND REBORN_SRCS
			src/io.cpp
			src/iterator.cpp
			src/strings.cpp
			src/format/format.cpp
			src/memory/allocator.cpp
			src/memory/arena.cpp
			src/memory/buffer.cpp
			src/memory/allocator/arena.cpp
			src/time/clock.cpp)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	list(APPEND REBORN_SRCS
				src/concurrency/mutex_win32.cpp
				src/concurrency/thread_win32.cpp
				src/filesystem/file_win32.cpp
				src/filesystem/paths_win32.cpp)
else()
	message(FATAL_ERROR "Can't compile for platform \"${CMAKE_SYSTEM_NAME}\"")
endif()

# Header files declaration
list(APPEND REBORN_HEADERS
			include/reborn/characters.h
			include/reborn/io.h
			include/reborn/iterator.h
			include/reborn/math.h
			include/reborn/memory.h
			include/reborn/strings.h
			include/reborn/types.h
			include/reborn/concurrency/mutex.h
			include/reborn/concurrency/thread.h
			include/reborn/filesystem/file.h
			include/reborn/filesystem/paths.h
			include/reborn/format/format.h
			include/reborn/memory/allocator.h
			include/reborn/memory/arena.h
			include/reborn/memory/buffer.h
			include/reborn/memory/prelude.h
			include/reborn/memory/allocator/arena.h
			include/reborn/time/clock.h
			include/reborn/time/types.h)

# Object library declarations
add_library(libreborn_objects OBJECT ${REBORN_SRCS} ${REBORN_HEADERS})

target_include_directories(libreborn_objects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(libreborn_objects PUBLIC ${PLATFORM_DEFINES})
target_link_libraries(libreborn_objects PUBLIC stb_sprintf)


add_library(libreborn_static STATIC $<TARGET_OBJECTS:libreborn_objects>)
target_include_directories(libreborn_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.23)
	target_sources(libreborn_static
				   PUBLIC
				   FILE_SET HEADERS
			  	 BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
			   	FILES ${REBRON_HEADERS})
endif()

set_target_properties(libreborn_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(libreborn_static PROPERTIES DEBUG_POSTFIX "_debug")

add_library(libreborn SHARED $<TARGET_OBJECTS:libreborn_objects>)

set_target_properties(libreborn PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(libreborn PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(libreborn PROPERTIES DEBUG_POSTFIX "_debug")

# (Optional) Playground for local tests
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/playground)
	add_subdirectory(playground)
endif()

# Tests
add_subdirectory(tests)

# Install
install(TARGETS libreborn_static libreborn)

# NOTE(Corentin): Workaround to install header file correctly
foreach (header_file ${REBORN_HEADERS})
	cmake_path(GET header_file PARENT_PATH header_file_directory)
	install(FILES ${header_file} DESTINATION ${header_file_directory})
endforeach ()