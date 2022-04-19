/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/concurrency/condition_variable.h>
#include <reborn/concurrency/thread.h>

TEST_CASE(condition_variable_creation_destruction) {
    ConditionVariable condition_variable = make_condition_variable();
    delete_condition_variable(&condition_variable);
    CHECK("The creation and destruction should be successful", true);
}

struct ConditionVariableUsageContext {
    Mutex mutex;
    ConditionVariable condition_variable;
    bool thread_awaken;
};

u64 cv_thread_func(void* parameters) {
    ConditionVariableUsageContext* context = (ConditionVariableUsageContext*)parameters;
    
    acquire_mutex(&context->mutex);
    wait_condition_variable(&context->condition_variable, &context->mutex);
    
    context->thread_awaken = true;
    
    return 0;
}

TEST_CASE(condition_variable_usage_1) {
    ConditionVariableUsageContext context = {0};
    context.mutex = make_mutex();
    context.condition_variable = make_condition_variable();
    
    ConstStringU8 thread_name = SCu8("Awaken Thread");
    Thread thread = make_thread(thread_name, cv_thread_func, &context);
    
    Sleep(50);
    notify_one_condition_variable(&context.condition_variable);
    Sleep(50);
    
    CHECK("The thread should have been awaken", context.thread_awaken);
    
    join_thread(&thread);
    
    delete_condition_variable(&context.condition_variable);
    delete_mutex(&context.mutex);
}

TEST_CASE(condition_variable_usage_2) {
    ConditionVariableUsageContext context = {0};
    context.mutex = make_mutex();
    context.condition_variable = make_condition_variable();
    
    ConstStringU8 thread_name = SCu8("Not Awaken Thread");
    Thread thread = make_thread(thread_name, cv_thread_func, &context);
    
    CHECK("The thread should not have been awaken", context.thread_awaken == false);
    
    Sleep(50);
    notify_one_condition_variable(&context.condition_variable);
    Sleep(50);
    
    join_thread(&thread);
    
    delete_condition_variable(&context.condition_variable);
    delete_mutex(&context.mutex);
}

// TODO(Corentin): add a test for multiple notify

SECTION(condition_variable) {
    RUN_TEST_CASE(condition_variable_creation_destruction);
    RUN_TEST_CASE(condition_variable_usage_1);
    RUN_TEST_CASE(condition_variable_usage_2);
}
