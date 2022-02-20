/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/memory.h>
#include <reborn/strings.h>

#include <assert.h>

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
    Arena temp_arena = make_arena();
    StringBuilder builder = make_string_builder(&temp_arena);
    destroy_string_builder(&builder);
    ArenaData* arena_data = (ArenaData*)allocator.user_data;
    CHECK("The arena is empty", arena_data->arena->cursor_node == 0);
    destroy_arena(&temp_arena);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(string_builder_2) {
    Allocator allocator = make_arena_allocator();
    Arena temp_arena = make_arena();
    StringBuilder builder = make_string_builder(&temp_arena);
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
    destroy_arena(&temp_arena);
    destroy_arena_allocator(&allocator);
}

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
