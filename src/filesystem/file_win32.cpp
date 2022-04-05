/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/filesystem/file.h>
#include <reborn/memory/allocator/arena.h>

#include <windows.h>

internal inl DWORD translate_file_access_mode(FileAccessMode access_mode) {
    DWORD result = 0;
    if (access_mode & FileAccessMode_Read) result |= GENERIC_READ;
    if (access_mode & FileAccessMode_Write) result |= GENERIC_WRITE;
    return result;
}

internal inl DWORD translate_file_open_option(FileOpenOption options) {
    DWORD result = 0;

    switch (options) {
    case FileOpenOption_CreateAlways: result = CREATE_ALWAYS; break;
    case FileOpenOption_CreateNew: result = CREATE_NEW; break;
    case FileOpenOption_OpenAlways: result = OPEN_ALWAYS; break;
    case FileOpenOption_OpenExisting: result = OPEN_EXISTING; break;
    case FileOpenOption_TruncateExisting: result = TRUNCATE_EXISTING; break;
    default: break;
    }

    return result;
}

FileOpenResult open_file(ConstStringU8 filename, FileAccessMode access_mode, FileOpenOption options) {
    Allocator allocator = make_arena_allocator();
    ConstStringU16 wide_filename = convert_utf8_to_utf16(&allocator, filename, Utf16Type_LE);

    FileOpenResult result = open_file(wide_filename, access_mode, options);

    destroy_arena_allocator(&allocator);
    return result;
}

FileOpenResult open_file(ConstStringU16 filename, FileAccessMode access_mode, FileOpenOption options) {
    DWORD desired_access = translate_file_access_mode(access_mode);
    DWORD creation_disposition = translate_file_open_option(options);
    HANDLE create_result =
        CreateFileW((LPCWSTR)filename.data, desired_access, 0, 0, creation_disposition, FILE_ATTRIBUTE_NORMAL, 0);
    FileOpenResult result = {0};

    if (create_result != INVALID_HANDLE_VALUE) {
        result.file.native_handle = *(u64*)&create_result;
        result.success = true;
    }

    return result;
}

void close_file(File* file) {
    if (file->native_handle == 0) return;
    HANDLE handle = *(HANDLE*)&file->native_handle;
    CloseHandle(handle);
    file->native_handle = 0;
}

u64 get_file_size(File file) {
    HANDLE handle = *(HANDLE*)&file.native_handle;
    LARGE_INTEGER native_size = {0};
    BOOL success = GetFileSizeEx(handle, &native_size);

    if (!success) return 0;
    return (u64)native_size.QuadPart;
}

Buffer read_entire_file(Allocator* allocator, File file) {
    if (file.native_handle == 0) return {0};

    u64 file_size = get_file_size(file);
    if (file_size == 0) return {0};

    Buffer buffer = push_buffer(allocator, file_size);

    HANDLE handle = *(HANDLE*)&file.native_handle;
    BOOL success = ReadFile(handle, buffer.data, (DWORD)file_size, 0, 0);
    if (!success) return buffer;

    buffer.size += file_size;
    return buffer;
}

bool write_to_file(File file, ConstBuffer buffer) {
    if (file.native_handle == 0) return false;
    if (buffer.size == 0) return true;

    HANDLE handle = *(HANDLE*)&file.native_handle;
    BOOL success = WriteFile(handle, buffer.data, buffer.size, 0, 0);

    if (!success) return false;
    return true;
}