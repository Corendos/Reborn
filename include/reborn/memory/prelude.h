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

#endif // REBORN_MEMORY_PRELUDE_H
