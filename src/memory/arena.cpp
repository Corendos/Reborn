/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/math.h>
#include <reborn/memory/arena.h>

#include <stdlib.h>

Cursor make_cursor(u8* data, u64 capacity) {
    Cursor cursor = {0};

    cursor.data = data;
    cursor.capacity = capacity;

    return cursor;
}

void* linear_allocation_push(Cursor* cursor, u64 size) {
    u8* result = 0;

    if (cursor->pos + size <= cursor->capacity) {
        result = cursor->data + cursor->pos;
        cursor->pos += size;
    }

    return result;
}

void linear_allocation_pop(Cursor* cursor, u64 size) {
    if (cursor->pos > size) {
        cursor->pos -= size;
    } else {
        cursor->pos = 0;
    }
}

TemporaryCursor linear_allocation_begin_temp(Cursor* cursor) {
    TemporaryCursor temporary = {0};

    temporary.cursor = cursor;
    temporary.pos = cursor->pos;

    return temporary;
}

void linear_allocation_end_temp(TemporaryCursor* temporary) { temporary->cursor->pos = temporary->pos; }

Arena make_arena(u64 node_size, u8 alignment) {
    ASSERT(is_power_of_two(alignment));
    Arena arena = {0};

    arena.node_size = node_size;
    arena.alignment = alignment;

    return arena;
}

Arena make_arena(u64 node_size) { return make_arena(node_size, 8); }

Arena make_arena() { return make_arena(KB(4)); }

void destroy_arena(Arena* arena) {
    TemporaryArena temp = {arena, 0, 0};
    linear_allocation_end_temp(&temp);
}

void reset_arena(Arena* arena) {
    TemporaryArena temp = {arena, 0, 0};
    linear_allocation_end_temp(&temp);
}

CursorNode* __arena_allocate_node(Arena* arena, u64 min_size) {
    u64 storage_size = max(min_size, arena->node_size);
    u64 aligned_cursor_node_size = align_to(sizeof(CursorNode), arena->alignment);
    u8* storage = (u8*)calloc(1, aligned_cursor_node_size + storage_size);
    CursorNode* node = (CursorNode*)storage;
    node->cursor = make_cursor(storage + aligned_cursor_node_size, storage_size);
    single_linked_list_stack_push(arena->cursor_node, node);
    return node;
}

void* linear_allocation_push(Arena* arena, u64 size) {
    u8* result = 0;

    if (size > 0) {
        u64 aligned_size = align_to(size, arena->alignment);
        CursorNode* node = arena->cursor_node;
        if (node == 0) {
            node = __arena_allocate_node(arena, aligned_size);
        }

        result = (u8*)linear_allocation_push(&node->cursor, aligned_size);
        if (result == 0) {
            node = __arena_allocate_node(arena, aligned_size);
            result = (u8*)linear_allocation_push(&node->cursor, aligned_size);
        }
    }

    return result;
}

void linear_allocation_pop(Arena* arena, u64 size) {
    if (size > 0) {
        CursorNode* node = arena->cursor_node;
        if (node) {
            linear_allocation_pop(&node->cursor, size);
            if (node->cursor.pos == 0) {
                void* old_node = node;
                single_linked_list_stack_pop(arena->cursor_node);
                free(old_node);
            }
        }
    }
}

TemporaryArena linear_allocation_begin_temp(Arena* arena) {
    TemporaryArena temporary = {0};

    temporary.arena = arena;
    temporary.cursor_node = arena->cursor_node;
    if (temporary.cursor_node != 0) {
        temporary.pos = temporary.cursor_node->cursor.pos;
    }

    return temporary;
}

void linear_allocation_end_temp(TemporaryArena* temporary) {
    CursorNode* current_node = temporary->arena->cursor_node;
    while (current_node != temporary->cursor_node && current_node != 0) {
        CursorNode* prev = current_node->prev;
        free(current_node);
        current_node = prev;
    }

    temporary->arena->cursor_node = current_node;

    if (current_node != 0) {
        if (temporary->pos > 0) {
            current_node->cursor.pos = temporary->pos;
        } else {
            void* old_node = current_node;
            single_linked_list_stack_pop(temporary->arena->cursor_node);
            free(old_node);
        }
    }
}
