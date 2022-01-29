/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#ifndef REBORN_MEMORY_ALLOCATOR_H
#define REBORN_MEMORY_ALLOCATOR_H

#include <reborn/memory/prelude.h>

struct Allocator {
    void* (*allocate_func)(u64 /* size */, u8 /* alignment */, void* /* user_data */);
    void (*free_func)(void* /* data */, void* /* user_data */);
    void* user_data;
};

void* allocate(Allocator* allocator, u64 size);
void free(Allocator* allocator, void* data);

#endif // REBORN_MEMORY_ALLOCATOR_H
