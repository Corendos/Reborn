/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#ifndef REBORN_MEMORY_ALLOCATOR_ARENA_H
#define REBORN_MEMORY_ALLOCATOR_ARENA_H

#include <reborn/memory/allocator.h>
#include <reborn/memory/arena.h>

struct ArenaData {
    Arena* arena;
    bool owned;
};

Allocator make_arena_allocator(Arena* arena = 0);
void destroy_arena_allocator(Allocator* allocator);

Allocator make_temporary_arena_allocator(Arena* arena);
void destroy_temporary_arena_allocator(Allocator* allocator);

#endif // REBORN_MEMORY_ALLOCATOR_ARENA_H
