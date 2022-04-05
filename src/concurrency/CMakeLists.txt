#
# MIT Licence
# Copyright (c) 2022 Corentin Godeau (@Corendos)
# More details at https://github.com/Corendos/Reborn
#

target_sources(libreborn PRIVATE mutex.cpp thread.cpp)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_sources(libreborn PRIVATE mutex_win32.cpp thread_win32.cpp)
else()
	message(FATAL_ERROR "Can't compile for platform \"${CMAKE_SYSTEM_NAME}\"")
endif()
