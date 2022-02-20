/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/math.h>
#include <reborn/memory.h>
#include <reborn/strings.h>

#include <stdio.h>

StringU8 make_string(char* str, u64 size) { return StringU8{str, size, size}; }

StringU8 make_string(char* str) { return make_string(str, string_length(str)); }

StringU16 make_string(u16* str, u64 size, Utf16Type type) { return StringU16{str, size, size, type}; }

StringU16 make_string(u16* str, Utf16Type type) { return make_string(str, string_length(str), type); }

StringU32 make_string(u32* str, u64 size) { return StringU32{str, size, size}; }

StringU32 make_string(u32* str) { return make_string(str, string_length(str)); }

ConstStringU8 make_const_string(const char* str, u64 size) { return ConstStringU8{str, size}; }

ConstStringU8 make_const_string(const char* str) { return make_const_string(str, string_length(str)); }

ConstStringU8 make_const_string(StringU8 source) { return make_const_string(source.data, source.size); }

ConstStringU16 make_const_string(const u16* str, u64 size, Utf16Type type) { return ConstStringU16{str, size, type}; }

ConstStringU16 make_const_string(const u16* str, Utf16Type type) {
    return ConstStringU16{str, string_length(str), type};
}

ConstStringU16 make_const_string(StringU16 source) { return ConstStringU16{source.data, source.size, source.type}; }

ConstStringU32 make_const_string(const u32* str, u64 size) { return ConstStringU32{str, size}; }

ConstStringU32 make_const_string(const u32* str) { return ConstStringU32{str, string_length(str)}; }

ConstStringU32 make_const_string(StringU32 source) { return ConstStringU32{source.data, source.size}; }

StringU8 make_string_from(char* data, u64 capacity) { return StringU8{data, 0, capacity - 1}; }

StringU16 make_string_from(u16* data, u64 capacity, Utf16Type type) { return StringU16{data, 0, capacity - 1, type}; }

StringU32 make_string_from(u32* data, u64 capacity) { return StringU32{data, 0, capacity - 1}; }

StringU8 push_string_u8(Allocator* allocator, const char* str, u64 size) {
    StringU8 string = {0};
    string.size = size;
    string.capacity = size;
    string.data = (char*)allocate(allocator, size + 1);
    memory_copy(str, string.data, size);
    string.data[size] = '\0';
    return string;
}

StringU8 push_string_u8(Allocator* allocator, const char* str) {
    return push_string_u8(allocator, str, string_length(str));
}

StringU8 push_string_u8(Allocator* allocator, u64 size) {
    StringU8 string = {0};
    string.size = 0;
    string.capacity = size;
    string.data = (char*)allocate(allocator, size + 1);
    string.data[size] = '\0';
    return string;
}

StringU16 push_string_u16(Allocator* allocator, const u16* str, u64 size, Utf16Type type) {
    StringU16 string = {0};
    string.size = size;
    string.capacity = size;
    string.type = type;
    string.data = (u16*)allocate(allocator, (size + 1) * sizeof(u16));
    memory_copy(str, string.data, size * sizeof(u16));
    string.data[size] = 0;
    return string;
}

StringU16 push_string_u16(Allocator* allocator, const u16* str, Utf16Type type) {
    return push_string_u16(allocator, str, string_length(str), type);
}

StringU16 push_string_u16(Allocator* allocator, u64 size, Utf16Type type) {
    StringU16 string = {0};
    string.size = 0;
    string.capacity = size;
    string.type = type;
    string.data = (u16*)allocate(allocator, (size + 1) * sizeof(u16));
    string.data[size] = 0;
    return string;
}

StringU32 push_string_u32(Allocator* allocator, const u32* str, u64 size) {
    StringU32 string = {0};
    string.size = size;
    string.capacity = size;
    string.data = (u32*)allocate(allocator, (size + 1) * sizeof(u32));
    memory_copy(str, string.data, size * sizeof(u32));
    string.data[size] = 0;
    return string;
}

StringU32 push_string_u32(Allocator* allocator, const u32* str) {
    return push_string_u32(allocator, str, string_length(str));
}

StringU32 push_string_u32(Allocator* allocator, u64 size) {
    StringU32 string = {0};
    string.size = 0;
    string.capacity = size;
    string.data = (u32*)allocate(allocator, (size + 1) * sizeof(u32));
    string.data[size] = 0;
    return string;
}

