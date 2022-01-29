/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#ifndef REBORN_PATHS_H
#define REBORN_PATHS_H

#include <reborn/memory.h>
#include <reborn/strings.h>

ConstStringU8 get_current_working_directory(Allocator* allocator);
bool change_directory(ConstStringU8 path);

ConstStringU8 join_paths(ConstStringU8Array paths);

bool is_directory(ConstStringU8 path);
bool is_file(ConstStringU8 path);

#endif // REBORN_PATHS_H
