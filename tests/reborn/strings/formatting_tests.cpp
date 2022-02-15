/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/memory.h>
#include <reborn/strings.h>

#include <cassert>
#include <cstring>

SECTION(strings_formatting) {
    RUN_TEST_CASE(string_write_to_1);
    RUN_TEST_CASE(string_write_to_2);
    RUN_TEST_CASE(string_write_to_3);
    RUN_TEST_CASE(string_write_to_4);
    RUN_TEST_CASE(string_write_to_5);
    RUN_TEST_CASE(string_write_to_6);
    RUN_TEST_CASE(string_write_to_7);
    RUN_TEST_CASE(string_write_to_8);
    RUN_TEST_CASE(string_write_to_9);

    RUN_TEST_CASE(string_write_to_u16_1);
    RUN_TEST_CASE(string_write_to_u16_2);
    RUN_TEST_CASE(string_write_to_u16_3);

    RUN_TEST_CASE(string_write_to_u32_1);
    RUN_TEST_CASE(string_write_to_u32_2);

    RUN_TEST_CASE(string_format_to_1);
    RUN_TEST_CASE(string_format_to_2);
    RUN_TEST_CASE(string_builder_1);
    RUN_TEST_CASE(string_builder_2);
}
