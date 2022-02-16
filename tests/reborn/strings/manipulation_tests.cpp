/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/memory.h>
#include <reborn/strings.h>

#include <cassert>
#include <cstring>

TEST_CASE(string_comparison) {
    StringU8 str1 = make_string("a");
    StringU8 str2 = make_string("b");
    ConstStringU8 const_str1 = make_const_string("c");
    ConstStringU8 const_str2 = make_const_string("d");

    CHECK("str1 should be equal to str1", string_compare(str1, str1) == 0);
    CHECK("str1 should be less than str2", string_compare(str1, str2) < 0);
    CHECK("str2 should be greater than str1", string_compare(str2, str1) > 0);
    CHECK("const_str1 should be equal to const_str1", string_compare(const_str1, const_str1) == 0);
    CHECK("const_str1 should be less than const_str2", string_compare(const_str1, const_str2) < 0);
    CHECK("const_str1 should be greater than const_str2", string_compare(const_str2, const_str1) > 0);

    CHECK("str1 should be less than const_str1", string_compare(str1, const_str1) < 0);
    CHECK("const_str2 should be greater than str2", string_compare(const_str2, str2) > 0);
}

TEST_CASE(string_comparison_u16) {
    StringU16 str1 = make_string((u16*)u"a");
    StringU16 str2 = make_string((u16*)u"b");
    ConstStringU16 const_str1 = make_const_string((u16*)u"c");
    ConstStringU16 const_str2 = make_const_string((u16*)u"d");

    CHECK("str1 should be equal to str1", string_compare(str1, str1) == 0);
    CHECK("str1 should be less than str2", string_compare(str1, str2) < 0);
    CHECK("str2 should be greater than str1", string_compare(str2, str1) > 0);
    CHECK("const_str1 should be equal to const_str1", string_compare(const_str1, const_str1) == 0);
    CHECK("const_str1 should be less than const_str2", string_compare(const_str1, const_str2) < 0);
    CHECK("const_str1 should be greater than const_str2", string_compare(const_str2, const_str1) > 0);

    CHECK("str1 should be less than const_str1", string_compare(str1, const_str1) < 0);
    CHECK("const_str2 should be greater than str2", string_compare(const_str2, str2) > 0);
}

TEST_CASE(string_comparison_u32) {
    StringU32 str1 = make_string((u32*)U"a");
    StringU32 str2 = make_string((u32*)U"b");
    ConstStringU32 const_str1 = make_const_string((u32*)U"c");
    ConstStringU32 const_str2 = make_const_string((u32*)U"d");

    CHECK("str1 should be equal to str1", string_compare(str1, str1) == 0);
    CHECK("str1 should be less than str2", string_compare(str1, str2) < 0);
    CHECK("str2 should be greater than str1", string_compare(str2, str1) > 0);
    CHECK("const_str1 should be equal to const_str1", string_compare(const_str1, const_str1) == 0);
    CHECK("const_str1 should be less than const_str2", string_compare(const_str1, const_str2) < 0);
    CHECK("const_str1 should be greater than const_str2", string_compare(const_str2, const_str1) > 0);

    CHECK("str1 should be less than const_str1", string_compare(str1, const_str1) < 0);
    CHECK("const_str2 should be greater than str2", string_compare(const_str2, str2) > 0);
}

TEST_CASE(find_first_1) {
    ConstStringU8 str = SCu8("I'm a string with particular ... patterns");
    i64 result = find_first(str, SCu8("..."));
    REQUIRE("The substring should be found", result != -1);
    CHECK("The returned index should match the truth", result == 29);
}

TEST_CASE(find_first_2) {
    ConstStringU8 str = SCu8("I'm a string with particular ... patterns");
    i64 result = find_first(str, SCu8("###"));
    REQUIRE("The substring should not be found", result == -1);
}

TEST_CASE(find_first_3) {
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");
    i64 result = find_first(str, SCu8("..."));
    REQUIRE("The substring should be found", result != -1);
    CHECK("The returned index should match the location of the first pattern", result == 18);
}

TEST_CASE(find_first_4) {
    ConstStringU8 str = SCu8("I'm a string with ...");
    i64 result = find_first(str, SCu8("..."));
    REQUIRE("The substring should be found", result != -1);
    CHECK("The returned index should match the location of the first pattern", result == 18);
}

TEST_CASE(find_last_1) {
    ConstStringU8 str = SCu8("I'm a string with particular ... patterns");
    i64 result = find_last(str, SCu8("..."));
    REQUIRE("The substring should be found", result != -1);
    CHECK("The returned index should match the truth", result == 29);
}

