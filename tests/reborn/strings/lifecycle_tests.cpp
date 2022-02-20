/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/memory.h>
#include <reborn/strings.h>

#include <assert.h>

TEST_CASE(make_string_1) {
    char raw_str[] = "This is a string";
    StringU8 str = make_string(raw_str);
    CHECK("The two string should have equal length", strlen(raw_str) == str.size);
    CHECK("The two string should be equal", strncmp(raw_str, str.data, str.size) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
}

TEST_CASE(make_string_2) {
    char raw_str[] = "This is a string";
    StringU8 str = make_string(raw_str, strlen(raw_str));
    CHECK("The two string should have equal length", strlen(raw_str) == str.size);
    CHECK("The two string should be equal", strncmp(raw_str, str.data, str.size) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
}

TEST_CASE(make_string_u16_1) {
    u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    StringU16 str = make_string(raw_str, string_length(raw_str));
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u16)) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
}

TEST_CASE(make_string_u16_2) {
    u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    StringU16 str = make_string(raw_str);
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u16)) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
}

TEST_CASE(make_string_u32_1) {
    u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    StringU32 str = make_string(raw_str, string_length(raw_str));
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u32)) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
}

TEST_CASE(make_string_u32_2) {
    u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    StringU32 str = make_string(raw_str);
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u32)) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
}

TEST_CASE(make_string_from_1) {
    u32 capacity = 128;
    char raw_str_buffer[128] = {0};
    StringU8 str = make_string_from(raw_str_buffer, capacity);
    CHECK("The string capacity should take the terminating character", str.capacity == capacity - 1);
    CHECK("The string size should be 0 on creation", str.size == 0);
}

TEST_CASE(make_string_u16_from_1) {
    u32 capacity = 128;
    u16 raw_str_buffer[128] = {0};
    StringU16 str = make_string_from(raw_str_buffer, capacity);
    CHECK("The string capacity should take the terminating character", str.capacity == capacity - 1);
    CHECK("The string size should be 0 on creation", str.size == 0);
}

TEST_CASE(make_string_u32_from_1) {
    u32 capacity = 128;
    u32 raw_str_buffer[128] = {0};
    StringU32 str = make_string_from(raw_str_buffer, capacity);
    CHECK("The string capacity should take the terminating character", str.capacity == capacity - 1);
    CHECK("The string size should be 0 on creation", str.size == 0);
}

TEST_CASE(make_const_string_1) {
    const char raw_str[] = "This is a string";
    ConstStringU8 str = SCu8(raw_str);
    CHECK("The two string should have equal length", strlen(raw_str) == str.size);
    CHECK("The two string should be equal", strncmp(raw_str, str.data, str.size) == 0);
}

TEST_CASE(make_const_string_2) {
    const char raw_str[] = "This is a string";
    ConstStringU8 str = make_const_string(raw_str);
    CHECK("The two string should have equal length", strlen(raw_str) == str.size);
    CHECK("The two string should be equal", strncmp(raw_str, str.data, str.size) == 0);
}

TEST_CASE(make_const_string_3) {
    const char raw_str[] = "This is a string";
    ConstStringU8 str = make_const_string(raw_str, strlen(raw_str));
    CHECK("The two string should have equal length", strlen(raw_str) == str.size);
    CHECK("The two string should be equal", strncmp(raw_str, str.data, str.size) == 0);
}

TEST_CASE(make_const_string_4) {
    char raw_str[] = "This is a string";
    StringU8 str = make_string(raw_str);
    ConstStringU8 str2 = make_const_string(str);
    CHECK("The two string should have equal length", str2.size == str.size);
    CHECK("The two string should be equal", string_compare(str, str2) == 0);
}

TEST_CASE(make_const_string_u16_1) {
    const u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    ConstStringU16 str = make_const_string(raw_str, string_length(raw_str));
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u16)) == 0);
}

TEST_CASE(make_const_string_u16_2) {
    const u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    ConstStringU16 str = make_const_string(raw_str);
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u16)) == 0);
}

TEST_CASE(make_const_string_u16_3) {
    const u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    ConstStringU16 str = make_const_string(raw_str);
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u16)) == 0);
}

TEST_CASE(make_const_string_u32_1) {
    const u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    ConstStringU32 str = make_const_string(raw_str, string_length(raw_str));
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u32)) == 0);
}

TEST_CASE(make_const_string_u32_2) {
    const u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    ConstStringU32 str = make_const_string(raw_str);
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u32)) == 0);
}

TEST_CASE(make_const_string_u32_3) {
    const u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    ConstStringU32 str = make_const_string(raw_str);
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u32)) == 0);
}

