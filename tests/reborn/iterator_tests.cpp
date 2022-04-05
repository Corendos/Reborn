/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/iterator.h>
#include <reborn/strings.h>

static const char ITERATOR_INPUT[] = "...........\n"
                                     "1..........\n"
                                     "2..........\n"
                                     "...........\n"
                                     "......642;.\n"
                                     "...........\n"
                                     "...........\n"
                                     "...........\n";

TEST_CASE(make_iterator_1) {
    Iterator it = make_iterator(ITERATOR_INPUT, array_size(ITERATOR_INPUT));
    CHECK("The iterator has the correct data ptr", it.data == ITERATOR_INPUT);
    CHECK("The iterator current pointer points to the beginning of the input", it.current == ITERATOR_INPUT);
    CHECK("The iterator has the correct input size", it.size == array_size(ITERATOR_INPUT));
}

TEST_CASE(make_iterator_2) {
    ConstStringU8 str = make_const_string(ITERATOR_INPUT, array_size(ITERATOR_INPUT));
    Iterator it = make_iterator(&str);
    CHECK("The iterator has the correct data ptr", it.data == ITERATOR_INPUT);
    CHECK("The iterator current pointer points to the beginning of the input", it.current == ITERATOR_INPUT);
    CHECK("The iterator has the correct input size", it.size == array_size(ITERATOR_INPUT));
}

TEST_CASE(iterator_peek) {
    Iterator it = make_iterator(ITERATOR_INPUT, array_size(ITERATOR_INPUT));
    u64 offset = 12;
    const char* c = ITERATOR_INPUT + offset;
    CONSTRAINT(*c == '1');
    CHECK("Calling peek with an offset of 12 should return the first 1", peek(&it, offset) == '1');
    u64 big_offset = 2000;
    CONSTRAINT(it.size < big_offset);
    CHECK("Calling peek with an offset of 2000 should return 0", peek(&it, big_offset) == 0);
}

TEST_CASE(iterator_peek_or) {
    Iterator it = make_iterator(ITERATOR_INPUT, array_size(ITERATOR_INPUT));
    u64 big_offset = 2000;
    CONSTRAINT(it.size < big_offset);
    CHECK("Calling peek_or with an offset of 2000 and 'a' should return 'a'", peek_or(&it, big_offset, 'a') == 'a');
}

TEST_CASE(iterator_get_position) {
    Iterator it = make_iterator(ITERATOR_INPUT, array_size(ITERATOR_INPUT));
    CHECK("An iterator freshly created should have a position of 0", get_position(&it) == 0);
    u64 advance = 12;
    CONSTRAINT(it.size > advance);
    it.current += advance;
    CHECK("An iterator that advanced by 12 should have a position of 12", get_position(&it) == advance);
}

TEST_CASE(iterator_is_valid) {
    Iterator it = make_iterator(ITERATOR_INPUT, array_size(ITERATOR_INPUT));
    CHECK("An iterator freshly created should be valid if the data has a size > 1", is_valid(&it));
    u64 advance = 12;
    CONSTRAINT(it.size > advance);
    it.current += advance;
    CHECK("An iterator that advanced by a number less than the input size should be valid", is_valid(&it));
    u64 big_advance = 2000;
    CONSTRAINT(it.size < big_advance);
    it.current += big_advance;
    CHECK("An iterator that advanced by a number greater than the input size should not be valid", !is_valid(&it));
}

TEST_CASE(iterator_skip_to) {
    Iterator it = make_iterator(ITERATOR_INPUT, array_size(ITERATOR_INPUT));
    skip_to(&it, '1');
    CHECK("The iterator should have skipped to the first 1 it encountered", it.current[0] == '1');
    CHECK("The iterator should have the correct position", get_position(&it) == 12);
}

TEST_CASE(iterator_skip_to_first_after) {
    Iterator it = make_iterator(ITERATOR_INPUT, array_size(ITERATOR_INPUT));
    skip_to_first_after(&it, '\n');
    CHECK("The iterator should have skipped to the character after the first '\\n'", it.current[0] == '1');
    CHECK("The iterator should have the correct position", get_position(&it) == 12);
}

bool is_two(char c) { return c == '2'; }

TEST_CASE(iterator_skip_to_first_if) {
    Iterator it = make_iterator(ITERATOR_INPUT, array_size(ITERATOR_INPUT));
    skip_to_first_if(&it, is_two);
    CHECK("The iterator should have skipped to the character validating the predicate", it.current[0] == '2');
    CHECK("The iterator has the correct position", get_position(&it) == 24);
}

TEST_CASE(iterator_parse_u64_1) {
    Iterator it = make_iterator(ITERATOR_INPUT, array_size(ITERATOR_INPUT));
    skip_to(&it, '6');
    CONSTRAINT(it.current[0] == '6');
    u64 value = parse_u64(&it);
    CHECK("The parsed value should be correct", value == 642);
    CHECK("The iterator should point to the first character after the number in the input", it.current[0] == ';');
}

SECTION(iterator) {
    RUN_TEST_CASE(make_iterator_1);
    RUN_TEST_CASE(make_iterator_2);
    RUN_TEST_CASE(iterator_peek);
    RUN_TEST_CASE(iterator_peek_or);
    RUN_TEST_CASE(iterator_get_position);
    RUN_TEST_CASE(iterator_is_valid);
    RUN_TEST_CASE(iterator_skip_to);
    RUN_TEST_CASE(iterator_skip_to_first_after);
    RUN_TEST_CASE(iterator_skip_to_first_if);
    RUN_TEST_CASE(iterator_parse_u64_1);
}