/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#ifndef REBORN_STRINGS_H
#define REBORN_STRINGS_H

#include <reborn/memory.h>
#include <reborn/types.h>

#include <cstdarg>

// ****************************************************************************
//                                    Macros
// ****************************************************************************

#define expand_string(str) (int)(str.size), (str.data)
#define SCu8(raw_str)                                                                                                  \
    ConstStringU8 { (raw_str), (sizeof(raw_str) / sizeof(*(raw_str))) - 1 }

// ****************************************************************************
//                                    Types
// ****************************************************************************

struct ConstStringU8 {
    const char* data;
    u64 size;
};

typedef u8 Utf16Type;
enum : u8 {
    Utf16Type_LE,
    Utf16Type_BE,
};

struct ConstStringU16 {
    const u16* data;
    u64 size;
    Utf16Type type;
};

struct ConstStringU32 {
    const u32* data;
    u64 size;
};

struct ConstStringU8Array {
    ConstStringU8* values;
    u64 count;
};

struct ConstStringU8ListNode {
    ConstStringU8ListNode* next;
    ConstStringU8ListNode* prev;
    ConstStringU8 string;
};

struct ConstStringU8List {
    ConstStringU8ListNode* first;
    ConstStringU8ListNode* last;
    u64 count;
};

struct StringU8 {
    char* data;
    u64 size;
    u64 capacity;
};

struct StringU16 {
    u16* data;
    u64 size;
    u64 capacity;
    Utf16Type type;
};

struct StringU32 {
    u32* data;
    u64 size;
    u64 capacity;
};

struct StringU8Array {
    StringU8* strings;
    u64 count;
};

struct StringBuilderNode {
    StringBuilderNode* next;
    StringU8 buffer;
};

struct FormatResult {
    i64 required;
    bool success;
};

struct StringBuilder {
    StringBuilderNode* first;
    StringBuilderNode* last;
    u64 size;
    Allocator allocator;
};

struct Utf8Iterator {
    ConstStringU8 string;
    u64 position;
    u64 codepoint_index;
};

struct Utf16Iterator {
    ConstStringU16 string;
    u64 position;
    u64 codepoint_index;
};

struct Utf32Iterator {
    ConstStringU32 string;
    u64 position;
    u64 codepoint_index;
};

// ****************************************************************************
//                                    Functions
// ****************************************************************************

StringU8 make_string(char* str, u64 size);
StringU8 make_string(char* str);
StringU16 make_string(u16* str, u64 size, Utf16Type type = Utf16Type_LE);
StringU16 make_string(u16* str, Utf16Type type = Utf16Type_LE);
StringU32 make_string(u32* str, u64 size);
StringU32 make_string(u32* str);
StringU8 make_string_from(char* data, u64 capacity);
StringU16 make_string_from(u16* data, u64 capacity, Utf16Type type = Utf16Type_LE);
StringU32 make_string_from(u32* data, u64 capacity);

ConstStringU8 make_const_string(const char* str, u64 size);
ConstStringU8 make_const_string(const char* str);
ConstStringU8 make_const_string(StringU8 source);
ConstStringU16 make_const_string(const u16* str, u64 size, Utf16Type type = Utf16Type_LE);
ConstStringU16 make_const_string(const u16* str, Utf16Type type = Utf16Type_LE);
ConstStringU16 make_const_string(StringU16 source);
ConstStringU32 make_const_string(const u32* str, u64 size);
ConstStringU32 make_const_string(const u32* str);
ConstStringU32 make_const_string(StringU32 source);

StringU8 push_string_u8(Allocator* allocator, const char* str, u64 size);
StringU8 push_string_u8(Allocator* allocator, const char* str);
StringU8 push_string_u8(Allocator* allocator, u64 size);
StringU16 push_string_u16(Allocator* allocator, const u16* str, u64 size, Utf16Type type = Utf16Type_LE);
StringU16 push_string_u16(Allocator* allocator, const u16* str, Utf16Type type = Utf16Type_LE);
StringU16 push_string_u16(Allocator* allocator, u64 size, Utf16Type type = Utf16Type_LE);
StringU32 push_string_u32(Allocator* allocator, const u32* str, u64 size);
StringU32 push_string_u32(Allocator* allocator, const u32* str);
StringU32 push_string_u32(Allocator* allocator, u64 size);

ConstStringU8 push_const_string(Allocator* allocator, const char* str, u64 size);
ConstStringU8 push_const_string(Allocator* allocator, const char* str);
ConstStringU16 push_const_string(Allocator* allocator, const u16* str, u64 size, Utf16Type type = Utf16Type_LE);
ConstStringU16 push_const_string(Allocator* allocator, const u16* str, Utf16Type type = Utf16Type_LE);
ConstStringU32 push_const_string(Allocator* allocator, const u32* str, u64 size);
ConstStringU32 push_const_string(Allocator* allocator, const u32* str);

ConstStringU8 copy_const_string(Allocator* allocator, ConstStringU8 other);
ConstStringU16 copy_const_string(Allocator* allocator, ConstStringU16 other);
ConstStringU32 copy_const_string(Allocator* allocator, ConstStringU32 other);

