/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/memory.h>

TEST_CASE(memory_compare_1) {
    u8 data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    u8 data_less[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 8};
    u8 data_greater[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 10};

    CONSTRAINT(array_size(data) == array_size(data_less));
    CONSTRAINT(array_size(data) == array_size(data_greater));

    CHECK("\"data\" should be equal to \"data\"", memory_compare(data, data, array_size(data)) == 0);
    CHECK("\"data_less\" should be less than \"data\"", memory_compare(data_less, data, array_size(data)) < 0);
    CHECK("\"data_greater\" should be greater than \"data\"", memory_compare(data_greater, data, array_size(data)) > 0);
}

TEST_CASE(memory_copy_1) {
    u8 data1[128] = {0};
    u8 data2[128] = {0};

    CONSTRAINT(array_size(data1) == array_size(data2));

    for (u64 i = 0; i < array_size(data1); ++i) {
        data1[i] = i;
    }

    memory_copy(data1, data2, array_size(data1));
    CHECK("The two buffer should be equal", memory_compare(data1, data2, array_size(data1)) == 0);
}

TEST_CASE(memory_copy_2) {
    u8 truth[256] = {0};
    u8 data[256] = {0};

    CONSTRAINT(array_size(truth) == array_size(data));

    for (u64 i = 0; i < array_size(data); ++i) {
        data[i] = i;
        truth[i] = i;
    }

    memory_copy(data, data + 64, 128);
    CHECK("The copied part should be equal to the original source", memory_compare(data + 64, truth, 128) == 0);
}

TEST_CASE(memory_copy_3) {
    u8 truth[256] = {0};
    u8 data[256] = {0};

    CONSTRAINT(array_size(truth) == array_size(data));

    for (u64 i = 0; i < array_size(data); ++i) {
        data[i] = i;
        truth[i] = i;
    }

    memory_copy(data + 64, data, 128);
    CHECK("The copied part should be equal to the original source", memory_compare(data, truth + 64, 128) == 0);
}

TEST_CASE(memory_set_1) {
    u8 truth[256] = {0};
    u8 data[256] = {0};

    CONSTRAINT(array_size(truth) == array_size(data));

    for (u64 i = 0; i < array_size(truth); ++i) {
        truth[i] = 1;
    }

    memory_set(data, 1, array_size(data));

    CHECK("The set buffer should contain the correct values", memory_compare(data, truth, array_size(data)) == 0);
}

TEST_CASE(make_cursor) {
    u8* data = (u8*)0xdeadbeef0000;
    u64 capacity = 128;
    Cursor cursor = make_cursor(data, capacity);
    CHECK("The constructed cursor should have the correct capacity", cursor.capacity == capacity);
    CHECK("The constructed cursor should have a position of 0 after construction", cursor.pos == 0);
    CHECK("The constructed cursor should point to the correct data", cursor.data == data);
}

TEST_CASE(cursor_push_and_pop) {
    u8* data = (u8*)0xdeadbeef0000;
    u64 capacity = 128;
    Cursor cursor = make_cursor(data, capacity);
    u64 pushed_size = 24;
    u8* ptr1 = (u8*)linear_allocation_push(&cursor, pushed_size);
    CHECK("ptr1 should be valid", ptr1 != 0);
    CHECK("ptr1 should have the correct address", ptr1 == data);

    u8* ptr2 = (u8*)linear_allocation_push(&cursor, pushed_size);
    CHECK("ptr2 should be valid", ptr2 != 0);
    CHECK("ptr2 should have the correct address", ptr2 == (data + pushed_size));

    linear_allocation_pop(&cursor, pushed_size + pushed_size);
    CHECK("The resulting cursor should have the correct capacity", cursor.capacity == capacity);
    CHECK("The resulting cursor should have a position of 0 after pop", cursor.pos == 0);
    CHECK("The resulting cursor should point to the correct data", cursor.data == data);
}

TEST_CASE(cursor_temp) {
    u8* data = (u8*)0xdeadbeef0000;
    u64 capacity = 128;
    Cursor cursor = make_cursor(data, capacity);
    u64 pushed_size = 24;

    u8* ptr1 = (u8*)linear_allocation_push(&cursor, pushed_size);
    CHECK("ptr1 should be valid", ptr1 != 0);
    CHECK("ptr1 should have the correct address", ptr1 == data);

    u64 previous_capacity = cursor.capacity;
    u64 previous_pos = cursor.pos;
    u8* previous_data = cursor.data;

    TemporaryCursor temp = linear_allocation_begin_temp(&cursor);

    u8* ptr2 = (u8*)linear_allocation_push(&cursor, pushed_size);
    CHECK("ptr2 should be valid", ptr2 != 0);
    CHECK("ptr2 should have the correct address", ptr2 == (data + pushed_size));

    linear_allocation_end_temp(&temp);

    CHECK("The cursor should be the same as before the temporary block",
          cursor.capacity == previous_capacity && cursor.pos == previous_pos && cursor.data == previous_data);
}

TEST_CASE(make_arena_1) {
    Arena arena = make_arena();
    CHECK("The default arena node capacity is 4kB", arena.node_size == KB(4));
    CHECK("The arena is empty on creation", arena.cursor_node == 0);
}

TEST_CASE(make_arena_2) {
    u64 capacity = MB(2);
    Arena arena = make_arena(capacity);
    CHECK("The default arena node capacity is the one given", arena.node_size == capacity);
    CHECK("The arena is empty on creation", arena.cursor_node == 0);
}

