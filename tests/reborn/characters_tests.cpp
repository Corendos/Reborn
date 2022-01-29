/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/characters.h>

TEST_CASE(is_alpha_characters) {
    bool result = true;
    for (char c = 'a'; c <= 'z'; ++c) {
        result &= is_alpha(c);
    }
    CHECK("characters 'a' to 'z' should be considered as alpha", result);

    result = true;
    for (char c = 'A'; c <= 'Z'; ++c) {
        result &= is_alpha(c);
    }
    CHECK("characters 'A' to 'Z' should be considered as alpha", result);

    result = true;
    for (char c = '0'; c <= '9'; ++c) {
        result &= !is_alpha(c);
    }
    CHECK("characters '0' to '9' should not be considered as alpha", result);
}

TEST_CASE(is_numeric_characters) {
    bool result = true;
    for (char c = 'a'; c <= 'z'; ++c) {
        result &= !is_numeric(c);
    }
    CHECK("characters 'a' to 'z' should not be considered as numeric", result);

    result = true;
    for (char c = 'A'; c <= 'Z'; ++c) {
        result &= !is_numeric(c);
    }
    CHECK("characters 'A' to 'Z' should not be considered as numeric", result);

    result = true;
    for (char c = '0'; c <= '9'; ++c) {
        result &= is_numeric(c);
    }
    CHECK("characters '0' to '9' should be considered as numeric", result);
}

TEST_CASE(is_alphanumeric_characters) {
    bool result = true;
    for (char c = 'a'; c <= 'z'; ++c) {
        result &= is_alphanumeric(c);
    }
    CHECK("characters 'a' to 'z' should be considered as alpha", result);

    result = true;
    for (char c = 'A'; c <= 'Z'; ++c) {
        result &= is_alphanumeric(c);
    }
    CHECK("characters 'A' to 'Z' should be considered as alpha", result);

    result = true;
    for (char c = '0'; c <= '9'; ++c) {
        result &= is_alphanumeric(c);
    }
    CHECK("characters '0' to '9' should be considered as alpha", result);
}

TEST_CASE(is_hexadecimal_characters) {
    bool result = true;
    for (char c = 'a'; c <= 'f'; ++c) {
        result &= is_alphanumeric(c);
    }
    CHECK("characters 'a' to 'f' should be considered as hexadecimal", result);

    result = true;
    for (char c = 'A'; c <= 'F'; ++c) {
        result &= is_alphanumeric(c);
    }
    CHECK("characters 'A' to 'F' should be considered as hexadecimal", result);

    result = true;
    for (char c = '0'; c <= '9'; ++c) {
        result &= is_alphanumeric(c);
    }
    CHECK("characters '0' to '9' should be considered as hexadecimal", result);
}

TEST_CASE(is_space_characters) {
    CHECK("' ' should be considered as a space", is_space(' '));
    CHECK("'\\t' should be considered as a space", is_space('\t'));
    CHECK("'\\n' should be considered as a space", is_space('\n'));
    CHECK("'\\v' should be considered as a space", is_space('\v'));
    CHECK("'\\f' should be considered as a space", is_space('\f'));
    CHECK("'\\r' should be considered as a space", is_space('\r'));
}

SECTION(characters) {
    RUN_TEST_CASE(is_alpha_characters);
    RUN_TEST_CASE(is_numeric_characters);
    RUN_TEST_CASE(is_alphanumeric_characters);
    RUN_TEST_CASE(is_hexadecimal_characters);
    RUN_TEST_CASE(is_space_characters);
}