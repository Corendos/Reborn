/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/concurrency/thread.h>

Thread make_thread(ConstStringU8 name, u64 (*thread_fun)(void*), void* parameters) {
    Thread result = {0};
    char* data = (char*)malloc(name.size + 1);
    result.name = make_string_from(data, name.size);
    write_to(&result.name, name);
    result.native_handle = _make_thread(name, thread_fun, parameters);

    return result;
}

void join_thread(Thread* thread) {
    _join_thread(&thread->native_handle);
    free(thread->name.data);
    thread->name.size = 0;
    thread->name.capacity = 0;
}

bool is_thread_joinable(Thread* thread) { return _is_thread_joinable(&thread->native_handle); }

void detach_thread(Thread* thread) { _detach_thread(&thread->native_handle); }
