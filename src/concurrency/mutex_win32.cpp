/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/concurrency/mutex.h>

Mutex make_mutex() {
    Mutex mutex = {0};

    InitializeCriticalSection(&mutex.native_handle.cs);

    return mutex;
}

void delete_mutex(Mutex* mutex) { DeleteCriticalSection(&mutex->native_handle.cs); }

void acquire_mutex(Mutex* mutex) { EnterCriticalSection(&mutex->native_handle.cs); }

bool try_acquire_mutex(Mutex* mutex) { return TryEnterCriticalSection(&mutex->native_handle.cs) != 0; }

void release_mutex(Mutex* mutex) { LeaveCriticalSection(&mutex->native_handle.cs); }