ConstStringU8 push_const_string(Allocator* allocator, const char* str, u64 size) {
    ConstStringU8 string = {0};
    string.size = size;
    char* data = (char*)allocate(allocator, size + 1);
    memory_copy(str, data, size);
    data[size] = '\0';
    string.data = data;
    return string;
}

ConstStringU8 push_const_string(Allocator* allocator, const char* str) {
    return push_const_string(allocator, str, string_length(str));
}

ConstStringU16 push_const_string(Allocator* allocator, const u16* str, u64 size, Utf16Type type) {
    ConstStringU16 string = {0};
    string.size = size;
    string.type = type;
    u16* data = (u16*)allocate(allocator, (size + 1) * sizeof(u16));
    memory_copy(str, data, size * sizeof(u16));
    data[size] = 0;
    string.data = data;
    return string;
}

ConstStringU16 push_const_string(Allocator* allocator, const u16* str, Utf16Type type) {
    return push_const_string(allocator, str, string_length(str), type);
}

ConstStringU32 push_const_string(Allocator* allocator, const u32* str, u64 size) {
    ConstStringU32 string = {0};
    string.size = size;
    u32* data = (u32*)allocate(allocator, (size + 1) * sizeof(u32));
    memory_copy(str, data, size * sizeof(u32));
    data[size] = 0;
    string.data = data;
    return string;
}

ConstStringU32 push_const_string(Allocator* allocator, const u32* str) {
    return push_const_string(allocator, str, string_length(str));
}

ConstStringU8 copy_const_string(Allocator* allocator, ConstStringU8 other) {
    return push_const_string(allocator, other.data, other.size);
}

ConstStringU16 copy_const_string(Allocator* allocator, ConstStringU16 other) {
    return push_const_string(allocator, other.data, other.size, other.type);
}

ConstStringU32 copy_const_string(Allocator* allocator, ConstStringU32 other) {
    return push_const_string(allocator, other.data, other.size);
}

StringU8 copy_string(Allocator* allocator, StringU8 other) { return push_string_u8(allocator, other.data, other.size); }

StringU16 copy_string(Allocator* allocator, StringU16 other) {
    return push_string_u16(allocator, other.data, other.size, other.type);
}

StringU32 copy_string(Allocator* allocator, StringU32 other) {
    return push_string_u32(allocator, other.data, other.size);
}

ConstStringU8 substring(ConstStringU8 str, u64 offset, i64 size) {
    u64 real_offset = min(offset, str.size);
    u64 real_size;
    if (size < 0) {
        real_size = str.size - real_offset;
    } else {
        real_size = min(str.size, real_offset + size) - real_offset;
    }
    return make_const_string(str.data + real_offset, real_size);
}

ConstStringU16 substring(ConstStringU16 str, u64 offset, i64 size) {
    u64 real_offset = min(offset, str.size);
    u64 real_size;
    if (size < 0) {
        real_size = str.size - real_offset;
    } else {
        real_size = min(str.size, real_offset + size) - real_offset;
    }
    return make_const_string(str.data + real_offset, real_size);
}

ConstStringU32 substring(ConstStringU32 str, u64 offset, i64 size) {
    u64 real_offset = min(offset, str.size);
    u64 real_size;
    if (size < 0) {
        real_size = str.size - real_offset;
    } else {
        real_size = min(str.size, real_offset + size) - real_offset;
    }
    return make_const_string(str.data + real_offset, real_size);
}

ConstStringU8ListNode* _push_const_string_list_node(Allocator* allocator, ConstStringU8 other) {
    u64 allocation_size = sizeof(ConstStringU8ListNode) + other.size + 1;
    u8* storage = (u8*)allocate(allocator, allocation_size);

    ConstStringU8ListNode* node = (ConstStringU8ListNode*)storage;
    node->next = 0;
    node->prev = 0;

    char* data = (char*)(storage + sizeof(ConstStringU8ListNode));
    memory_copy(other.data, data, other.size);
    data[other.size] = 0;

    node->string = make_const_string(data, other.size);

    return node;
}

void push_const_string_list_node(Allocator* allocator, ConstStringU8List* list, ConstStringU8 other) {
    ConstStringU8ListNode* new_node = _push_const_string_list_node(allocator, other);
    doubly_linked_list_push(list, new_node);
}

void clear_string(StringU8* str) { str->size = 0; }

void clear_string(StringU16* str) { str->size = 0; }

void clear_string(StringU32* str) { str->size = 0; }

i32 string_compare(ConstStringU8 a, ConstStringU8 b) {
    i32 sub_result = memory_compare(a.data, b.data, min(a.size, b.size));
    if (sub_result != 0 || a.size == b.size) return sub_result;
    return a.size < b.size ? -1 : 1;
}

