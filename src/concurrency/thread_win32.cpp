/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/concurrency/thread.h>

struct ThreadContext {
    u64 (*thread_func)(void*);
    void* parameters;
};

DWORD WINAPI default_thread_start_trampoline(void* parameters) {
    ThreadContext* context = (ThreadContext*)parameters;
    DWORD result = (DWORD)context->thread_func(context->parameters);
    free(context);
    return result;
}

// TODO(Corentin): use SetThreadDescription to set thread name
NativeThread make_native_thread(ConstStringU8 name, u64 (*thread_func)(void*), void* parameters) {
    NativeThread native_thread = {0};
    SECURITY_ATTRIBUTES security_attributes = {0};
    security_attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    security_attributes.lpSecurityDescriptor = 0;
    security_attributes.bInheritHandle = FALSE;

    ThreadContext* context = (ThreadContext*)calloc(1, sizeof(ThreadContext));
    context->thread_func = thread_func;
    context->parameters = parameters;

    HANDLE thread_handle =
        CreateThread(&security_attributes, 0, default_thread_start_trampoline, context, 0, &native_thread.id);

    native_thread.handle = thread_handle;
    return native_thread;
}

Thread make_thread(ConstStringU8 name, u64 (*thread_fun)(void*), void* parameters) {
    Thread result = {0};
    char* data = (char*)malloc(name.size + 1);
    result.name = make_string_from(data, name.size + 1);
    write_to(&result.name, name);
    result.native_handle = make_native_thread(name, thread_fun, parameters);

    return result;
}

void join_thread(Thread* thread) {
    WaitForSingleObject(thread->native_handle.handle, INFINITE);
    CloseHandle(thread->native_handle.handle);
    free(thread->name.data);
    thread->name.size = 0;
    thread->name.capacity = 0;
}

// TODO(Corentin): does that make sense ?
bool is_thread_joinable(Thread* thread) { return false; }

void detach_thread(Thread* thread) {}