/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#ifndef REBORN_MEMORY_PRELUDE_H
#define REBORN_MEMORY_PRELUDE_H

#include <reborn/types.h>

#define KB(x) (u64)(x) * 1024ull
#define MB(x) (u64)(x) * 1024ull * 1024ull
#define GB(x) (u64)(x) * 1024ull * 1024ull * 1024ull

#define array_size(a) sizeof(a) / sizeof(*(a))

inl void memory_copy(const void* src, void* dest, u64 count) {
    const u8* src_byte = (const u8*)src;
    u8* dest_byte = (u8*)dest;
    if (src_byte > dest_byte) {
        for (u64 i = 0; i < count; ++i) {
            *(dest_byte++) = *(src_byte++);
        }
    } else {
        for (u64 i = 0; i < count; ++i) {
            *(dest_byte + count - i - 1) = *(src_byte + count - i - 1);
        }
    }
}

inl i32 memory_compare(const void* a, const void* b, u64 count) {
    const u8* a_byte = (const u8*)a;
    const u8* b_byte = (const u8*)b;

    for (u64 i = 0; i < count; ++i) {
        i16 value = (i16) * (a_byte++) - (i16) * (b_byte++);
        if (value != 0) return value;
    }

    return 0;
}

inl void memory_set(void* dest, u8 value, u64 count) {
    u8* dest_byte = (u8*)dest;
    for (u64 i = 0; i < count; ++i) {
        *(dest_byte++) = value;
    }
}

#endif // REBORN_MEMORY_PRELUDE_H