i32 string_compare(StringU8 a, StringU8 b) { return string_compare(make_const_string(a), make_const_string(b)); }

i32 string_compare(ConstStringU8 a, StringU8 b) { return string_compare(a, make_const_string(b)); }

i32 string_compare(StringU8 a, ConstStringU8 b) { return string_compare(make_const_string(a), b); }

i32 string_compare(ConstStringU16 a, ConstStringU16 b) {
    u64 size_min = min(a.size, b.size);

    for (u64 index = 0; index < size_min; ++index) {
        u16 c_a = a.data[index];
        u16 c_b = b.data[index];
        if (c_a < c_b) {
            return -1;
        } else if (c_a > c_b) {
            return 1;
        }
    }

    if (a.size < b.size) {
        return -1;
    } else if (a.size > b.size) {
        return 1;
    }

    return 0;
}

i32 string_compare(StringU16 a, StringU16 b) { return string_compare(make_const_string(a), make_const_string(b)); }

i32 string_compare(ConstStringU16 a, StringU16 b) { return string_compare(a, make_const_string(b)); }

i32 string_compare(StringU16 a, ConstStringU16 b) { return string_compare(make_const_string(a), b); }

i32 string_compare(ConstStringU32 a, ConstStringU32 b) {
    u64 size_min = min(a.size, b.size);

    for (u64 index = 0; index < size_min; ++index) {
        u32 c_a = a.data[index];
        u32 c_b = b.data[index];
        if (c_a < c_b) {
            return -1;
        } else if (c_a > c_b) {
            return 1;
        }
    }

    if (a.size < b.size) {
        return -1;
    } else if (a.size > b.size) {
        return 1;
    }

    return 0;
}

i32 string_compare(StringU32 a, StringU32 b) { return string_compare(make_const_string(a), make_const_string(b)); }

i32 string_compare(ConstStringU32 a, StringU32 b) { return string_compare(a, make_const_string(b)); }

i32 string_compare(StringU32 a, ConstStringU32 b) { return string_compare(make_const_string(a), b); }

bool write_to(StringU8* str, char c) { return write_to(str, (u32)c); }

bool write_to(StringU8* str, u32 codepoint) {
    if (codepoint <= 0x007F) {
        if (str->size + 1 > str->capacity) return false;
        str->data[str->size++] = (u8)(codepoint & 0x7F);
    } else if (codepoint <= 0x07FF) {
        if (str->size + 2 > str->capacity) return false;
        u8 first = (u8)(codepoint & 0x3F) + 0x80;
        u8 second = (u8)((codepoint & 0x7C0) >> 6) + 0xC0;
        str->data[str->size++] = second;
        str->data[str->size++] = first;
    } else if (codepoint <= 0xFFFF) {
        if (str->size + 3 > str->capacity) return false;
        u8 first = (u8)(codepoint & 0x3F) + 0x80;
        u8 second = (u8)((codepoint & 0xFC0) >> 6) + 0x80;
        u8 third = (u8)((codepoint & 0xF000) >> 12) + 0xE0;
        str->data[str->size++] = third;
        str->data[str->size++] = second;
        str->data[str->size++] = first;
    } else if (codepoint <= 0x10FFFF) {
        if (str->size + 4 > str->capacity) return false;
        u8 first = (u8)(codepoint & 0x3F) + 0x80;
        u8 second = (u8)((codepoint & 0xFC0) >> 6) + 0x80;
        u8 third = (u8)((codepoint & 0x3F000) >> 12) + 0x80;
        u8 fourth = (u8)((codepoint & 0x1C0000) >> 18) + 0xF0;
        str->data[str->size++] = fourth;
        str->data[str->size++] = third;
        str->data[str->size++] = second;
        str->data[str->size++] = first;
    } else {
        return false;
    }

    return true;
}

bool write_to(StringU8* str, StringU8 other) { return write_to(str, make_const_string(other)); }

bool write_to(StringU8* str, ConstStringU8 other) {
    if (str->size + other.size > str->capacity) return false;
    memory_copy(other.data, str->data + str->size, other.size);
    str->size += other.size;
    return true;
}

bool write_to(StringU16* str, char c) { return write_to(str, (u32)c); }

