/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/concurrency/condition_variable.h>

ConditionVariable make_condition_variable() {
    ConditionVariable condition_variable = {0};
    
    condition_variable.native_handle.cv = CONDITION_VARIABLE_INIT;
    
    return condition_variable;
}

void delete_condition_variable(ConditionVariable* condition_variable) {
    *condition_variable = {0};
}

void notify_one_condition_variable(ConditionVariable* condition_variable) {
    WakeConditionVariable(&condition_variable->native_handle.cv);
}

void notify_all_condition_variable(ConditionVariable* condition_variable) {
    WakeAllConditionVariable(&condition_variable->native_handle.cv);
}

void wait_condition_variable(ConditionVariable* condition_variable, Mutex* mutex) {
    ASSERT(SleepConditionVariableCS(&condition_variable->native_handle.cv, &mutex->native_handle.cs, INFINITE) != 0);
}
