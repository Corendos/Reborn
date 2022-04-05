#
# MIT Licence
# Copyright (c) 2022 Corentin Godeau (@Corendos)
# More details at https://github.com/Corendos/Reborn
#

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_sources(libreborn PRIVATE paths_win32.cpp file_win32.cpp)
else()
	message(FATAL_ERROR "Can't compile for platform \"${CMAKE_SYSTEM_NAME}\"")
endif()