bool write_to(StringU16* str, u32 codepoint) {
    bool is_big_endian = str->type == Utf16Type_BE;
    if (codepoint <= 0xD7FF || (codepoint >= 0xE000 && codepoint <= 0xFFFF)) {
        if (str->size + 1 > str->capacity) return false;
        u16 value = (u16)(codepoint & 0xFFFF);
        if (is_big_endian) value = to_big_endian(value);
        str->data[str->size++] = value;
    } else if (codepoint <= 0x10FFFF) {
        if (str->size + 2 > str->capacity) return false;

        u16 w1 = (u16)(((codepoint - 0x10000) & 0xFFC00) >> 10) + 0xD800;
        u16 w2 = (u16)((codepoint - 0x10000) & 0x3FF) + 0xDC00;
        if (is_big_endian) {
            w1 = to_big_endian(w1);
            w2 = to_big_endian(w2);
        }

        str->data[str->size++] = w1;
        str->data[str->size++] = w2;
    } else {
        return false;
    }

    return true;
}

bool write_to(StringU16* str, StringU16 other) { return write_to(str, make_const_string(other)); }

bool write_to(StringU16* str, ConstStringU16 other) {
    if (str->size + other.size > str->capacity) return false;

    if (str->type == other.type) {
        memory_copy(other.data, str->data + str->size * sizeof(u16), other.size * sizeof(u16));
    } else {
        u64 index = 0;
        while (index < other.size) {
            str->data[str->size++] = to_big_endian(other.data[index++]);
        }
    }

    str->size += other.size;
    return true;
}

bool write_to(StringU32* str, char c) { return write_to(str, (u32)c); }

bool write_to(StringU32* str, u32 codepoint) {
    if (str->size == str->capacity) return false;
    str->data[str->size++] = codepoint;
    return true;
}

bool write_to(StringU32* str, StringU32 other) { return write_to(str, make_const_string(other)); }

bool write_to(StringU32* str, ConstStringU32 other) {
    if (str->size + other.size > str->capacity) return false;
    memory_copy(other.data, str->data + str->size * sizeof(u32), other.size * sizeof(u32));
    str->size += other.size;
    return true;
}

FormatResult format_to(StringU8* str, const char* format, ...) {
    va_list args;
    va_start(args, format);
    FormatResult result = format_to_v(str, format, args);
    va_end(args);
    return result;
}

FormatResult format_to_v(StringU8* str, const char* format, va_list args) {
    // NOTE(Corentin): the string is allocated to have an extra '\0' at the end
    u64 remaining = str->capacity - str->size + 1;
    i64 required = (i64)vsnprintf(str->data + str->size, remaining, format, args);
    if (required < remaining) {
        str->size += required;
        return FormatResult{required, true};
    }
    // NOTE(Corentin): we discard the characters that have potentially been written already
    str->data[str->size] = 0;
    return FormatResult{required, false};
}

i64 required_for_format(const char* format, va_list args) { return (i64)vsnprintf(0, 0, format, args); }

StringBuilder make_string_builder(Arena* temporary) {
    StringBuilder builder = {0};

    builder.allocator = make_temporary_arena_allocator(temporary);

    return builder;
}

void destroy_string_builder(StringBuilder* builder) { destroy_temporary_arena_allocator(&builder->allocator); }

void format_to(StringBuilder* builder, const char* format, ...) {
    va_list args;
    va_start(args, format);
    format_to_v(builder, format, args);
    va_end(args);
}

void format_to_v(StringBuilder* builder, const char* format, va_list args) {
    va_list temp;
    va_copy(temp, args);
    FormatResult result = {0};
    if (builder->last) {
        // NOTE(Corentin): here we can try to write to the last string
        result = format_to_v(&builder->last->buffer, format, args);
    } else {
        // NOTE(Corentin): Here we just need to find the required size
        result.required = required_for_format(format, args);
    }

    // TODO(Corentin): check for zero sized strings
    if (!builder->last || !result.success) {
        u64 required_buffer_size = max(512, (u64)result.required);
        void* storage = allocate(&builder->allocator, required_buffer_size + sizeof(StringBuilderNode));
        StringBuilderNode* new_node = (StringBuilderNode*)storage;
        new_node->buffer = make_string_from((char*)storage + sizeof(StringBuilderNode), required_buffer_size);

        if (builder->last) {
            builder->last->next = new_node;
        }

        if (builder->first == 0) {
            builder->first = new_node;
        }

        builder->last = new_node;

        format_to_v(&new_node->buffer, format, args);
    }

    builder->size += (u64)result.required;

    va_end(temp);
}

