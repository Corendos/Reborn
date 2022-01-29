#
# MIT Licence
# Copyright (c) 2022 Corentin Godeau (@Corendos)
# More details a https://github.com/Corendos/Reborn
#

target_sources(libreborn PRIVATE strings.cpp iterator.cpp)

add_subdirectory(concurrency)
add_subdirectory(filesystem)
add_subdirectory(format)
add_subdirectory(memory)