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

TEST_CASE(string_write_to_1) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 128);
    CONSTRAINT(str.data != 0);

    bool result = write_to(&str, 'E');
    CHECK("The string should have a size of 1", str.size == 1);
    CHECK("The string should be 'E'", string_compare(str, SCu8("E")) == 0);
    CHECK("The write should be successful", result == true);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_2) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 128);
    CONSTRAINT(str.data != 0);

    bool result = write_to(&str, (u32)0x45); // Write an 'E'
    CHECK("The string should have a size of 1", str.size == 1);
    CHECK("The string should be 'E'", string_compare(str, SCu8("E")) == 0);
    CHECK("The write should be successful", result == true);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_3) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 2);
    CONSTRAINT(str.data != 0);

    // NOTE(Corentin): write 2 characters to fill the string
    bool result1 = write_to(&str, 'O');
    bool result2 = write_to(&str, 'K');
    bool result3 = write_to(&str, 'O');
    CHECK("The string should have a size of 2", str.size == 2);
    CHECK("The string should be 'OK'", string_compare(str, SCu8("OK")) == 0);
    CHECK("The first two writes should be successful", result1 && result2);
    CHECK("The third write should not be successful", !result3);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_4) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 1);
    CONSTRAINT(str.data != 0);

    // NOTE(Corentin): write a character spanning 2 bytes
    bool result = write_to(&str, (u32)0x00C9);
    CHECK("The string should still be empty", str.size == 0);
    CHECK("The write should not be successful", !result);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_5) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 128);
    CONSTRAINT(str.data != 0);

    bool result = write_to(&str, (u32)0x00C9);
    CHECK("The string should have a size of 2", str.size == 2);
    CHECK("The string should be equal to the utf8 representation of the codepoint U+00C9",
          string_compare(str, SCu8("\xC3\x89")) == 0);
    CHECK("The write should be successful", result);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_6) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 2);
    CONSTRAINT(str.data != 0);

    // NOTE(Corentin): write a character spanning 3 bytes
    bool result = write_to(&str, (u32)0x0F4B);
    CHECK("The string should still be empty", str.size == 0);
    CHECK("The write should not be successful", !result);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_7) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 128);
    CONSTRAINT(str.data != 0);

    bool result = write_to(&str, (u32)0x0F4B);
    CHECK("The string should have a size of 3", str.size == 3);
    CHECK("The string should be equal to the utf8 representation of the codepoint U+0F4B",
          string_compare(str, SCu8("\xE0\xBD\x8B")) == 0);
    CHECK("The write should be successful", result);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_8) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 3);
    CONSTRAINT(str.data != 0);

    // NOTE(Corentin): write a character spanning 4 bytes
    bool result = write_to(&str, (u32)0x1035A);
    CHECK("The string should still be empty", str.size == 0);
    CHECK("The write should not be successful", !result);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_9) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 128);
    CONSTRAINT(str.data != 0);

    bool result = write_to(&str, (u32)0x1035A);
    CHECK("The string should have a size of 4", str.size == 4);
    CHECK("The string should be equal to the utf8 representation of the codepoint U+1035A",
          string_compare(str, SCu8("\xF0\x90\x8D\x9A")) == 0);
    CHECK("The write should be successful", result);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_u16_1) {
    Allocator allocator = make_arena_allocator();
    StringU16 str = push_string_u16(&allocator, 128);
    CONSTRAINT(str.data != 0);

    bool result = write_to(&str, 'E');
    CHECK("The string should have a size of 1", str.size == 1);
    CHECK("The string should be 'E'", string_compare(str, make_const_string((const u16*)u"E")) == 0);
    CHECK("The write should be successful", result == true);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_u16_2) {
    Allocator allocator = make_arena_allocator();
    StringU16 str = push_string_u16(&allocator, 1);
    CONSTRAINT(str.data != 0);

    // NOTE(Corentin): write a character spanning 2 u16
    bool result = write_to(&str, (u32)0x1035A);
    CHECK("The string should still be empty", str.size == 0);
    CHECK("The write should not be successful", !result);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_u16_3) {
    Allocator allocator = make_arena_allocator();
    StringU16 str = push_string_u16(&allocator, 128);
    CONSTRAINT(str.data != 0);

    bool result = write_to(&str, (u32)0x1035A);
    CHECK("The string should have a size of 1", str.size == 2);
    CHECK("The string should be equal to the utf16 representation of the codepoint U+1035A",
          string_compare(str, make_const_string((const u16*)"\x00\xD8\x5A\xDF\x00")) == 0);
    CHECK("The write should be successful", result == true);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_u32_1) {
    Allocator allocator = make_arena_allocator();
    StringU32 str = push_string_u32(&allocator, 128);
    CONSTRAINT(str.data != 0);

    bool result = write_to(&str, 'E');
    CHECK("The string should have a size of 1", str.size == 1);
    CHECK("The string should be 'E'", string_compare(str, make_const_string((const u32*)U"E")) == 0);
    CHECK("The write should be successful", result == true);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_write_to_u32_2) {
    Allocator allocator = make_arena_allocator();
    StringU32 str = push_string_u32(&allocator, 128);
    CONSTRAINT(str.data != 0);

    bool result = write_to(&str, (u32)0x1035A);
    CHECK("The string should have a size of 1", str.size == 1);
    CHECK("The string should be equal to the utf32 representation of the codepoint U+1035A",
          string_compare(str, make_const_string((const u32*)U"\U0001035A")) == 0);
    CHECK("The write should be successful", result == true);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_format_to_1) {
    const char start[] = "123456789:";
    const char remaining[] = "smoll";
    u64 total_size = strlen(start) + strlen(remaining);

    u64 string_capacity = 16;
    CONSTRAINT(total_size <= string_capacity);

    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, string_capacity);
    CONSTRAINT(str.data != 0);

    FormatResult result = format_to(&str, "%s%s", start, remaining);
    CHECK("The call should be successful", result.success);
    CHECK("The string should be of the right size", str.size == total_size);

    char buffer[128] = {0};
    int concat_result = snprintf(buffer, 128, "%s%s", start, remaining);
    CONSTRAINT(concat_result > 0 && concat_result < 128);
    CHECK("The string should be equal to the concatenation of its parts",
          string_compare(make_const_string(buffer), str) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_format_to_2) {
    const char start[] = "123456789:";
    const char remaining[] = "huge remaining string";
    u64 total_size = strlen(start) + strlen(remaining);

    u64 string_capacity = 16;
    CONSTRAINT(total_size > string_capacity);

    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, string_capacity);
    CONSTRAINT(str.data != 0);

    FormatResult result = format_to(&str, "%s%s", start, remaining);
    CHECK("The call should not be successful", !result.success);
    CHECK("The result should contain the required size", result.required == total_size);
    CHECK("The string should still be empty", str.size == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_builder_1) {
    Allocator allocator = make_arena_allocator();
    StringBuilder builder = make_string_builder();
    destroy_string_builder(&builder);
    ArenaData* arena_data = (ArenaData*)allocator.user_data;
    CHECK("The arena is empty", arena_data->arena->cursor_node == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_builder_2) {
    Allocator allocator = make_arena_allocator();
    StringBuilder builder = make_string_builder();
    format_to(&builder, "This is a test string");
    format_to(&builder, " that has been built");
    format_to(&builder, " using multiple");
    format_to(&builder, " instructions");
    Allocator allocator2 = make_arena_allocator();
    ConstStringU8 string_built = build(&allocator2, &builder);
    destroy_string_builder(&builder);
    ArenaData* arena_data = (ArenaData*)allocator.user_data;
    CHECK("The arena is empty", arena_data->arena->cursor_node == 0);
    destroy_arena_allocator(&allocator2);
    destroy_arena_allocator(&allocator);
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
}
