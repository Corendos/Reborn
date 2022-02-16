/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#ifndef REBORN_MEMORY_BUFFER_H
#define REBORN_MEMORY_BUFFER_H

#include <reborn/memory/allocator.h>
#include <reborn/memory/prelude.h>

struct ConstBuffer {
    const u8* data;
    u64 size;
};

struct Buffer {
    u8* data;
    u64 size;
    u64 capacity;
};

ConstBuffer make_const_buffer(const u8* data, u64 size);
ConstBuffer make_const_buffer(Buffer buffer);
ConstBuffer copy_const_buffer(Allocator* allocator, ConstBuffer source);
Buffer copy_buffer(Allocator* allocator, ConstBuffer source);
bool copy_buffer(Buffer* dest, ConstBuffer source);
Buffer push_buffer(Allocator* allocator, u64 size);
void reset_buffer(Buffer* buffer);

// NOTE(Corentin): Temporary
void print_buffer_hex(ConstBuffer buffer, Arena* temporary_arena);

#endif // REBORN_MEMORY_BUFFER_H
