/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#ifndef REBORN_IO_H
#define REBORN_IO_H

#include <reborn/types.h>

void print(const char* format, ...);
void println(const char* format, ...);

void eprint(const char* format, ...);
void eprintln(const char* format, ...);

void set_separator(char comma, char period);

#endif // IO_H
