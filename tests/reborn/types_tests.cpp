/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/types.h>

struct TestSingleLinkedListNode {
    union {
        TestSingleLinkedListNode* next;
        TestSingleLinkedListNode* prev;
    };
    u64 sentinel;
};

struct TestSingleLinkedList {
    TestSingleLinkedListNode* node;
};

TEST_CASE(stack_push_and_pop) {
    TestSingleLinkedList list = {0};
    REQUIRE("A just created list has no node", list.node == 0);
    TestSingleLinkedListNode first_node = {0};
    first_node.sentinel = 42;
    single_linked_list_stack_push(list.node, &first_node);
    REQUIRE("The top of the stack should be the last added node",
            list.node == &first_node && list.node->sentinel == 42);
    CHECK("The single node at the top of the stack should point to nothing", list.node->next == 0);
    TestSingleLinkedListNode second_node = {0};
    second_node.sentinel = 10;
    single_linked_list_stack_push(list.node, &second_node);
    REQUIRE("The top of the stack should be the last added node",
            list.node == &second_node && list.node->sentinel == 10);
    CHECK("The node at the top of the stack should point to the previous one", list.node->next == &first_node);

    single_linked_list_stack_pop(list.node);
    REQUIRE("The top of the stack should be the first added node after a pop",
            list.node == &first_node && list.node->sentinel == 42);
    CHECK("The single node at the top of the stack should point to nothing", list.node->next == 0);
}

TEST_CASE(is_power_of_two) {
    CHECK("0 should be considered as a power of two", is_power_of_two(0) == true);
    CHECK("1 should be considered as a power of two", is_power_of_two(1) == true);
    CHECK("2 should be considered as a power of two", is_power_of_two(2) == true);
    CHECK("3 should not be considered as a power of two", is_power_of_two(3) == false);
    CHECK("2^10 should be considered as a power of two", is_power_of_two(0b10000000000) == true);
    CHECK("2^10 + 2^12 should not be considered as a power of two", is_power_of_two(0b1010000000000) == false);
    CHECK("37163251 should not be considered a power of two", is_power_of_two(37163251) == false);
}

TEST_CASE(align_to_1) {
    u64 aligned = align_to(0, 8);
    CHECK("0 with alignment of 8 should be aligned to 0", aligned == 0);
}

TEST_CASE(align_to_2) {
    u64 aligned = align_to(3, 8);
    CHECK("3 with alignment of 8 should be aligned to 8", aligned == 8);
}

TEST_CASE(align_to_3) {
    u64 aligned = align_to(8, 8);
    CHECK("8 with alignment of 8 should be aligned to 8", aligned == 8);
}

TEST_CASE(align_to_4) {
    u64 aligned = align_to(8, 15);
    CHECK("8 with alignment of 15 should be aligned to 15", aligned == 15);
}

TEST_CASE(align_to_5) {
    u64 aligned = align_to(15, 15);
    CHECK("15 with alignment of 15 should be aligned to 15", aligned == 15);
}

TEST_CASE(is_aligned_to_1) {
    CHECK("0 with alignment of 8 is aligned to 8", is_aligned_to(0, 8) == true);
    CHECK("8 with alignment of 8 is aligned to 8", is_aligned_to(8, 8) == true);
    CHECK("3 with alignment of 8 is not aligned to 8", is_aligned_to(3, 8) == false);

    CHECK("15 with alignment of 15 is aligned to 15", is_aligned_to(15, 15) == true);
    CHECK("8 with alignment of 15 is not aligned to 15", is_aligned_to(8, 15) == false);
}

SECTION(misc_utils) {
    RUN_TEST_CASE(is_power_of_two);
    RUN_TEST_CASE(align_to_1);
    RUN_TEST_CASE(align_to_2);
    RUN_TEST_CASE(align_to_3);
    RUN_TEST_CASE(align_to_4);
    RUN_TEST_CASE(align_to_5);
    RUN_TEST_CASE(is_aligned_to_1);
}

SECTION(types) {
    RUN_TEST_CASE(stack_push_and_pop);
    RUN_SECTION(misc_utils);
}
