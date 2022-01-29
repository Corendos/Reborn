/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/memory.h>
#include <reborn/strings.h>

#include <cassert>
#include <cstring>

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

TEST_CASE(utf8_internal_validation) {
    char length1_start = 0b01110100;
    char length2_start = 0b11010100;
    char length3_start = 0b11101100;
    char length4_start = 0b11110100;
    char continuation = 0b10110110;
    CHECK("A codepoint of length 1 should start with 0b0xxxxxxx", is_valid_utf8_code_unit_start_1(length1_start));
    CHECK("A codepoint of length 2 should start with 0b110xxxxx", is_valid_utf8_code_unit_start_2(length2_start));
    CHECK("A codepoint of length 3 should start with 0b1110xxxx", is_valid_utf8_code_unit_start_3(length3_start));
    CHECK("A codepoint of length 4 should start with 0b11110xxx", is_valid_utf8_code_unit_start_4(length4_start));
    CHECK("A codepoint continuation should start with 0b10xxxxxx", is_valid_utf8_continuation_code_unit(continuation));
}

TEST_CASE(utf8_code_unit_continuation) {
    char continuations[] = {(char)0b10001010, (char)0b10011010, (char)0b10001011};
    CHECK("Multiple bytes starting with 0b10xxxxxx should be valid continuation",
          are_valid_utf8_continuation_code_units(continuations, array_size(continuations)));
}

TEST_CASE(utf8_validation_1) {
    ConstStringU8 str = SCu8("I'm a valid utf8 string");
    CHECK("An ASCII string should be a valid UTF-8 string", is_valid_utf8(str));
}

TEST_CASE(utf8_validation_2) {
    ConstStringU8 str = SCu8("I'm a valid utf8 string containing unicode : \U0001F625");
    CHECK("An string containing escaped unicodes should be a valid UTF-8 string", is_valid_utf8(str));
}

TEST_CASE(utf8_validation_3) {
    ConstStringU8 str = SCu8("I'm not a valid utf8 string because I have a \xB4");
    CHECK("A string containing an invalid byte should not be a valid UTF-8 string", is_valid_utf8(str) == false);
}