TEST_CASE(find_last_2) {
    ConstStringU8 str = SCu8("I'm a string with particular ... patterns");
    i64 result = find_last(str, SCu8("###"));
    REQUIRE("The substring should not be found", result == -1);
}

TEST_CASE(find_last_3) {
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");
    i64 result = find_last(str, SCu8("..."));
    REQUIRE("The substring should be found", result != -1);
    CHECK("The returned index should match the location of the last pattern", result == 32);
}

TEST_CASE(find_next_1) {
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");
    i64 result = find_next(str, SCu8("..."));
    REQUIRE("The substring should be found", result != -1);
    CHECK("The returned index should match the location of the next pattern", result == 18);

    result = find_next(str, SCu8("..."), result);
    REQUIRE("The substring should be found a second time", result != -1);
    CHECK("The returned index should match the location of the next pattern", result == 32);
}

TEST_CASE(find_next_2) {
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");
    i64 result = find_next(str, SCu8("..."), -100000);
    REQUIRE("The substring should be found", result != -1);
    CHECK("The returned index should match the location of the next pattern", result == 18);
}

TEST_CASE(find_next_3) {
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");
    i64 result = find_next(str, SCu8("..."), 100000);
    REQUIRE("The substring should not be found", result == -1);
}

TEST_CASE(find_next_4) {
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");
    i64 result = find_next(str, SCu8("..."), 0);
    REQUIRE("The substring should be found", result != -1);
    CHECK("The returned index should match the location of the next pattern", result == 18);
}

TEST_CASE(find_previous_1) {
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");
    i64 result = find_previous(str, SCu8("..."), str.size);
    REQUIRE("The substring should be found", result != -1);
    CHECK("The returned index should match the location of the previous pattern", result == 32);

    result = find_previous(str, SCu8("..."), result);
    REQUIRE("The substring should be found", result != -1);
    CHECK("The returned index should match the location of the previous pattern", result == 18);
}

TEST_CASE(find_previous_2) {
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");
    i64 result = find_previous(str, SCu8("..."), 10000);
    REQUIRE("The substring should be found", result != -1);
    CHECK("The returned index should match the location of the previous pattern", result == 32);
}

TEST_CASE(find_previous_3) {
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");
    i64 result = find_previous(str, SCu8("..."), -10000);
    REQUIRE("The substring should not be found", result == -1);
}

TEST_CASE(find_previous_4) {
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");
    i64 result = find_previous(str, SCu8("..."), 0);
    REQUIRE("The substring should not be found", result == -1);
}