ConstStringU8 build(Allocator* allocator, StringBuilder* builder) {
    StringU8 str = push_string_u8(allocator, builder->size);

    StringBuilderNode* current = builder->first;
    while (current) {
        ASSERT(write_to(&str, current->buffer));
        current = current->next;
    }

    return make_const_string(str);
}

bool is_valid_utf8(ConstStringU8 str) {
    u64 index = 0;
    while (index < str.size) {
        const char* c = str.data + index;

        if (is_valid_utf8_code_unit_start_1(*c)) {
            index++;
        } else if (is_valid_utf8_code_unit_start_2(*c)) {
            if (index + 1 >= str.size || !are_valid_utf8_continuation_code_units(c + 1, 1)) return false;
            index += 2;
        } else if (is_valid_utf8_code_unit_start_3(*c)) {
            if (index + 2 >= str.size || !are_valid_utf8_continuation_code_units(c + 1, 2)) return false;
            index += 3;
        } else if (is_valid_utf8_code_unit_start_4(*c)) {
            if (index + 3 >= str.size || !are_valid_utf8_continuation_code_units(c + 1, 3)) return false;
            index += 4;
        } else {
            return false;
        }
    }
    return true;
}

bool is_valid_utf16(ConstStringU16 str) {
    u64 index = 0;
    while (index < str.size) {
        const u16* c = str.data + index;

        if (is_valid_utf16_single_code_unit(*c, str.type)) {
            index++;
        } else if (is_valid_utf16_high_surrogate(*c, str.type)) {
            if (index + 1 >= str.size || !is_valid_utf16_low_surrogate(c[1], str.type)) return false;
            index += 2;
        } else {
            return false;
        }
    }
    return true;
}

// TODO(Corentin): implement
bool is_valid_utf32(ConstStringU8 str) { return false; }

ConstStringU16 convert_utf8_to_utf16(Allocator* allocator, ConstStringU8 str, Utf16Type type) {
    u64 codepoint_count = get_codepoint_count(str);
    // NOTE(Corentin): in the worst case, each codepoint will span 2 code units.
    u64 reserved_size = codepoint_count * 2;
    StringU16 converted_str = push_string_u16(allocator, reserved_size, type);

    Utf8Iterator it = make_utf8_iterator(str);
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        write_to(&converted_str, codepoint);
    }

    return make_const_string(converted_str);
}

ConstStringU16 convert_utf8_to_utf16(Allocator* allocator, StringU8 str, Utf16Type type) {
    return convert_utf8_to_utf16(allocator, make_const_string(str), type);
}

ConstStringU32 convert_utf8_to_utf32(Allocator* allocator, ConstStringU8 str) {
    u64 codepoint_count = get_codepoint_count(str);
    StringU32 converted_str = push_string_u32(allocator, codepoint_count);

    Utf8Iterator it = make_utf8_iterator(str);
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        write_to(&converted_str, codepoint);
    }

    return make_const_string(converted_str);
}

ConstStringU32 convert_utf8_to_utf32(Allocator* allocator, StringU8 str) {
    return convert_utf8_to_utf32(allocator, make_const_string(str));
}

ConstStringU8 convert_utf16_to_utf8(Allocator* allocator, ConstStringU16 str) {
    u64 codepoint_count = get_codepoint_count(str);
    // NOTE(Corentin): in the worst case, each codepoint will span 4 code units.
    u64 reserved_size = codepoint_count * 4;
    StringU8 converted_str = push_string_u8(allocator, reserved_size);

    Utf16Iterator it = make_utf16_iterator(str);
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        write_to(&converted_str, codepoint);
    }

    return make_const_string(converted_str);
}

ConstStringU8 convert_utf16_to_utf8(Allocator* allocator, StringU16 str) {
    return convert_utf16_to_utf8(allocator, make_const_string(str));
}

ConstStringU32 convert_utf16_to_utf32(Allocator* allocator, ConstStringU16 str) {
    u64 codepoint_count = get_codepoint_count(str);
    StringU32 converted_str = push_string_u32(allocator, codepoint_count);

    Utf16Iterator it = make_utf16_iterator(str);
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        write_to(&converted_str, codepoint);
    }

    return make_const_string(converted_str);
}

ConstStringU32 convert_utf16_to_utf32(Allocator* allocator, StringU16 str) {
    return convert_utf16_to_utf32(allocator, make_const_string(str));
}

