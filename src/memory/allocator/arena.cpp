/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/memory/allocator/arena.h>

#include <stdlib.h>

void* _arena_allocation_func(u64 size, u8 alignment, void* user_data) {
    ArenaData* data = (ArenaData*)user_data;

    return linear_allocation_push(data->arena, size);
}

Allocator make_arena_allocator(Arena* arena) {
    ArenaData* data = 0;

    if (arena == 0) {
        u8* storage = (u8*)calloc(1, sizeof(ArenaData) + sizeof(Arena));
        data = (ArenaData*)storage;
        data->owned = true;
        // NOTE(Corentin): is it good to rely on malloc here ?
        data->arena = (Arena*)(storage + sizeof(ArenaData));
        *data->arena = make_arena();
    } else {
        data = (ArenaData*)calloc(1, sizeof(ArenaData));
        data->owned = false;
        data->arena = arena;
    }

    Allocator allocator = {0};
    allocator.allocate_func = _arena_allocation_func;
    // NOTE(Corentin): with an arena, we do nothing on free
    allocator.free_func = 0;
    allocator.user_data = data;

    return allocator;
}

void destroy_arena_allocator(Allocator* allocator) {
    ArenaData* data = (ArenaData*)allocator->user_data;
    destroy_arena(data->arena);
    free(allocator->user_data);
    *allocator = {0};
}

void* _temporary_arena_allocation_func(u64 size, u8 alignment, void* user_data) {
    // NOTE(Corentin): Here we want to retrieve an arena
    TemporaryArena* temp = (TemporaryArena*)user_data;

    return linear_allocation_push(temp->arena, size);
}

Allocator make_temporary_arena_allocator(Arena* arena) {
    TemporaryArena* temp = (TemporaryArena*)calloc(1, sizeof(TemporaryArena));
    *temp = linear_allocation_begin_temp(arena);

    Allocator allocator = {0};
    allocator.user_data = temp;
    allocator.allocate_func = _arena_allocation_func;
    // NOTE(Corentin): with an arena, we do nothing on free
    allocator.free_func = 0;

    return allocator;
}

void destroy_temporary_arena_allocator(Allocator* allocator) {
    TemporaryArena* temp = (TemporaryArena*)allocator->user_data;
    linear_allocation_end_temp(temp);
    free(allocator->user_data);
    *allocator = {0};
}