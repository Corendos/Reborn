/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/memory/allocator/arena.h>
#include <reborn/memory/buffer.h>
#include <reborn/strings.h>

#include <stdio.h>

ConstBuffer make_const_buffer(const u8* data, u64 size) { return ConstBuffer{data, size}; }

ConstBuffer make_const_buffer(Buffer buffer) { return make_const_buffer(buffer.data, buffer.size); }

ConstBuffer copy_const_buffer(Allocator* allocator, ConstBuffer source) {
    return make_const_buffer(copy_buffer(allocator, source));
}

Buffer copy_buffer(Allocator* allocator, ConstBuffer source) {
    Buffer buffer = push_buffer(allocator, source.size);
    ASSERT(copy_buffer(&buffer, source));
    return buffer;
}

bool copy_buffer(Buffer* dest, ConstBuffer source) {
    if (dest->capacity - dest->size < source.size) return false;
    memory_copy(source.data, dest->data + dest->size, source.size);
    dest->size += source.size;
    return true;
}

Buffer push_buffer(Allocator* allocator, u64 size) {
    Buffer buffer = {0, 0, size};
    buffer.data = (u8*)allocate(allocator, size);
    return buffer;
}

void reset_buffer(Buffer* buffer) { buffer->size = 0; }

void print_buffer_hex(ConstBuffer buffer, Arena* temporary_arena) {
    StringBuilder builder = make_string_builder(temporary_arena);

    for (u64 i = 0; i < buffer.size; ++i) {
        format_to(&builder, "\\x%02X", buffer.data[i]);
    }

    Allocator temp = make_temporary_arena_allocator(temporary_arena);
    ConstStringU8 str = build(&temp, &builder);

    printf("%.*s\n", expand_string(str));

    destroy_arena_allocator(&temp);
    destroy_string_builder(&builder);
}