TEST_CASE(codepoint_to_utf8_1) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 256);

    ConstStringU8 truth = SCu8(u8"a");

    write_to(&str, (u32)'a');
    CHECK("The string should have the correct character written ('a')", string_compare(str, truth) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(codepoint_to_utf8_2) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 256);

    ConstStringU8 truth = SCu8(u8"\u00C9");

    write_to(&str, (u32)0x00C9);
    CHECK("The string should have the correct character written (U+00C9)", string_compare(str, truth) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(codepoint_to_utf8_3) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 256);

    ConstStringU8 truth = SCu8(u8"\u258C");

    write_to(&str, (u32)0x258C);
    CHECK("The string should have the correct character written (U+258C)", string_compare(str, truth) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(codepoint_to_utf8_4) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 256);

    ConstStringU8 truth = SCu8(u8"\U0001F648");

    write_to(&str, (u32)0x1F648);
    CHECK("The string should have the correct character written (U+1F648)", string_compare(str, truth) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(utf8_conversion_1) {
    Allocator allocator = make_arena_allocator();

    ConstStringU8 str = SCu8(u8"This is a string");
    ConstStringU16 converted_str = convert_utf8_to_utf16(&allocator, str);
    ConstStringU8 back_conversion = convert_utf16_to_utf8(&allocator, converted_str);

    CHECK("The converted string should be the equal to the original string in utf16",
          string_compare(str, back_conversion) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(utf8_conversion_2) {
    Allocator allocator = make_arena_allocator();

    ConstStringU8 str = SCu8(u8"This is a string");
    ConstStringU32 converted_str = convert_utf8_to_utf32(&allocator, str);
    ConstStringU8 back_conversion = convert_utf32_to_utf8(&allocator, converted_str);

    CHECK("The converted string should be the equal to the original string in utf32",
          string_compare(str, back_conversion) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(utf8_iterator_1) {
    ConstStringU8 str = SCu8(u8"");
    Utf8Iterator it = make_utf8_iterator(str);
    CHECK("An iterator created with an empty string should be invalid", is_valid(&it) == false);
}

TEST_CASE(utf8_iterator_2) {
    const char raw_str[] = u8"abcdef";
    ConstStringU8 str = SCu8(raw_str);
    Utf8Iterator it = make_utf8_iterator(str);

    const char* raw_codepoint = raw_str;
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        CHECK("Calling get_codepoint_and_advance on an iterator returns the current codepoint and advance",
              codepoint == (u32)*raw_codepoint);
        raw_codepoint++;
    }
}

TEST_CASE(utf8_iterator_3) {
    const u32 raw_str[] = {*(u32*)U"a", *(u32*)U"b",          *(u32*)U"c", *(u32*)U"d",
                           *(u32*)U"e", *(u32*)U"\U0001035A", (u32)0};
    ConstStringU32 str_u32 = make_const_string(raw_str);

    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = convert_utf32_to_utf8(&allocator, str_u32);
    Utf8Iterator it = make_utf8_iterator(str);

    const u32* raw_codepoint = raw_str;
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        CHECK("Calling get_codepoint_and_advance on an iterator returns the current codepoint and advance",
              codepoint == *raw_codepoint);
        raw_codepoint++;
    }

    destroy_arena_allocator(&allocator);
}

SECTION(utf8) {
    RUN_TEST_CASE(utf8_internal_validation);
    RUN_TEST_CASE(utf8_code_unit_continuation);
    RUN_TEST_CASE(utf8_validation_1);
    RUN_TEST_CASE(utf8_validation_2);
    RUN_TEST_CASE(utf8_validation_3);
    RUN_TEST_CASE(codepoint_to_utf8_1);
    RUN_TEST_CASE(codepoint_to_utf8_2);
    RUN_TEST_CASE(codepoint_to_utf8_3);
    RUN_TEST_CASE(codepoint_to_utf8_4);
    RUN_TEST_CASE(utf8_conversion_1);
    RUN_TEST_CASE(utf8_conversion_2);
    RUN_TEST_CASE(utf8_iterator_1);
    RUN_TEST_CASE(utf8_iterator_2);
    RUN_TEST_CASE(utf8_iterator_3);
}

TEST_CASE(utf16_internal_validation) {
    u16 length1_character_1 = 0xD63F;
    u16 length1_character_2 = 0xF021;
    u16 high_surrogate = 0xD834;
    u16 low_surrogate = 0xDC1A;
    CHECK("A utf16 word between 0x0000 and 0xD7FF should represent a character of length one",
          is_valid_utf16_single_code_unit(length1_character_1, Utf16Type_LE));
    CHECK("A utf16 word between 0xE000 and 0xFFFF should represent a character of length one",
          is_valid_utf16_single_code_unit(length1_character_2, Utf16Type_LE));
    CHECK("A utf16 word between 0xD800 and 0xDBFF should be a valid high surrogate",
          is_valid_utf16_high_surrogate(high_surrogate, Utf16Type_LE));
    CHECK("A utf16 word between 0xDC00 and 0xDFFF should be a valid low surrogate",
          is_valid_utf16_low_surrogate(low_surrogate, Utf16Type_LE));
}

TEST_CASE(utf16_validation_1) {
    const u16* utf16_raw_str = (const u16*)u"This is a valid utf16 string";
    u64 utf16_raw_str_size = string_length(utf16_raw_str);
    ConstStringU16 str = {utf16_raw_str, utf16_raw_str_size};
    CHECK("An array representing a utf16 string should be valid", is_valid_utf16(str));
}

TEST_CASE(utf16_conversion_1) {
    Allocator allocator = make_arena_allocator();
    const u16* utf16_raw_str = (const u16*)u"\u00e9";
    u64 utf16_raw_str_size = string_length(utf16_raw_str);
    ConstStringU16 str = {utf16_raw_str, utf16_raw_str_size};
    ConstStringU8 converted_str = convert_utf16_to_utf8(&allocator, str);
    ConstStringU16 back_conversion = convert_utf8_to_utf16(&allocator, converted_str);

    CHECK("The converted string should be the equal to the original string in utf8",
          string_compare(str, back_conversion) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(utf16_conversion_2) {
    Allocator allocator = make_arena_allocator();
    const u16* utf16_raw_str = (const u16*)u"\u00e9";
    u64 utf16_raw_str_size = string_length(utf16_raw_str);
    ConstStringU16 str = {utf16_raw_str, utf16_raw_str_size};
    ConstStringU32 converted_str = convert_utf16_to_utf32(&allocator, str);
    ConstStringU16 back_conversion = convert_utf32_to_utf16(&allocator, converted_str);

    CHECK("The converted string should be the equal to the original string in utf8",
          string_compare(str, back_conversion) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(utf16_iterator_1) {
    u16 raw_str[] = {0};
    ConstStringU16 str = make_const_string(raw_str);
    Utf16Iterator it = make_utf16_iterator(str);
    CHECK("An iterator created with an empty string should be invalid", is_valid(&it) == false);
}

TEST_CASE(utf16_iterator_2) {
    u16 raw_str[] = {*(u16*)u"a", *(u16*)u"b", *(u16*)u"c", *(u16*)u"d", *(u16*)u"e", *(u16*)u"f", (u16)0};
    ConstStringU16 str = make_const_string(raw_str);
    Utf16Iterator it = make_utf16_iterator(str);

    const u16* raw_codepoint = raw_str;
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        CHECK("Calling get_codepoint_and_advance on an iterator returns the current codepoint and advance",
              codepoint == (u32)*raw_codepoint);
        raw_codepoint++;
    }
}

TEST_CASE(utf16_iterator_3) {
    const u32 raw_str[] = {*(u32*)U"a", *(u32*)U"b",          *(u32*)U"c", *(u32*)U"d",
                           *(u32*)U"e", *(u32*)U"\U0001035A", (u32)0};
    ConstStringU32 str_u32 = make_const_string(raw_str);

    Allocator allocator = make_arena_allocator();
    ConstStringU16 str = convert_utf32_to_utf16(&allocator, str_u32);
    Utf16Iterator it = make_utf16_iterator(str);

    const u32* raw_codepoint = raw_str;
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        CHECK("Calling get_codepoint_and_advance on an iterator returns the current codepoint and advance",
              codepoint == *raw_codepoint);
        raw_codepoint++;
    }

    destroy_arena_allocator(&allocator);
}

SECTION(utf16) {
    RUN_TEST_CASE(utf16_internal_validation);
    RUN_TEST_CASE(utf16_validation_1);
    RUN_TEST_CASE(utf16_conversion_1);
    RUN_TEST_CASE(utf16_conversion_2);
    RUN_TEST_CASE(utf16_iterator_1);
    RUN_TEST_CASE(utf16_iterator_2);
    RUN_TEST_CASE(utf16_iterator_3);
}

SECTION(strings) {
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

    RUN_TEST_CASE(clear_string_1);
    RUN_TEST_CASE(clear_string_u16_1);
    RUN_TEST_CASE(clear_string_u32_1);

    RUN_TEST_CASE(string_comparison);
    RUN_TEST_CASE(string_comparison_u16);
    RUN_TEST_CASE(string_comparison_u32);

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
    RUN_SECTION(utf8);
    RUN_SECTION(utf16);
}