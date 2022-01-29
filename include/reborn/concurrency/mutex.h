/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#ifndef REBORN_CONCURRENCY_MUTEX_H
#define REBORN_CONCURRENCY_MUTEX_H

#include <reborn/types.h>

#if defined(OS_WINDOWS)
#include "mutex_win32.h"
#else
#error "No implementation for type Mutex"
#endif

struct Mutex {
    NativeMutex native_handle;
};

Mutex make_mutex();
void delete_mutex(Mutex* mutex);
void acquire_mutex(Mutex* mutex);
bool try_acquire_mutex(Mutex* mutex);
void release_mutex(Mutex* mutex);

#endif // REBORN_CONCURRENCY_MUTEX_H
