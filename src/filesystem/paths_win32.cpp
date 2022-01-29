/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/filesystem/paths.h>

#include <windows.h>

ConstStringU8 get_current_working_directory(Allocator* allocator) {
    DWORD required_buffer_size = GetCurrentDirectory(0, 0);
    StringU8 buffer = push_string_u8(allocator, (u64)required_buffer_size);
    GetCurrentDirectory(buffer.capacity + 1, (TCHAR*)buffer.data);
    buffer.size = (u64)required_buffer_size;

    return make_const_string(buffer);
}

bool change_directory(ConstStringU8 path) { return SetCurrentDirectory(path.data) != 0; }

ConstStringU8 join_paths(ConstStringU8Array paths) { return {0}; }

bool is_directory(ConstStringU8 path) { return false; }

bool is_file(ConstStringU8 path) { return false; }