ConstStringU8 convert_utf32_to_utf8(Allocator* allocator, ConstStringU32 str) {
    // NOTE(Corentin): in the worst case, each codepoint will span 4 code units.
    u64 reserved_size = str.size * 4;
    StringU8 converted_str = push_string_u8(allocator, reserved_size);

    Utf32Iterator it = make_utf32_iterator(str);
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        write_to(&converted_str, codepoint);
    }

    return make_const_string(converted_str);
}

ConstStringU8 convert_utf32_to_utf8(Allocator* allocator, StringU32 str) {
    return convert_utf32_to_utf8(allocator, make_const_string(str));
}

ConstStringU16 convert_utf32_to_utf16(Allocator* allocator, ConstStringU32 str, Utf16Type type) {
    // NOTE(Corentin): in the worst case, each codepoint will span 2 code units.
    u64 reserved_size = str.size * 2;
    StringU16 converted_str = push_string_u16(allocator, reserved_size, type);

    Utf32Iterator it = make_utf32_iterator(str);
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        write_to(&converted_str, codepoint);
    }

    return make_const_string(converted_str);
}

ConstStringU16 convert_utf32_to_utf16(Allocator* allocator, StringU32 str, Utf16Type type) {
    return convert_utf32_to_utf16(allocator, make_const_string(str), type);
}

ConstStringU8 escape_as_codepoint(Allocator* allocator, ConstStringU8 str) {
    u64 codepoint_count = get_codepoint_count(str);
    u64 reserved_size = codepoint_count * 11;
    StringU8 escaped_string = push_string_u8(allocator, reserved_size);

    Utf8Iterator it = make_utf8_iterator(str);
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        format_to(&escaped_string, "\\U+%08lX", codepoint);
    }

    return make_const_string(escaped_string);
}

ConstStringU8 escape_as_codepoint(Allocator* allocator, ConstStringU16 str) {
    u64 codepoint_count = get_codepoint_count(str);
    u64 reserved_size = codepoint_count * 11;
    StringU8 escaped_string = push_string_u8(allocator, reserved_size);

    Utf16Iterator it = make_utf16_iterator(str);
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        format_to(&escaped_string, "\\U+%08lX", codepoint);
    }

    return make_const_string(escaped_string);
}

ConstStringU8 escape_as_codepoint(Allocator* allocator, ConstStringU32 str) {
    u64 codepoint_count = get_codepoint_count(str);
    u64 reserved_size = codepoint_count * 11;
    StringU8 escaped_string = push_string_u8(allocator, reserved_size);

    Utf32Iterator it = make_utf32_iterator(str);
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        format_to(&escaped_string, "\\U+%08lX", codepoint);
    }

    return make_const_string(escaped_string);
}

internal ConstStringU8 escape_as_bytes(Allocator* allocator, const char* str, u64 size) {
    StringU8 escaped_string = push_string_u8(allocator, size * 4);

    for (u64 i = 0; i < size; ++i) {
        u8 value = *(u8*)(str + i);
        format_to(&escaped_string, "\\x%02X", value);
    }

    return make_const_string(escaped_string);
}

ConstStringU8 escape_as_bytes(Allocator* allocator, ConstStringU8 str) {
    return escape_as_bytes(allocator, str.data, str.size);
}

ConstStringU8 escape_as_bytes(Allocator* allocator, ConstStringU16 str) {
    return escape_as_bytes(allocator, (const char*)str.data, str.size * sizeof(u16));
}

ConstStringU8 escape_as_bytes(Allocator* allocator, ConstStringU32 str) {
    return escape_as_bytes(allocator, (const char*)str.data, str.size * sizeof(u32));
}

Utf8Iterator make_utf8_iterator(ConstStringU8 string) {
    Utf8Iterator it{string, 0, 0};
    return it;
}

Utf16Iterator make_utf16_iterator(ConstStringU16 string) {
    Utf16Iterator it{string, 0, 0};
    return it;
}

Utf32Iterator make_utf32_iterator(ConstStringU32 string) {
    Utf32Iterator it{string, 0, 0};
    return it;
}

void advance(Utf8Iterator* it) { get_codepoint_and_advance(it); }

void advance(Utf16Iterator* it) { get_codepoint_and_advance(it); }

void advance(Utf32Iterator* it) { get_codepoint_and_advance(it); }

u32 get_codepoint(Utf8Iterator* it) {
    Utf8Iterator old = *it;
    u32 codepoint = get_codepoint_and_advance(it);
    *it = old;
    return codepoint;
}

u32 get_codepoint(Utf16Iterator* it) {
    Utf16Iterator old = *it;
    u32 codepoint = get_codepoint_and_advance(it);
    *it = old;
    return codepoint;
}

