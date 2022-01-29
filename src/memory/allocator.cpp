/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/memory/allocator.h>

void* allocate(Allocator* allocator, u64 size) {
    if (allocator->allocate_func == 0 || allocator->user_data == 0) return 0;
    return allocator->allocate_func(size, 0, allocator->user_data);
}

void free(Allocator* allocator, void* data) {
    if (allocator->free_func == 0 || allocator->user_data == 0) return;
    allocator->free_func(data, allocator->user_data);
}
