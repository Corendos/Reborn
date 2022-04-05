/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/concurrency/mutex.h>
#include <reborn/concurrency/thread.h>

TEST_CASE(mutex_creation_destruction) {
    Mutex mutex = make_mutex();
    delete_mutex(&mutex);
    CHECK("The creation and destruction should be successful", true);
}

struct MutexUsageContext {
    Mutex mutex;
    bool thread1_acquired_lock;
    bool thread2_failed_to_acquire_lock;
};

u64 locking_thread_func(void* parameters) {
    MutexUsageContext* context = (MutexUsageContext*)parameters;
    context->thread1_acquired_lock = try_acquire_mutex(&context->mutex);
    // TODO(Corentin): implement agnostic version of this
    Sleep(100);
    release_mutex(&context->mutex);

    return 0;
}

u64 failing_to_lock_thread_func(void* parameters) {
    MutexUsageContext* context = (MutexUsageContext*)parameters;
    Sleep(50);
    context->thread2_failed_to_acquire_lock = !try_acquire_mutex(&context->mutex);
    return 0;
}

TEST_CASE(mutex_usage) {
    MutexUsageContext context = {0};
    context.mutex = make_mutex();

    ConstStringU8 thread1_name = SCu8("Thread 1");
    Thread t1 = make_thread(thread1_name, locking_thread_func, &context);
    ConstStringU8 thread2_name = SCu8("Thread 2");
    Thread t2 = make_thread(thread2_name, failing_to_lock_thread_func, &context);

    join_thread(&t1);
    join_thread(&t2);

    CHECK("The thread 1 should have succeeded to acquire the mutex", context.thread1_acquired_lock);
    CHECK("The thread 2 should have failed to acquire the mutex", context.thread2_failed_to_acquire_lock);

    delete_mutex(&context.mutex);
}

SECTION(mutex) {
    RUN_TEST_CASE(mutex_creation_destruction);
    RUN_TEST_CASE(mutex_usage);
}