u32 get_codepoint(Utf32Iterator* it) {
    Utf32Iterator old = *it;
    u32 codepoint = get_codepoint_and_advance(it);
    *it = old;
    return codepoint;
}

u32 get_codepoint_and_advance(Utf8Iterator* it) {
    if (it->position == it->string.size) return 0;

    const char* c = it->string.data + it->position;

    u32 codepoint = 0;
    if (is_valid_utf8_code_unit_start_1(*c)) {
        codepoint = *c & 0x7F;
        it->position++;
        it->codepoint_index++;
    } else if (is_valid_utf8_code_unit_start_2(*c)) {
        ASSERT(it->position + 1 < it->string.size);
        codepoint = c[1] & 0x3F;
        codepoint |= (c[0] & 0x1F) << 6;
        it->position += 2;
        it->codepoint_index++;
    } else if (is_valid_utf8_code_unit_start_3(*c)) {
        ASSERT(it->position + 2 < it->string.size);
        codepoint = c[2] & 0x3F;
        codepoint |= (c[1] & 0x3F) << 6;
        codepoint |= (c[0] & 0x0F) << 12;
        it->position += 3;
        it->codepoint_index++;
    } else if (is_valid_utf8_code_unit_start_4(*c)) {
        ASSERT(it->position + 3 < it->string.size);
        codepoint = c[3] & 0x3F;
        codepoint |= (c[2] & 0x3F) << 6;
        codepoint |= (c[1] & 0x3F) << 12;
        codepoint |= (c[0] & 0x07) << 18;
        it->position += 4;
        it->codepoint_index++;
    }

    return codepoint;
}

u32 get_codepoint_and_advance(Utf16Iterator* it) {
    if (it->position == it->string.size) return 0;
    bool is_big_endian = it->string.type == Utf16Type_BE;

    const u16* c = it->string.data + it->position;

    u32 codepoint = 0;
    if (is_valid_utf16_single_code_unit(*c, it->string.type)) {
        codepoint = is_big_endian ? (u32)to_little_endian(*c) : (u32)*c;
        it->position++;
        it->codepoint_index++;
    } else if (is_valid_utf16_high_surrogate(*c, it->string.type)) {
        u32 first = (is_big_endian ? (u32)to_little_endian(*c) : (u32)*c) & 0x3FF;
        u32 second = (is_big_endian ? (u32)to_little_endian(*(c + 1)) : (u32) * (c + 1)) & 0x3FF;
        codepoint = (first << 10) + second + 0x10000;
        it->position += 2;
        it->codepoint_index++;
    }

    return codepoint;
}

u32 get_codepoint_and_advance(Utf32Iterator* it) {
    if (it->position == it->string.size) return 0;

    u32 codepoint = it->string.data[it->position];
    it->position++;
    it->codepoint_index++;

    return codepoint;
}

// TODO(Corentin): fix that it's wrong
bool is_valid(Utf8Iterator* it) { return it->position != it->string.size; }

bool is_valid(Utf16Iterator* it) { return it->position != it->string.size; }

bool is_valid(Utf32Iterator* it) { return it->position != it->string.size; }

i64 find_first(ConstStringU8 str, ConstStringU8 separator) {
    i64 limit = str.size - separator.size;
    if (limit < 0) return -1;

    for (u64 i = 0; i <= limit; ++i) {
        ConstStringU8 candidate = substring(str, i, separator.size);
        if (string_compare(candidate, separator) == 0) return i;
    }

    return -1;
}

i64 find_last(ConstStringU8 str, ConstStringU8 separator) {
    i64 limit = str.size - separator.size;
    if (limit < 0) return -1;

    for (u64 i = 0; i <= limit; ++i) {
        u64 start = limit - i;
        ConstStringU8 candidate = substring(str, start, separator.size);
        if (string_compare(candidate, separator) == 0) return start;
    }

    return -1;
}

i64 find_next(ConstStringU8 str, ConstStringU8 separator, i64 old_result) {
    i64 start = old_result;
    if (start < 0)
        start = 0;
    else
        start += 1;

    i64 result = find_first(substring(str, start), separator);
    if (result == -1) return result;
    return result + start;
}

i64 find_previous(ConstStringU8 str, ConstStringU8 separator, i64 old_result) {
    i64 limit = 0;
    if (old_result < 0)
        limit = 0;
    else
        limit = min(str.size, old_result);

    i64 result = find_last(substring(str, 0, limit), separator);
    return result;
}

