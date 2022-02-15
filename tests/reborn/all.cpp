/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include "concurrency/all.cpp"
#include "characters_tests.cpp"
#include "filesystem/all.cpp"
#include "iterator_tests.cpp"
#include "memory_tests.cpp"
#include "strings/all.cpp"
#include "types_tests.cpp"

SECTION(reborn) {
    RUN_SECTION(types);
    RUN_SECTION(memory);
    RUN_SECTION(strings);
    RUN_SECTION(characters);
    RUN_SECTION(iterator);
    RUN_SECTION(concurrency);
    RUN_SECTION(filesystem);
}