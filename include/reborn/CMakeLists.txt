#
# MIT Licence
# Copyright (c) 2022 Corentin Godeau (@Corendos)
# More details a https://github.com/Corendos/Reborn
#

target_sources(libreborn PRIVATE characters.h iterator.h strings.h memory.h types.h math.h)

add_subdirectory(concurrency)
add_subdirectory(format)
add_subdirectory(time)