TEST_CASE(push_string_1) {
    char raw_str[] = "This is a string";
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, raw_str, strlen(raw_str));
    CHECK("The two string should have equal length", strlen(raw_str) == str.size);
    CHECK("The two string should be equal", strncmp(raw_str, str.data, str.size) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_string_2) {
    char raw_str[] = "This is a string";
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, raw_str);
    CHECK("The two string should have equal length", strlen(raw_str) == str.size);
    CHECK("The two string should be equal", strncmp(raw_str, str.data, str.size) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_string_3) {
    u64 string_capacity = 128;
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, string_capacity);
    CHECK("The string should have a size of 0", str.size == 0);
    CHECK("The string should have the capacity we asked for", str.capacity == string_capacity);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_string_u16_1) {
    const u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    Allocator allocator = make_arena_allocator();
    StringU16 str = push_string_u16(&allocator, raw_str, string_length(raw_str));
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u16)) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_string_u16_2) {
    const u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    Allocator allocator = make_arena_allocator();
    StringU16 str = push_string_u16(&allocator, raw_str);
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u16)) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_string_u16_3) {
    u64 string_capacity = 128;
    Allocator allocator = make_arena_allocator();
    StringU16 str = push_string_u16(&allocator, string_capacity);
    CHECK("The string should have a size of 0", str.size == 0);
    CHECK("The string should have the capacity we asked for", str.capacity == string_capacity);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_string_u32_1) {
    const u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    Allocator allocator = make_arena_allocator();
    StringU32 str = push_string_u32(&allocator, raw_str, string_length(raw_str));
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u32)) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_string_u32_2) {
    const u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    Allocator allocator = make_arena_allocator();
    StringU32 str = push_string_u32(&allocator, raw_str);
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u32)) == 0);
    CHECK("The created string capacity should be equal to its size", str.size == str.capacity);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_string_u32_3) {
    u64 string_capacity = 128;
    Allocator allocator = make_arena_allocator();
    StringU32 str = push_string_u32(&allocator, string_capacity);
    CHECK("The string should have a size of 0", str.size == 0);
    CHECK("The string should have the capacity we asked for", str.capacity == string_capacity);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_const_string_1) {
    const char raw_str[] = "This is a string";
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = push_const_string(&allocator, raw_str);
    CHECK("The two string should have equal length", strlen(raw_str) == str.size);
    CHECK("The two string should be equal", strncmp(raw_str, str.data, str.size) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_const_string_2) {
    const char raw_str[] = "This is a string";
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = push_const_string(&allocator, raw_str, strlen(raw_str));
    CHECK("The two string should have equal length", strlen(raw_str) == str.size);
    CHECK("The two string should be equal", strncmp(raw_str, str.data, str.size) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_const_string_u16_1) {
    const u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    Allocator allocator = make_arena_allocator();
    ConstStringU16 str = push_const_string(&allocator, raw_str);
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u16)) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_const_string_u16_2) {
    const u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    Allocator allocator = make_arena_allocator();
    ConstStringU16 str = push_const_string(&allocator, raw_str, string_length(raw_str));
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u16)) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_const_string_u32_1) {
    const u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    Allocator allocator = make_arena_allocator();
    ConstStringU32 str = push_const_string(&allocator, raw_str);
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u32)) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(push_const_string_u32_2) {
    const u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    Allocator allocator = make_arena_allocator();
    ConstStringU32 str = push_const_string(&allocator, raw_str, string_length(raw_str));
    CHECK("The two string should have equal length", string_length(raw_str) == str.size);
    CHECK("The two string should be equal", memcmp(raw_str, str.data, str.size * sizeof(u32)) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(copy_const_string_1) {
    ConstStringU8 str = make_const_string("This is a string");
    Allocator allocator = make_arena_allocator();
    ConstStringU8 copy = copy_const_string(&allocator, str);
    CHECK("The two string should have equal length", str.size == copy.size);
    CHECK("The two string should be equal", strncmp(str.data, copy.data, str.size) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(copy_const_string_u16_1) {
    const u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    ConstStringU16 str = make_const_string(raw_str, string_length(raw_str));
    Allocator allocator = make_arena_allocator();
    ConstStringU16 copy = copy_const_string(&allocator, str);
    CHECK("The two string should have equal length", str.size == copy.size);
    CHECK("The two string should be equal", string_compare(str, copy) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(copy_const_string_u32_1) {
    const u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    ConstStringU32 str = make_const_string(raw_str, string_length(raw_str));
    Allocator allocator = make_arena_allocator();
    ConstStringU32 copy = copy_const_string(&allocator, str);
    CHECK("The two string should have equal length", str.size == copy.size);
    CHECK("The two string should be equal", string_compare(str, copy) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(copy_string_1) {
    StringU8 str = make_string("This is a string");
    Allocator allocator = make_arena_allocator();
    StringU8 copy = copy_string(&allocator, str);
    CHECK("The two string should have equal length", str.size == copy.size);
    CHECK("The two string should be equal", strncmp(str.data, copy.data, str.size) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(copy_string_u16_1) {
    u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    StringU16 str = make_string(raw_str);
    Allocator allocator = make_arena_allocator();
    StringU16 copy = copy_string(&allocator, str);
    CHECK("The two string should have equal length", str.size == copy.size);
    CHECK("The two string should be equal", string_compare(str, copy) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(copy_string_u32_1) {
    u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    StringU32 str = make_string(raw_str);
    Allocator allocator = make_arena_allocator();
    StringU32 copy = copy_string(&allocator, str);
    CHECK("The two string should have equal length", str.size == copy.size);
    CHECK("The two string should be equal", string_compare(str, copy) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(substring_u8_1) {
    ConstStringU8 str = SCu8("This is a string");
    u64 sub_offset = 0;
    u64 sub_size = 4;
    ConstStringU8 sub = substring(str, sub_offset, sub_size);
    CHECK("The substring should have the correct length", sub.size == sub_size);
    CHECK("The substring be \"This\"", string_compare(sub, SCu8("This")) == 0);
}

TEST_CASE(substring_u8_2) {
    ConstStringU8 str = SCu8("This is a string");
    u64 sub_offset = 10;
    u64 sub_size = 20;
    ConstStringU8 sub = substring(str, sub_offset, sub_size);
    CHECK("The substring should be truncated to the maximum length possible", sub.size == str.size - sub_offset);
    CHECK("The substring should have the correct length", sub.size == 6);
    CHECK("The substring be \"string\"", string_compare(sub, SCu8("string")) == 0);
}

TEST_CASE(substring_u8_3) {
    ConstStringU8 str = SCu8("This is a string");
    u64 sub_offset = 100;
    u64 sub_size = 20;
    ConstStringU8 sub = substring(str, sub_offset, sub_size);
    CHECK("The substring should be empty if the offset is greater than the source string", sub.size == 0);
    CHECK("The substring be \"\"", string_compare(sub, SCu8("")) == 0);
}

TEST_CASE(substring_u16_1) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str_u8 = SCu8("This is a string");
    ConstStringU16 str = convert_utf8_to_utf16(&allocator, str_u8);
    u64 sub_offset = 0;
    u64 sub_size = 4;
    ConstStringU16 sub = substring(str, sub_offset, sub_size);
    ConstStringU16 truth = convert_utf8_to_utf16(&allocator, SCu8("This"));
    CHECK("The substring should have the correct length", sub.size == sub_size);
    CHECK("The substring be \"This\"", string_compare(sub, truth) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(substring_u16_2) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str_u8 = SCu8("This is a string");
    ConstStringU16 str = convert_utf8_to_utf16(&allocator, str_u8);
    u64 sub_offset = 10;
    u64 sub_size = 20;
    ConstStringU16 sub = substring(str, sub_offset, sub_size);
    ConstStringU16 truth = convert_utf8_to_utf16(&allocator, SCu8("string"));
    CHECK("The substring should be truncated to the maximum length possible", sub.size == str.size - sub_offset);
    CHECK("The substring should have the correct length", sub.size == 6);
    CHECK("The substring be \"string\"", string_compare(sub, truth) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(substring_u16_3) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str_u8 = SCu8("This is a string");
    ConstStringU16 str = convert_utf8_to_utf16(&allocator, str_u8);
    u64 sub_offset = 100;
    u64 sub_size = 20;
    ConstStringU16 sub = substring(str, sub_offset, sub_size);
    ConstStringU16 truth = convert_utf8_to_utf16(&allocator, SCu8(""));
    CHECK("The substring should be empty if the offset is greater than the source string", sub.size == 0);
    CHECK("The substring be \"\"", string_compare(sub, truth) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(substring_u32_1) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str_u8 = SCu8("This is a string");
    ConstStringU32 str = convert_utf8_to_utf32(&allocator, str_u8);
    u64 sub_offset = 0;
    u64 sub_size = 4;
    ConstStringU32 sub = substring(str, sub_offset, sub_size);
    ConstStringU32 truth = convert_utf8_to_utf32(&allocator, SCu8("This"));
    CHECK("The substring should have the correct length", sub.size == sub_size);
    CHECK("The substring be \"This\"", string_compare(sub, truth) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(substring_u32_2) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str_u8 = SCu8("This is a string");
    ConstStringU32 str = convert_utf8_to_utf32(&allocator, str_u8);
    u64 sub_offset = 10;
    u64 sub_size = 20;
    ConstStringU32 sub = substring(str, sub_offset, sub_size);
    ConstStringU32 truth = convert_utf8_to_utf32(&allocator, SCu8("string"));
    CHECK("The substring should be truncated to the maximum length possible", sub.size == str.size - sub_offset);
    CHECK("The substring should have the correct length", sub.size == 6);
    CHECK("The substring be \"string\"", string_compare(sub, truth) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(substring_u32_3) {
    Allocator allocator = make_arena_allocator();
    ConstStringU8 str_u8 = SCu8("This is a string");
    ConstStringU32 str = convert_utf8_to_utf32(&allocator, str_u8);
    u64 sub_offset = 100;
    u64 sub_size = 20;
    ConstStringU32 sub = substring(str, sub_offset, sub_size);
    ConstStringU32 truth = convert_utf8_to_utf32(&allocator, SCu8(""));
    CHECK("The substring should be empty if the offset is greater than the source string", sub.size == 0);
    CHECK("The substring be \"\"", string_compare(sub, truth) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(clear_string_1) {
    StringU8 str = make_string("This is a string");
    Allocator allocator = make_arena_allocator();
    clear_string(&str);
    CHECK("The string should be empty", str.size == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(clear_string_u16_1) {
    u16 raw_str[] = {*(u16*)u"T", *(u16*)u"h", *(u16*)u"i", *(u16*)u"s", (u16)0};
    StringU16 str = make_string(raw_str);
    Allocator allocator = make_arena_allocator();
    clear_string(&str);
    CHECK("The string should be empty", str.size == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(clear_string_u32_1) {
    u32 raw_str[] = {*(u32*)U"T", *(u32*)U"h", *(u32*)U"i", *(u32*)U"s", (u32)0};
    StringU32 str = make_string(raw_str);
    Allocator allocator = make_arena_allocator();
    clear_string(&str);
    CHECK("The string should be empty", str.size == 0);
    destroy_arena_allocator(&allocator);
}

SECTION(strings_lifecycle) {
    RUN_TEST_CASE(make_string_1);
    RUN_TEST_CASE(make_string_2);
    RUN_TEST_CASE(make_string_u16_1);
    RUN_TEST_CASE(make_string_u16_2);
    RUN_TEST_CASE(make_string_u32_1);
    RUN_TEST_CASE(make_string_u32_2);
    RUN_TEST_CASE(make_string_from_1);
    RUN_TEST_CASE(make_string_u16_from_1);
    RUN_TEST_CASE(make_string_u32_from_1);

    RUN_TEST_CASE(make_const_string_1);
    RUN_TEST_CASE(make_const_string_2);
    RUN_TEST_CASE(make_const_string_3);
    RUN_TEST_CASE(make_const_string_4);
    RUN_TEST_CASE(make_const_string_u16_1);
    RUN_TEST_CASE(make_const_string_u16_2);
    RUN_TEST_CASE(make_const_string_u16_3);
    RUN_TEST_CASE(make_const_string_u32_1);
    RUN_TEST_CASE(make_const_string_u32_2);
    RUN_TEST_CASE(make_const_string_u32_3);

    RUN_TEST_CASE(push_string_1);
    RUN_TEST_CASE(push_string_2);
    RUN_TEST_CASE(push_string_3);
    RUN_TEST_CASE(push_string_u16_1);
    RUN_TEST_CASE(push_string_u16_2);
    RUN_TEST_CASE(push_string_u16_3);
    RUN_TEST_CASE(push_string_u32_1);
    RUN_TEST_CASE(push_string_u32_2);
    RUN_TEST_CASE(push_string_u32_3);

    RUN_TEST_CASE(push_const_string_1);
    RUN_TEST_CASE(push_const_string_2);
    RUN_TEST_CASE(push_const_string_u16_1);
    RUN_TEST_CASE(push_const_string_u16_2);
    RUN_TEST_CASE(push_const_string_u32_1);
    RUN_TEST_CASE(push_const_string_u32_2);

    RUN_TEST_CASE(copy_const_string_1);
    RUN_TEST_CASE(copy_const_string_u16_1);
    RUN_TEST_CASE(copy_const_string_u32_1);

    RUN_TEST_CASE(copy_string_1);
    RUN_TEST_CASE(copy_string_u16_1);
    RUN_TEST_CASE(copy_string_u32_1);

    RUN_TEST_CASE(substring_u8_1);
    RUN_TEST_CASE(substring_u8_2);
    RUN_TEST_CASE(substring_u8_3);

    RUN_TEST_CASE(substring_u16_1);
    RUN_TEST_CASE(substring_u16_2);
    RUN_TEST_CASE(substring_u16_3);

    RUN_TEST_CASE(substring_u32_1);
    RUN_TEST_CASE(substring_u32_2);
    RUN_TEST_CASE(substring_u32_3);

    RUN_TEST_CASE(clear_string_1);
    RUN_TEST_CASE(clear_string_u16_1);
    RUN_TEST_CASE(clear_string_u32_1);
}