TEST_CASE(find_all_1) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");

    ListU64 result = find_all(&allocator, str, SCu8("..."));
    REQUIRE("The function should find the correct number of matches", result.count == 2);
    CHECK("The first match should be found at the correct location", result.first->value == 18);
    CHECK("The second match should be found at the correct location", result.first->next->value == 32);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(find_all_2) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = SCu8("I'm a string with ... repeating ... patterns");

    ListU64 result = find_all(&allocator, str, SCu8(".."));
    REQUIRE("The function should find the correct number of matches", result.count == 4);
    CHECK("The first match should be found at the correct location", result.first->value == 18);
    CHECK("The second match should be found at the correct location", result.first->next->value == 19);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(join_string_1) {
    ConstStringU8 string_values[] = {SCu8("This"), SCu8("is"), SCu8("an"), SCu8("array"), SCu8("of"), SCu8("strings")};
    ConstStringU8Array strings{string_values, array_size(string_values)};
    ConstStringU8 separator = SCu8("-");

    Allocator allocator = make_arena_allocator();

    ConstStringU8 result = join_string(&allocator, strings, separator);

    ConstStringU8 truth = SCu8("This-is-an-array-of-strings");
    CHECK("The resulting string should be equal to the concatenation of sub-strings",
          string_compare(truth, result) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(join_string_2) {
    ConstStringU8 string_values[] = {SCu8("This"), SCu8("is"), SCu8("an"), SCu8("array"), SCu8("of"), SCu8("strings")};
    ConstStringU8Array strings{string_values, array_size(string_values)};
    ConstStringU8 separator = SCu8("");

    Allocator allocator = make_arena_allocator();

    ConstStringU8 result = join_string(&allocator, strings, separator);

    ConstStringU8 truth = SCu8("Thisisanarrayofstrings");
    CHECK("The resulting string should be equal to the concatenation of sub-strings",
          string_compare(truth, result) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(join_string_3) {
    ConstStringU8 string_values[] = {SCu8("This")};
    ConstStringU8Array strings{string_values, array_size(string_values)};
    ConstStringU8 separator = SCu8("-");

    Allocator allocator = make_arena_allocator();

    ConstStringU8 result = join_string(&allocator, strings, separator);

    ConstStringU8 truth = SCu8("This");
    CHECK("The resulting string should be equal to the concatenation of sub-strings",
          string_compare(truth, result) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(join_string_4) {
    ConstStringU8 string_values[] = {SCu8("This"), SCu8("is"), SCu8("an"), SCu8("array"), SCu8("of"), SCu8("strings")};
    ConstStringU8Array strings{string_values, array_size(string_values)};
    ConstStringU8 separator = SCu8(" <-> ");

    Allocator allocator = make_arena_allocator();

    ConstStringU8 result = join_string(&allocator, strings, separator);

    ConstStringU8 truth = SCu8("This <-> is <-> an <-> array <-> of <-> strings");
    CHECK("The resulting string should be equal to the concatenation of sub-strings",
          string_compare(truth, result) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(split_string_1) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = SCu8("I'm a string with...repeating...patterns");

    ConstStringU8List result = split_string(&allocator, str, SCu8("..."));
    REQUIRE("The function should split the string to the correct number of parts", result.count == 3);
    CHECK("The 1st string should be correct", string_compare(result.first->string, SCu8("I'm a string with")) == 0);
    CHECK("The 2nd string should be correct", string_compare(result.first->next->string, SCu8("repeating")) == 0);
    CHECK("The 3rd string should be correct", string_compare(result.first->next->next->string, SCu8("patterns")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(split_string_2) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = SCu8("I'm a string with...repeating...patterns");

    ConstStringU8List result = split_string(&allocator, str, SCu8(".."));
    REQUIRE("The function should split the string to the correct number of parts", result.count == 3);
    CHECK("The 1st string should be correct", string_compare(result.first->string, SCu8("I'm a string with")) == 0);
    CHECK("The 2nd string should be correct", string_compare(result.first->next->string, SCu8(".repeating")) == 0);
    CHECK("The 3rd string should be correct", string_compare(result.first->next->next->string, SCu8(".patterns")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(split_string_3) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = SCu8("...I'm a string with...repeating...patterns...");

    ConstStringU8List result = split_string(&allocator, str, SCu8("..."));
    REQUIRE("The function should split the string to the correct number of parts", result.count == 5);
    CHECK("The 1st string should be correct", string_compare(result.first->string, SCu8("")) == 0);
    CHECK("The 2nd string should be correct",
          string_compare(result.first->next->string, SCu8("I'm a string with")) == 0);
    CHECK("The 3rd string should be correct", string_compare(result.first->next->next->string, SCu8("repeating")) == 0);
    CHECK("The 4th string should be correct",
          string_compare(result.first->next->next->next->string, SCu8("patterns")) == 0);
    CHECK("The 5th string should be correct",
          string_compare(result.first->next->next->next->next->string, SCu8("")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(split_string_array_1) {
    Allocator allocator = make_arena_allocator();
    Arena temporary_arena = make_arena();
    ConstStringU8 str = SCu8("I'm a string with...repeating...patterns");

    ConstStringU8Array result = split_string(&allocator, &temporary_arena, str, SCu8("..."));
    REQUIRE("The function should split the string to the correct number of parts", result.count == 3);
    CHECK("The 1st string should be correct", string_compare(result.values[0], SCu8("I'm a string with")) == 0);
    CHECK("The 2nd string should be correct", string_compare(result.values[1], SCu8("repeating")) == 0);
    CHECK("The 3rd string should be correct", string_compare(result.values[2], SCu8("patterns")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(split_string_array_2) {
    Allocator allocator = make_arena_allocator();
    Arena temporary_arena = make_arena();
    ConstStringU8 str = SCu8("I'm a string with...repeating...patterns");

    ConstStringU8Array result = split_string(&allocator, &temporary_arena, str, SCu8("..."));
    REQUIRE("The function should split the string to the correct number of parts", result.count == 3);
    CHECK("The 1st string should be correct", string_compare(result.values[0], SCu8("I'm a string with")) == 0);
    CHECK("The 2nd string should be correct", string_compare(result.values[1], SCu8("repeating")) == 0);
    CHECK("The 3rd string should be correct", string_compare(result.values[2], SCu8("patterns")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(split_string_array_3) {
    Allocator allocator = make_arena_allocator();
    Arena temporary_arena = make_arena();
    ConstStringU8 str = SCu8("...I'm a string with...repeating...patterns...");

    ConstStringU8Array result = split_string(&allocator, &temporary_arena, str, SCu8("..."));
    REQUIRE("The function should split the string to the correct number of parts", result.count == 5);
    CHECK("The 1st string should be correct", string_compare(result.values[0], SCu8("")) == 0);
    CHECK("The 2nd string should be correct", string_compare(result.values[1], SCu8("I'm a string with")) == 0);
    CHECK("The 3rd string should be correct", string_compare(result.values[2], SCu8("repeating")) == 0);
    CHECK("The 4th string should be correct", string_compare(result.values[3], SCu8("patterns")) == 0);
    CHECK("The 5th string should be correct", string_compare(result.values[4], SCu8("")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(trim_begin_1) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = SCu8("    I'm a string with trailing spaces");

    ConstStringU8 trimmed_str = trim_begin(&allocator, str);
    CHECK("The resulting string should be trimmed from whitespaces",
          string_compare(trimmed_str, SCu8("I'm a string with trailing spaces")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(trim_begin_2) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = SCu8("    ");

    ConstStringU8 trimmed_str = trim_begin(&allocator, str);
    CHECK("The resulting string should be trimmed from whitespaces", string_compare(trimmed_str, SCu8("")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(trim_end_1) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = SCu8("I'm a string with trailing spaces     ");

    ConstStringU8 trimmed_str = trim_end(&allocator, str);
    CHECK("The resulting string should be trimmed from whitespaces",
          string_compare(trimmed_str, SCu8("I'm a string with trailing spaces")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(trim_end_2) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = SCu8("    ");

    ConstStringU8 trimmed_str = trim_end(&allocator, str);
    CHECK("The resulting string should be trimmed from whitespaces", string_compare(trimmed_str, SCu8("")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(trim_all_1) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = SCu8("    I'm a string with trailing spaces     ");

    ConstStringU8 trimmed_str = trim_all(&allocator, str);
    CHECK("The resulting string should be trimmed from whitespaces",
          string_compare(trimmed_str, SCu8("I'm a string with trailing spaces")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(trim_all_2) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = SCu8("    ");

    ConstStringU8 trimmed_str = trim_end(&allocator, str);
    CHECK("The resulting string should be trimmed from whitespaces", string_compare(trimmed_str, SCu8("")) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(replace_1) {
    Allocator allocator = make_arena_allocator();
    Arena temp_arena = make_arena();
    ConstStringU8 str = SCu8("C:/this/is/a/path/with/unix/style");

    ConstStringU8 replaced_str = replace(&allocator, &temp_arena, str, SCu8("/"), SCu8("\\"));
    CHECK("The resulting string should have pattern replaced",
          string_compare(replaced_str, SCu8("C:\\this\\is\\a\\path\\with\\unix\\style")) == 0);

    destroy_arena(&temp_arena);
    destroy_arena_allocator(&allocator);
}

SECTION(strings_manipulation) {
    RUN_TEST_CASE(string_comparison);
    RUN_TEST_CASE(string_comparison_u16);
    RUN_TEST_CASE(string_comparison_u32);

    RUN_TEST_CASE(find_first_1);
    RUN_TEST_CASE(find_first_2);
    RUN_TEST_CASE(find_first_3);
    RUN_TEST_CASE(find_first_4);

    RUN_TEST_CASE(find_last_1);
    RUN_TEST_CASE(find_last_2);
    RUN_TEST_CASE(find_last_3);

    RUN_TEST_CASE(find_next_1);
    RUN_TEST_CASE(find_next_2);
    RUN_TEST_CASE(find_next_3);
    RUN_TEST_CASE(find_next_4);

    RUN_TEST_CASE(find_previous_1);
    RUN_TEST_CASE(find_previous_2);
    RUN_TEST_CASE(find_previous_3);
    RUN_TEST_CASE(find_previous_4);

    RUN_TEST_CASE(find_all_1);
    RUN_TEST_CASE(find_all_2);

    RUN_TEST_CASE(join_string_1);
    RUN_TEST_CASE(join_string_2);
    RUN_TEST_CASE(join_string_3);
    RUN_TEST_CASE(join_string_4);

    RUN_TEST_CASE(split_string_1);
    RUN_TEST_CASE(split_string_2);
    RUN_TEST_CASE(split_string_3);

    RUN_TEST_CASE(split_string_array_1);
    RUN_TEST_CASE(split_string_array_2);
    RUN_TEST_CASE(split_string_array_3);

    RUN_TEST_CASE(trim_begin_1);
    RUN_TEST_CASE(trim_begin_2);

    RUN_TEST_CASE(trim_end_1);
    RUN_TEST_CASE(trim_end_2);

    RUN_TEST_CASE(trim_all_1);
    RUN_TEST_CASE(trim_all_2);

    RUN_TEST_CASE(replace_1);
}