ListU64 find_all(Allocator* allocator, ConstStringU8 str, ConstStringU8 separator) {
    ListU64 result = {0};

    i64 find_result = find_next(str, separator);
    while (find_result != -1) {
        ListU64Node* new_node = (ListU64Node*)allocate(allocator, sizeof(ListU64Node));
        new_node->next = 0;
        new_node->prev = 0;
        new_node->value = (u64)find_result;

        doubly_linked_list_push(&result, new_node);
        find_result = find_next(str, separator, find_result);
    }

    return result;
}

ConstStringU8List split_string(Allocator* allocator, ConstStringU8 str, ConstStringU8 separator) {
    if (str.size == 0) return {0};

    ConstStringU8List result = {0};
    if (separator.size == 0) {
        push_const_string_list_node(allocator, &result, str);
        return result;
    }

    i64 old_result = 0;
    i64 find_result = find_next(str, separator);
    while (find_result != -1) {
        push_const_string_list_node(allocator, &result, substring(str, old_result, find_result - old_result));

        old_result = find_result + separator.size;
        find_result = find_next(str, separator, old_result);
    }

    push_const_string_list_node(allocator, &result, substring(str, old_result));

    return result;
}

ConstStringU8 join_string(Allocator* allocator, ConstStringU8Array strings, ConstStringU8 separator) {
    if (strings.count == 0) return SCu8("");

    u64 total_size = (strings.count - 1) * separator.size;
    for (u64 i = 0; i < strings.count; ++i) {
        ConstStringU8* str = strings.values + i;
        total_size += str->size;
    }

    StringU8 result = push_string_u8(allocator, total_size);
    for (u64 i = 0; i < strings.count; ++i) {
        ConstStringU8* str = strings.values + i;
        write_to(&result, *str);
        if (i < strings.count - 1) {
            write_to(&result, separator);
        }
    }

    return make_const_string(result);
}

ConstStringU8Array split_string(Allocator* allocator, Arena* temporary_arena, ConstStringU8 str,
                                ConstStringU8 separator) {
    Allocator temporary_allocator = make_temporary_arena_allocator(temporary_arena);

    ConstStringU8Array result = {0};

    ConstStringU8List temporary_result = split_string(&temporary_allocator, str, separator);
    result.count = temporary_result.count;
    result.values = (ConstStringU8*)allocate(allocator, result.count * sizeof(ConstStringU8));
    ConstStringU8ListNode* current = temporary_result.first;
    for (usize i = 0; i < result.count; ++i) {
        result.values[i] = copy_const_string(allocator, current->string);
        current = current->next;
    }

    destroy_temporary_arena_allocator(&temporary_allocator);

    return result;
}

ConstStringU8 trim_begin(Allocator* allocator, ConstStringU8 str) {
    u64 new_start = 0;

    while (new_start < str.size) {
        if (str.data[new_start] != ' ') break;
        new_start++;
    }

    return copy_const_string(allocator, substring(str, new_start));
}

ConstStringU8 trim_end(Allocator* allocator, ConstStringU8 str) {
    u64 new_start_from_end = 0;

    while (new_start_from_end < str.size) {
        if (str.data[str.size - new_start_from_end - 1] != ' ') break;
        new_start_from_end++;
    }

    return copy_const_string(allocator, substring(str, 0, str.size - new_start_from_end));
}

ConstStringU8 trim_all(Allocator* allocator, ConstStringU8 str) {
    u64 new_start = 0;

    while (new_start < str.size) {
        if (str.data[new_start] != ' ') break;
        new_start++;
    }

    return trim_end(allocator, substring(str, new_start));
}

ConstStringU8 replace(Allocator* allocator, Arena* temporary_arena, ConstStringU8 str, ConstStringU8 pattern,
                      ConstStringU8 replacement) {
    StringBuilder builder = make_string_builder(temporary_arena);

    i64 old_result = 0;
    i64 find_result = find_next(str, pattern);
    while (find_result != -1) {
        format_to(&builder, "%.*s", expand_string(substring(str, old_result, find_result - old_result)));
        format_to(&builder, "%.*s", expand_string(replacement));
        old_result = find_result + pattern.size;
        find_result = find_next(str, pattern, old_result);
    }

    format_to(&builder, "%.*s", expand_string(substring(str, old_result)));

    ConstStringU8 result = build(allocator, &builder);
    destroy_string_builder(&builder);
    return result;
}

bool contains(ConstStringU8 str, ConstStringU8 pattern) { return find_first(str, pattern) != -1; }