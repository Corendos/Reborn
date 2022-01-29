/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#ifndef REBORN_MEMORY_ARENA_H
#define REBORN_MEMORY_ARENA_H

#include <reborn/memory/prelude.h>

struct Cursor {
    u8* data;
    u64 pos;
    u64 capacity;
};

struct TemporaryCursor {
    Cursor* cursor;
    u64 pos;
};

struct CursorNode {
    union {
        CursorNode* next;
        CursorNode* prev;
    };
    Cursor cursor;
};

struct Arena {
    CursorNode* cursor_node;
    u64 node_size;
    u8 alignment;
};

struct TemporaryArena {
    Arena* arena;
    CursorNode* cursor_node;
    u64 pos;
};

Cursor make_cursor(u8* data, u64 capacity);

void* linear_allocation_push(Cursor* cursor, u64 size);
void linear_allocation_pop(Cursor* cursor, u64 size);
TemporaryCursor linear_allocation_begin_temp(Cursor* cursor);
void linear_allocation_end_temp(TemporaryCursor* temporary);

Arena make_arena(u64 node_size, u8 alignment);
Arena make_arena(u64 node_size);
Arena make_arena();
void destroy_arena(Arena* arena);
void reset_arena(Arena* arena);

void* linear_allocation_push(Arena* arena, u64 size);
void linear_allocation_pop(Arena* arena, u64 size);
TemporaryArena linear_allocation_begin_temp(Arena* arena);
void linear_allocation_end_temp(TemporaryArena* temporary);

#endif // REBORN_MEMORY_ARENA_H
