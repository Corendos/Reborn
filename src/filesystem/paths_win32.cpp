/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/characters.h>
#include <reborn/filesystem/paths.h>

#include <windows.h>

ConstStringU8 get_current_working_directory(Allocator* allocator) {
    DWORD required_buffer_size = GetCurrentDirectory(0, 0);
    StringU8 buffer = push_string_u8(allocator, (u64)required_buffer_size);
    GetCurrentDirectory(buffer.capacity + 1, (TCHAR*)buffer.data);
    buffer.size = (u64)required_buffer_size;

    return make_const_string(buffer);
}

ConstStringU8 get_executable_path(Allocator* allocator) {
    u64 capacity = 256;
    char* raw_filepath = (char*)allocate(allocator, capacity);
    u64 size = GetModuleFileNameA(NULL, raw_filepath, capacity - 1);
    return make_const_string(raw_filepath, size);
}

bool change_directory(ConstStringU8 path) { return SetCurrentDirectory(path.data) != 0; }

ConstStringU8 join_paths(ConstStringU8Array paths) { return {0}; }

bool is_directory(ConstStringU8 path) {
    DWORD attributes = GetFileAttributesA(path.data);
    return attributes & FILE_ATTRIBUTE_DIRECTORY;
}

bool is_file(ConstStringU8 path) {
    DWORD attributes = GetFileAttributesA(path.data);
    return attributes & FILE_ATTRIBUTE_NORMAL;
}

bool is_absolute(ConstStringU8 path) {
#if 0
    // NOTE(Corentin): this is ambiguous as it is considered as absolute for Windows, but not
    //                 really since it depends on the current active disk
    if (path.size < 1) return false;
    if (!is_alpha(path.data[0])) {
        if (path.data[0] == '\\') return true;
        return false;
    }
#endif
    if (path.size < 3) return false;
    if (!is_alpha(path.data[0])) return false;
    if (path.data[1] != ':') return false;
    if (path.data[2] != '/' && path.data[2] != '\\') return false;
    return true;
}

bool is_relative(ConstStringU8 path) { return !is_absolute(path); }

bool exists(ConstStringU8 path) {
    DWORD attributes = GetFileAttributesA(path.data);
    return attributes != INVALID_FILE_ATTRIBUTES;
}

SizeResult get_size(ConstStringU8 path) { return {0}; }

ConstStringU8Result get_absolute_path(Allocator* allocator, ConstStringU8 path) { return {0}; }

ConstStringU8Result get_base_name(Allocator* allocator, ConstStringU8 path) { return {0}; }

ConstStringU8Result get_common_path(Allocator* allocator, ConstStringU8Array paths) { return {0}; }

ConstStringU8Result get_common_prefix(Allocator* allocator, ConstStringU8Array paths) { return {0}; }

ConstStringU8 get_directory_name(Allocator* allocator, ConstStringU8 path) {
    i64 last_slash = find_last(path, SCu8("\\"));
    if (last_slash == -1) {
        last_slash = find_last(path, SCu8("/"));
    }

    if (last_slash == -1) return copy_const_string(allocator, SCu8(""));

    return copy_const_string(allocator, substring(path, 0, last_slash));
}