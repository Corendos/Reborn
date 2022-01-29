/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include "tests.h"

#include <cstdio>

#include "reborn/all.cpp"

SECTION(all) { RUN_SECTION(reborn); }

int main(int argc, char** argv) {
    all_func();
    printf("%d Assertions in %d Tests (" GREEN_FG("%d") "/" RED_FG("%d") ")\n", _testing_context.assertion_run_count,
           _testing_context.test_run_count, _testing_context.test_success_count, _testing_context.test_failure_count);
    if (_testing_context.test_failure_count > 0) {
        printf(RED_FG("Failure") "\n");
    } else {
        printf(GREEN_FG("SUCCESS !") "\n");
    }
    return 0;
}