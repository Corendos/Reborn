/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/io.h>

#define STB_SPRINTF_IMPLEMENTATION
#include <stb_sprintf.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

struct PrintContext {
    FILE* output;
    char* buffer;
};

char* print_callback(const char* buffer, void* user, int len) {
    PrintContext* ctx = (PrintContext*)user;
    fwrite(buffer, 1, len, ctx->output);
    return ctx->buffer;
}

void print(const char* format, ...) {
    char temp[STB_SPRINTF_MIN];
    PrintContext ctx = {stdout, temp};
    va_list args;
    va_start(args, format);
    stbsp_vsprintfcb(print_callback, &ctx, temp, format, args);
    va_end(args);
}

void println(const char* format, ...) {
    char temp[STB_SPRINTF_MIN];
    PrintContext ctx = {stdout, temp};
    va_list args;
    va_start(args, format);
    stbsp_vsprintfcb(print_callback, &ctx, temp, format, args);
    fputc('\n', stdout);
    va_end(args);
}

void eprint(const char* format, ...) {
    char temp[STB_SPRINTF_MIN];
    PrintContext ctx = {stderr, temp};
    va_list args;
    va_start(args, format);
    stbsp_vsprintfcb(print_callback, &ctx, temp, format, args);
    va_end(args);
}

void eprintln(const char* format, ...) {
    char temp[STB_SPRINTF_MIN];
    PrintContext ctx = {stderr, temp};
    va_list args;
    va_start(args, format);
    stbsp_vsprintfcb(print_callback, &ctx, temp, format, args);
    fputc('\n', stdout);
    va_end(args);
}

void set_separator(char comma, char period) { stbsp_set_separators(comma, period); }