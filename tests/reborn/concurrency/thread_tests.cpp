/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/concurrency/thread.h>

static bool thread_touched = false;

u64 thread_func(void* parameters) {
    thread_touched = true;
    return 0;
}

TEST_CASE(thread_creation) {
    ConstStringU8 thread_name = SCu8("My Thread");
    Thread t = make_thread(thread_name, thread_func, 0);
    CHECK("The thread should have the correct name", string_compare(thread_name, t.name) == 0);
    join_thread(&t);
    CHECK("The thread should have run", thread_touched == true);
}

SECTION(thread) { RUN_TEST_CASE(thread_creation); }
