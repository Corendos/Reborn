/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/concurrency/thread_win32.h>

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
NativeThread _make_thread(ConstStringU8 name, u64 (*thread_func)(void*), void* parameters) {
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

void _join_thread(NativeThread* thread) { WaitForSingleObject(thread->handle, INFINITE); }

// TODO(Corentin): does that make sense ?
bool _is_thread_joinable(NativeThread* thread) { return false; }

void _detach_thread(NativeThread* thread) {}