StringU8 copy_string(Allocator* allocator, StringU8 other);
StringU16 copy_string(Allocator* allocator, StringU16 other);
StringU32 copy_string(Allocator* allocator, StringU32 other);

ConstStringU8 substring(ConstStringU8 str, u64 offset, i64 size = -1);
ConstStringU16 substring(ConstStringU16 str, u64 offset, i64 size = -1);
ConstStringU32 substring(ConstStringU32 str, u64 offset, i64 size = -1);

ConstStringU8ListNode* _push_const_string_list_node(Allocator* allocator, ConstStringU8 other);
void push_const_string_list_node(Allocator* allocator, ConstStringU8List* list, ConstStringU8 other);

void clear_string(StringU8* str);
void clear_string(StringU16* str);
void clear_string(StringU32* str);

i32 string_compare(ConstStringU8 a, ConstStringU8 b);
i32 string_compare(StringU8 a, StringU8 b);
i32 string_compare(ConstStringU8 a, StringU8 b);
i32 string_compare(StringU8 a, ConstStringU8 b);

i32 string_compare(ConstStringU16 a, ConstStringU16 b);
i32 string_compare(StringU16 a, StringU16 b);
i32 string_compare(ConstStringU16 a, StringU16 b);
i32 string_compare(StringU16 a, ConstStringU16 b);

i32 string_compare(ConstStringU32 a, ConstStringU32 b);
i32 string_compare(StringU32 a, StringU32 b);
i32 string_compare(ConstStringU32 a, StringU32 b);
i32 string_compare(StringU32 a, ConstStringU32 b);

bool write_to(StringU8* str, char c);
bool write_to(StringU8* str, u32 codepoint);
bool write_to(StringU8* str, StringU8 other);
bool write_to(StringU8* str, ConstStringU8 other);

bool write_to(StringU16* str, char c);
bool write_to(StringU16* str, u32 codepoint);
bool write_to(StringU16* str, StringU16 other);
bool write_to(StringU16* str, ConstStringU16 other);

bool write_to(StringU32* str, char c);
bool write_to(StringU32* str, u32 codepoint);
bool write_to(StringU32* str, StringU32 other);
bool write_to(StringU32* str, ConstStringU32 other);

FormatResult format_to(StringU8* str, const char* format, ...);
FormatResult format_to_v(StringU8* str, const char* format, va_list args);

i64 required_for_format(const char* format, va_list args);

StringBuilder make_string_builder(Arena* temporary);
void destroy_string_builder(StringBuilder* builder);
void format_to(StringBuilder* builder, const char* format, ...);
void format_to_v(StringBuilder* builder, const char* format, va_list args);
ConstStringU8 build(Allocator* allocator, StringBuilder* builder);

bool is_valid_utf8(ConstStringU8 str);
bool is_valid_utf16(ConstStringU16 str);
bool is_valid_utf32(ConstStringU8 str);

ConstStringU16 convert_utf8_to_utf16(Allocator* allocator, ConstStringU8 str, Utf16Type type = Utf16Type_LE);
ConstStringU16 convert_utf8_to_utf16(Allocator* allocator, StringU8 str, Utf16Type type = Utf16Type_LE);
ConstStringU32 convert_utf8_to_utf32(Allocator* allocator, ConstStringU8 str);
ConstStringU32 convert_utf8_to_utf32(Allocator* allocator, StringU8 str);

ConstStringU8 convert_utf16_to_utf8(Allocator* allocator, ConstStringU16 str);
ConstStringU8 convert_utf16_to_utf8(Allocator* allocator, StringU16 str);
ConstStringU32 convert_utf16_to_utf32(Allocator* allocator, ConstStringU16 str);
ConstStringU32 convert_utf16_to_utf32(Allocator* allocator, StringU16 str);

ConstStringU8 convert_utf32_to_utf8(Allocator* allocator, ConstStringU32 str);
ConstStringU8 convert_utf32_to_utf8(Allocator* allocator, StringU32 str);
ConstStringU16 convert_utf32_to_utf16(Allocator* allocator, ConstStringU32 str, Utf16Type type = Utf16Type_LE);
ConstStringU16 convert_utf32_to_utf16(Allocator* allocator, StringU32 str, Utf16Type type = Utf16Type_LE);

ConstStringU8 escape_as_codepoint(Allocator* allocator, ConstStringU8 str);
ConstStringU8 escape_as_codepoint(Allocator* allocator, ConstStringU16 str);
ConstStringU8 escape_as_codepoint(Allocator* allocator, ConstStringU32 str);

ConstStringU8 escape_as_bytes(Allocator* allocator, ConstStringU8 str);
ConstStringU8 escape_as_bytes(Allocator* allocator, ConstStringU16 str);
ConstStringU8 escape_as_bytes(Allocator* allocator, ConstStringU32 str);

