/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include "strings/formatting_tests.cpp"
#include "strings/lifecycle_tests.cpp"
#include "strings/manipulation_tests.cpp"
#include "strings/unicode_tests.cpp"

SECTION(strings) {
    RUN_SECTION(strings_lifecycle);
    RUN_SECTION(strings_manipulation);
    RUN_SECTION(strings_formatting);
    RUN_SECTION(strings_unicode);
}
