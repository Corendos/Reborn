/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include "mutex_tests.cpp"
#include "condition_variable_tests.cpp"
#include "thread_tests.cpp"

SECTION(concurrency) {
    RUN_SECTION(thread);
    RUN_SECTION(condition_variable);
    RUN_SECTION(mutex);
}