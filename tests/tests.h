/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#ifndef TESTS_H
#define TESTS_H

#include <reborn/types.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define _STRINGIFY(s) #s
#define STRINGIFY(s)  _STRINGIFY(s)
#define CONCAT(a, b)  a##b

#define GREEN_OUTPUT                                                                                                   \
    "\x1b\x5b"                                                                                                         \
    "32m"
#define RED_OUTPUT                                                                                                     \
    "\x1b\x5b"                                                                                                         \
    "31m"
#define DEFAULT_OUTPUT                                                                                                 \
    "\x1b\x5b"                                                                                                         \
    "0m"

#define GREEN_FG(text)                                                                                                 \
    "\x1b\x5b"                                                                                                         \
    "32m" text "\x1b\x5b"                                                                                              \
    "0m"
#define RED_FG(text)                                                                                                   \
    "\x1b\x5b"                                                                                                         \
    "31m" text "\x1b\x5b"                                                                                              \
    "0m"

static const int INDENT_SIZE = 2;
static const int LINE_LENGTH = 120;

struct TestContext {
    int assertion_run_count;
    int test_run_count;
    int test_success_count;
    int test_failure_count;
    int indent_level;
};

static TestContext _testing_context = {0};

static const char success_str[] = "\x1b\x5b"
                                  "32m"
                                  "S"
                                  "\x1b\x5b"
                                  "0m";
static const char failure_str[] = "\x1b\x5b"
                                  "31m"
                                  "F"
                                  "\x1b\x5b"
                                  "0m";

static void print_test_report(char* buffer, u64 buffer_length, char* test_message, u64 test_message_length,
                              u64 line_length, u64 indent_level, bool test_success) {
    assert(buffer_length > line_length);
    memset(buffer, 0, buffer_length);

    i64 space_needed = (i64)line_length - 2 - (i64)indent_level - (i64)test_message_length;
    bool need_ellipsis = false;
    i64 max_message_length = test_message_length;
    if (space_needed < 0) {
        max_message_length = (i64)line_length - 2 - (i64)indent_level - 3;
        max_message_length = max_message_length < 0 ? 0 : max_message_length;
        space_needed = 0;
        need_ellipsis = true;
    }

    char* current = buffer;

    memset(current, ' ', indent_level);
    current += indent_level;
    memcpy(current, test_message, max_message_length);
    current += max_message_length;
    if (need_ellipsis) {
        memset(current, '.', 3);
        current += 3;
    } else {
        memset(current, '.', space_needed);
        current += space_needed;
    }
    *current = 0;
    assert(current - buffer < buffer_length);
    printf("%s %s\n", buffer, test_success ? success_str : failure_str);
}

#define CHECK(message, test)                                                                                           \
    do {                                                                                                               \
        bool success = test;                                                                                           \
        _testing_context.assertion_run_count++;                                                                        \
        char temp_buffer_format[1024] = {0};                                                                           \
        print_test_report(temp_buffer_format, 1024, message, strlen(message), LINE_LENGTH,                             \
                          _testing_context.indent_level, success);                                                     \
        _test_framework_result = _test_framework_result && success;                                                    \
    } while (0)

#define REQUIRE(message, test)                                                                                         \
    do {                                                                                                               \
        bool success = test;                                                                                           \
        _testing_context.assertion_run_count++;                                                                        \
        char temp_buffer_format[1024] = {0};                                                                           \
        print_test_report(temp_buffer_format, 1024, message, strlen(message), LINE_LENGTH,                             \
                          _testing_context.indent_level, success);                                                     \
        _test_framework_result = _test_framework_result && success;                                                    \
        if (!success) return;                                                                                          \
    } while (0)

#define CONSTRAINT(test)                                                                                               \
    do {                                                                                                               \
        bool success = test;                                                                                           \
        if (!success) {                                                                                                \
            printf("\x1b\x5b"                                                                                          \
                   "31m"                                                                                               \
                   "!!!"                                                                                               \
                   "\x1b\x5b"                                                                                          \
                   "0m"                                                                                                \
                   " Error, test constraint '%s' is false, aborting this test\n",                                      \
                   STRINGIFY(test));                                                                                   \
            _test_framework_result = false;                                                                            \
            return;                                                                                                    \
        }                                                                                                              \
    } while (0)

#define TEST_CASE(test_name)                                                                                           \
    void CONCAT(test_name, _case_proxy)(bool& _test_framework_result);                                                 \
    bool CONCAT(test_name, _func)() {                                                                                  \
        bool _test_framework_result = true;                                                                            \
        CONCAT(test_name, _case_proxy)(_test_framework_result);                                                        \
        _testing_context.test_run_count++;                                                                             \
        if (_test_framework_result) {                                                                                  \
            _testing_context.test_success_count++;                                                                     \
        } else {                                                                                                       \
            _testing_context.test_failure_count++;                                                                     \
        }                                                                                                              \
        return _test_framework_result;                                                                                 \
    }                                                                                                                  \
    void CONCAT(test_name, _case_proxy)(bool& _test_framework_result)

#define SECTION(section_name)                                                                                          \
    void CONCAT(section_name, _section_proxy)(bool& _section_framework_result);                                        \
    bool CONCAT(section_name, _func)() {                                                                               \
        bool _section_framework_result = true;                                                                         \
        CONCAT(section_name, _section_proxy)(_section_framework_result);                                               \
        return _section_framework_result;                                                                              \
    }                                                                                                                  \
    void CONCAT(section_name, _section_proxy)(bool& _section_framework_result)

void _run_test(const char* test_name, const char* prefix, bool& result, bool (*test_func)(void)) {
    printf("%*s%s: \"%s\"\n", _testing_context.indent_level, "", prefix, test_name);
    _testing_context.indent_level += INDENT_SIZE;
    bool success = test_func();
    _testing_context.indent_level -= INDENT_SIZE;
    result = result && success;
}

#define RUN_TEST_CASE(test)                                                                                            \
    do {                                                                                                               \
        const char test_name[] = STRINGIFY(test);                                                                      \
        _run_test(test_name, "Test", _section_framework_result, CONCAT(test, _func));                                  \
    } while (0)

#define RUN_SECTION(test)                                                                                              \
    do {                                                                                                               \
        const char test_name[] = STRINGIFY(test);                                                                      \
        _run_test(test_name, "Section", _section_framework_result, CONCAT(test, _func));                               \
    } while (0)

#endif // TESTS_H