Utf8Iterator make_utf8_iterator(ConstStringU8 string);
Utf16Iterator make_utf16_iterator(ConstStringU16 string);
Utf32Iterator make_utf32_iterator(ConstStringU32 string);

void advance(Utf8Iterator* it);
void advance(Utf16Iterator* it);
void advance(Utf32Iterator* it);

u32 get_codepoint(Utf8Iterator* it);
u32 get_codepoint(Utf16Iterator* it);
u32 get_codepoint(Utf32Iterator* it);

u32 get_codepoint_and_advance(Utf8Iterator* it);
u32 get_codepoint_and_advance(Utf16Iterator* it);
u32 get_codepoint_and_advance(Utf32Iterator* it);

bool is_valid(Utf8Iterator* it);
bool is_valid(Utf16Iterator* it);
bool is_valid(Utf32Iterator* it);

i64 find_first(ConstStringU8 str, ConstStringU8 separator);
i64 find_last(ConstStringU8 str, ConstStringU8 separator);
i64 find_next(ConstStringU8 str, ConstStringU8 separator, i64 old_result = -1);
i64 find_previous(ConstStringU8 str, ConstStringU8 separator, i64 old_result = -1);
ListU64 find_all(Allocator* allocator, ConstStringU8 str, ConstStringU8 separator);

ConstStringU8List split_string(Allocator* allocator, ConstStringU8 str, ConstStringU8 separator);
ConstStringU8Array split_string(Allocator* allocator, Arena* temporary_arena, ConstStringU8 str,
                                ConstStringU8 separator);
ConstStringU8 join_string(Allocator* allocator, ConstStringU8Array strings, ConstStringU8 separator);
ConstStringU8 trim_begin(Allocator* allocator, ConstStringU8 str);
ConstStringU8 trim_end(Allocator* allocator, ConstStringU8 str);
ConstStringU8 trim_all(Allocator* allocator, ConstStringU8 str);

ConstStringU8 replace(Allocator* allocator, Arena* temporary_arena, ConstStringU8 str, ConstStringU8 pattern,
                      ConstStringU8 replacement);

// ****************************************************************************
//                            Inline Functions
// ****************************************************************************

inline u64 string_length(const char* str) {
    const char* c = str;
    while (*c != 0) {
        c++;
    }

    return (u64)(c - str);
}

inline u64 string_length(const u16* str) {
    const u16* c = str;
    while (*c != 0) {
        c++;
    }

    return (u64)(c - str);
}

inline u64 string_length(const u32* str) {
    const u32* c = str;
    while (*c != 0) {
        c++;
    }

    return (u64)(c - str);
}

inline u16 to_big_endian(u16 value) {
    u16 low_byte = value & 0xFF;
    u16 high_byte = (value & 0xFF00) >> 8;
    value = (low_byte << 8) + high_byte;
    ;
    return value;
}

// NOTE(Corentin): for u16 it's the same
inline u16 to_little_endian(u16 value) { return to_big_endian(value); }

inline bool is_valid_utf8_code_unit_start_1(char c) { return (c & 0b10000000) == 0; }

inline bool is_valid_utf8_code_unit_start_2(char c) { return (c & 0b11100000) == 0b11000000; }

inline bool is_valid_utf8_code_unit_start_3(char c) { return (c & 0b11110000) == 0b11100000; }

inline bool is_valid_utf8_code_unit_start_4(char c) { return (c & 0b11111000) == 0b11110000; }

inline bool is_valid_utf8_continuation_code_unit(char c) { return (c & 0b11000000) == 0b10000000; }

inline bool are_valid_utf8_continuation_code_units(const char* c, u64 count) {
    bool result = true;
    for (u64 i = 0; i < count; ++i) {
        result &= is_valid_utf8_continuation_code_unit(c[i]);
    }
    return result;
}

inline bool is_valid_utf16_single_code_unit(u16 c, Utf16Type type) {
    if (type == Utf16Type_BE) {
        c = to_big_endian(c);
    }
    return (c >= 0x0000 && c <= 0xD7FF) || (c >= 0xE000 && c <= 0xFFFF);
}

inline bool is_valid_utf16_high_surrogate(u16 c, Utf16Type type) {
    if (type == Utf16Type_BE) {
        c = to_big_endian(c);
    }
    return (c & 0xFC00) == 0xD800;
}

inline bool is_valid_utf16_low_surrogate(u16 c, Utf16Type type) {
    if (type == Utf16Type_BE) {
        c = to_big_endian(c);
    }
    return (c & 0xFC00) == 0xDC00;
}

inline u64 get_codepoint_count(ConstStringU8 str) {
    Utf8Iterator it = make_utf8_iterator(str);
    while (is_valid(&it)) {
        advance(&it);
    }

    return it.codepoint_index;
}

inline u64 get_codepoint_count(ConstStringU16 str) {
    Utf16Iterator it = make_utf16_iterator(str);
    while (is_valid(&it)) {
        advance(&it);
    }

    return it.codepoint_index;
}

inline u64 get_codepoint_count(ConstStringU32 str) { return str.size; }

#endif // REBORN_STRINGS_H
