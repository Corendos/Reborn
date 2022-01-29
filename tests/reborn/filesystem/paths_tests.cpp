/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/filesystem/paths.h>

TEST_CASE(get_current_working_directory) {
    Allocator allocator = make_arena_allocator();

    ConstStringU8 current_directory = get_current_working_directory(&allocator);
    CHECK("Changing directory should be successful", change_directory(SCu8("bin")));
    ConstStringU8 current_directory_after = get_current_working_directory(&allocator);

    destroy_arena_allocator(&allocator);
}

SECTION(paths) { RUN_TEST_CASE(get_current_working_directory); }