TEST_CASE(arena_push_and_pop) {
    Arena arena = make_arena();
    void* ptr1 = linear_allocation_push(&arena, 7);
    void* ptr2 = linear_allocation_push(&arena, 42);
    CONSTRAINT(ptr1 != 0);
    CONSTRAINT(ptr2 != 0);
    CHECK("The pointers should be aligned on a 8-byte boundary",
          is_aligned_to((u64)ptr1, 8) && is_aligned_to((u64)ptr2, 8));
    void* big_ptr = linear_allocation_push(&arena, KB(128));
    CONSTRAINT(big_ptr != 0);
    CHECK("The pointers should be aligned on a 8-byte boundary", is_aligned_to((u64)big_ptr, 8));
    CHECK("Big allocation should be a special sized node", arena.cursor_node->cursor.capacity == KB(128));
    destroy_arena(&arena);
    CHECK("After a cleanup, there shouldn't be any node left", arena.cursor_node == 0);
}

TEST_CASE(arena_temp_1) {
    Arena arena = make_arena();
    u64 pushed_size = 24;

    u8* ptr1 = (u8*)linear_allocation_push(&arena, pushed_size);
    CHECK("ptr1 should be valid", ptr1 != 0);

    u8* previous_node_data = arena.cursor_node->cursor.data;
    u64 previous_node_pos = arena.cursor_node->cursor.pos;

    TemporaryArena temp = linear_allocation_begin_temp(&arena);

    u8* ptr2 = (u8*)linear_allocation_push(&arena, pushed_size);
    CHECK("ptr2 should be valid", ptr2 != 0);

    linear_allocation_end_temp(&temp);

    CHECK("The arena should be the same as before the temporary block",
          arena.cursor_node->cursor.data == previous_node_data && arena.cursor_node->cursor.pos == previous_node_pos);
    destroy_arena(&arena);
}

TEST_CASE(arena_temp_2) {
    Arena arena = make_arena();

    TemporaryArena temp = linear_allocation_begin_temp(&arena);

    u64 pushed_size = 24;
    u8* ptr1 = (u8*)linear_allocation_push(&arena, pushed_size);
    CHECK("ptr1 should be valid", ptr1 != 0);

    linear_allocation_end_temp(&temp);

    CHECK("The arena should be empty after the temporary block", arena.cursor_node == 0);
    destroy_arena(&arena);
}

TEST_CASE(arena_allocator_1) {
    Allocator allocator = make_arena_allocator();
    ArenaData* arena_data = (ArenaData*)allocator.user_data;
    CHECK("The arena is empty when created inside an allocator", arena_data->arena->cursor_node == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(arena_allocator_2) {
    Allocator allocator = make_arena_allocator();

    u64 pushed_size = 24;
    u8* ptr1 = (u8*)allocate(&allocator, pushed_size);
    CHECK("ptr1 should be valid", ptr1 != 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(arena_allocator_3) {
    Arena arena = make_arena();
    linear_allocation_push(&arena, 10);
    CONSTRAINT(arena.cursor_node != 0);
    u64 arena_size = arena.cursor_node->cursor.pos;

    Allocator allocator = make_arena_allocator(&arena);
    REQUIRE("Creating an allocator shouldn't impact the arena", arena.cursor_node->cursor.pos == arena_size);

    u64 pushed_size = 24;
    u8* ptr1 = (u8*)allocate(&allocator, pushed_size);
    CHECK("ptr1 should be valid", ptr1 != 0);
    CHECK("The arena size should be the sum of old size and new allocated size",
          arena.cursor_node->cursor.pos == arena_size + pushed_size);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(temporary_arena_allocator_1) {
    Arena arena = make_arena();
    linear_allocation_push(&arena, 10);
    CONSTRAINT(arena.cursor_node != 0);
    u64 arena_size = arena.cursor_node->cursor.pos;

    Allocator allocator = make_temporary_arena_allocator(&arena);
    REQUIRE("Creating a temporary allocator shouldn't impact the arena", arena.cursor_node->cursor.pos == arena_size);

    u64 pushed_size = 24;
    u8* ptr1 = (u8*)allocate(&allocator, pushed_size);
    CHECK("ptr1 should be valid", ptr1 != 0);
    CHECK("The arena size should be the sum of old size and new allocated size",
          arena.cursor_node->cursor.pos == arena_size + pushed_size);
    destroy_temporary_arena_allocator(&allocator);

    CHECK("After destruction of the allocator, the arena should be in the same state as before",
          arena.cursor_node->cursor.pos == arena_size);
    destroy_arena(&arena);
}

SECTION(allocator) {
    RUN_TEST_CASE(arena_allocator_1);
    RUN_TEST_CASE(arena_allocator_2);
    RUN_TEST_CASE(arena_allocator_3);
    RUN_TEST_CASE(temporary_arena_allocator_1);
}

SECTION(memory) {
    RUN_TEST_CASE(memory_compare_1);

    RUN_TEST_CASE(memory_copy_1);
    RUN_TEST_CASE(memory_copy_2);
    RUN_TEST_CASE(memory_copy_3);

    RUN_TEST_CASE(memory_set_1);

    RUN_TEST_CASE(make_cursor);
    RUN_TEST_CASE(cursor_push_and_pop);
    RUN_TEST_CASE(cursor_temp);
    RUN_TEST_CASE(make_arena_1);
    RUN_TEST_CASE(make_arena_2);
    RUN_TEST_CASE(arena_push_and_pop);
    RUN_TEST_CASE(arena_temp_1);
    RUN_TEST_CASE(arena_temp_2);
    RUN_SECTION(allocator);
}