/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#include <reborn/memory.h>
#include <reborn/strings.h>

#include <assert.h>
#include <string.h>

TEST_CASE(utf8_internal_validation) {
    char length1_start = 0b01110100;
    char length2_start = 0b11010100;
    char length3_start = 0b11101100;
    char length4_start = 0b11110100;
    char continuation = 0b10110110;
    CHECK("A codepoint of length 1 should start with 0b0xxxxxxx", is_valid_utf8_code_unit_start_1(length1_start));
    CHECK("A codepoint of length 2 should start with 0b110xxxxx", is_valid_utf8_code_unit_start_2(length2_start));
    CHECK("A codepoint of length 3 should start with 0b1110xxxx", is_valid_utf8_code_unit_start_3(length3_start));
    CHECK("A codepoint of length 4 should start with 0b11110xxx", is_valid_utf8_code_unit_start_4(length4_start));
    CHECK("A codepoint continuation should start with 0b10xxxxxx", is_valid_utf8_continuation_code_unit(continuation));
}

TEST_CASE(utf8_code_unit_continuation) {
    char continuations[] = {(char)0b10001010, (char)0b10011010, (char)0b10001011};
    CHECK("Multiple bytes starting with 0b10xxxxxx should be valid continuation",
          are_valid_utf8_continuation_code_units(continuations, array_size(continuations)));
}

TEST_CASE(utf8_validation_1) {
    ConstStringU8 str = SCu8("I'm a valid utf8 string");
    CHECK("An ASCII string should be a valid UTF-8 string", is_valid_utf8(str));
}

TEST_CASE(utf8_validation_2) {
    ConstStringU8 str = SCu8("I'm a valid utf8 string containing unicode : \U0001F625");
    CHECK("An string containing escaped unicodes should be a valid UTF-8 string", is_valid_utf8(str));
}

TEST_CASE(utf8_validation_3) {
    ConstStringU8 str = SCu8("I'm not a valid utf8 string because I have a \xB4");
    CHECK("A string containing an invalid byte should not be a valid UTF-8 string", is_valid_utf8(str) == false);
}

TEST_CASE(codepoint_to_utf8_1) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 256);

    ConstStringU8 truth = SCu8(u8"a");

    write_to(&str, (u32)'a');
    CHECK("The string should have the correct character written ('a')", string_compare(str, truth) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(codepoint_to_utf8_2) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 256);

    ConstStringU8 truth = SCu8(u8"\u00C9");

    write_to(&str, (u32)0x00C9);
    CHECK("The string should have the correct character written (U+00C9)", string_compare(str, truth) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(codepoint_to_utf8_3) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 256);

    ConstStringU8 truth = SCu8(u8"\u258C");

    write_to(&str, (u32)0x258C);
    CHECK("The string should have the correct character written (U+258C)", string_compare(str, truth) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(codepoint_to_utf8_4) {
    Allocator allocator = make_arena_allocator();
    StringU8 str = push_string_u8(&allocator, 256);

    ConstStringU8 truth = SCu8(u8"\U0001F648");

    write_to(&str, (u32)0x1F648);
    CHECK("The string should have the correct character written (U+1F648)", string_compare(str, truth) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(utf8_conversion_1) {
    Allocator allocator = make_arena_allocator();

    ConstStringU8 str = SCu8(u8"This is a string");
    ConstStringU16 converted_str = convert_utf8_to_utf16(&allocator, str);
    ConstStringU8 back_conversion = convert_utf16_to_utf8(&allocator, converted_str);

    CHECK("The converted string should be the equal to the original string in utf16",
          string_compare(str, back_conversion) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(utf8_conversion_2) {
    Allocator allocator = make_arena_allocator();

    ConstStringU8 str = SCu8(u8"This is a string");
    ConstStringU32 converted_str = convert_utf8_to_utf32(&allocator, str);
    ConstStringU8 back_conversion = convert_utf32_to_utf8(&allocator, converted_str);

    CHECK("The converted string should be the equal to the original string in utf32",
          string_compare(str, back_conversion) == 0);
    destroy_arena_allocator(&allocator);
}

TEST_CASE(utf8_iterator_1) {
    ConstStringU8 str = SCu8(u8"");
    Utf8Iterator it = make_utf8_iterator(str);
    CHECK("An iterator created with an empty string should be invalid", is_valid(&it) == false);
}

TEST_CASE(utf8_iterator_2) {
    const char raw_str[] = u8"abcdef";
    ConstStringU8 str = SCu8(raw_str);
    Utf8Iterator it = make_utf8_iterator(str);

    const char* raw_codepoint = raw_str;
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        CHECK("Calling get_codepoint_and_advance on an iterator returns the current codepoint and advance",
              codepoint == (u32)*raw_codepoint);
        raw_codepoint++;
    }
}

TEST_CASE(utf8_iterator_3) {
    const u32 raw_str[] = {*(u32*)U"a", *(u32*)U"b",          *(u32*)U"c", *(u32*)U"d",
                           *(u32*)U"e", *(u32*)U"\U0001035A", (u32)0};
    ConstStringU32 str_u32 = make_const_string(raw_str);

    Allocator allocator = make_arena_allocator();
    ConstStringU8 str = convert_utf32_to_utf8(&allocator, str_u32);
    Utf8Iterator it = make_utf8_iterator(str);

    const u32* raw_codepoint = raw_str;
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        CHECK("Calling get_codepoint_and_advance on an iterator returns the current codepoint and advance",
              codepoint == *raw_codepoint);
        raw_codepoint++;
    }

    destroy_arena_allocator(&allocator);
}

SECTION(utf8) {
    RUN_TEST_CASE(utf8_internal_validation);
    RUN_TEST_CASE(utf8_code_unit_continuation);
    RUN_TEST_CASE(utf8_validation_1);
    RUN_TEST_CASE(utf8_validation_2);
    RUN_TEST_CASE(utf8_validation_3);
    RUN_TEST_CASE(codepoint_to_utf8_1);
    RUN_TEST_CASE(codepoint_to_utf8_2);
    RUN_TEST_CASE(codepoint_to_utf8_3);
    RUN_TEST_CASE(codepoint_to_utf8_4);
    RUN_TEST_CASE(utf8_conversion_1);
    RUN_TEST_CASE(utf8_conversion_2);
    RUN_TEST_CASE(utf8_iterator_1);
    RUN_TEST_CASE(utf8_iterator_2);
    RUN_TEST_CASE(utf8_iterator_3);
}

TEST_CASE(utf16_internal_validation) {
    u16 length1_character_1 = 0xD63F;
    u16 length1_character_2 = 0xF021;
    u16 high_surrogate = 0xD834;
    u16 low_surrogate = 0xDC1A;
    CHECK("A utf16 word between 0x0000 and 0xD7FF should represent a character of length one",
          is_valid_utf16_single_code_unit(length1_character_1, Utf16Type_LE));
    CHECK("A utf16 word between 0xE000 and 0xFFFF should represent a character of length one",
          is_valid_utf16_single_code_unit(length1_character_2, Utf16Type_LE));
    CHECK("A utf16 word between 0xD800 and 0xDBFF should be a valid high surrogate",
          is_valid_utf16_high_surrogate(high_surrogate, Utf16Type_LE));
    CHECK("A utf16 word between 0xDC00 and 0xDFFF should be a valid low surrogate",
          is_valid_utf16_low_surrogate(low_surrogate, Utf16Type_LE));
}

TEST_CASE(utf16_validation_1) {
    const u16* utf16_raw_str = (const u16*)u"This is a valid utf16 string";
    u64 utf16_raw_str_size = string_length(utf16_raw_str);
    ConstStringU16 str = {utf16_raw_str, utf16_raw_str_size};
    CHECK("An array representing a utf16 string should be valid", is_valid_utf16(str));
}

TEST_CASE(utf16_conversion_1) {
    Allocator allocator = make_arena_allocator();
    const u16* utf16_raw_str = (const u16*)u"\u00e9";
    u64 utf16_raw_str_size = string_length(utf16_raw_str);
    ConstStringU16 str = {utf16_raw_str, utf16_raw_str_size};
    ConstStringU8 converted_str = convert_utf16_to_utf8(&allocator, str);
    ConstStringU16 back_conversion = convert_utf8_to_utf16(&allocator, converted_str);

    CHECK("The converted string should be the equal to the original string in utf8",
          string_compare(str, back_conversion) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(utf16_conversion_2) {
    Allocator allocator = make_arena_allocator();
    const u16* utf16_raw_str = (const u16*)u"\u00e9";
    u64 utf16_raw_str_size = string_length(utf16_raw_str);
    ConstStringU16 str = {utf16_raw_str, utf16_raw_str_size};
    ConstStringU32 converted_str = convert_utf16_to_utf32(&allocator, str);
    ConstStringU16 back_conversion = convert_utf32_to_utf16(&allocator, converted_str);

    CHECK("The converted string should be the equal to the original string in utf8",
          string_compare(str, back_conversion) == 0);

    destroy_arena_allocator(&allocator);
}

TEST_CASE(utf16_iterator_1) {
    u16 raw_str[] = {0};
    ConstStringU16 str = make_const_string(raw_str);
    Utf16Iterator it = make_utf16_iterator(str);
    CHECK("An iterator created with an empty string should be invalid", is_valid(&it) == false);
}

TEST_CASE(utf16_iterator_2) {
    u16 raw_str[] = {*(u16*)u"a", *(u16*)u"b", *(u16*)u"c", *(u16*)u"d", *(u16*)u"e", *(u16*)u"f", (u16)0};
    ConstStringU16 str = make_const_string(raw_str);
    Utf16Iterator it = make_utf16_iterator(str);

    const u16* raw_codepoint = raw_str;
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        CHECK("Calling get_codepoint_and_advance on an iterator returns the current codepoint and advance",
              codepoint == (u32)*raw_codepoint);
        raw_codepoint++;
    }
}

TEST_CASE(utf16_iterator_3) {
    const u32 raw_str[] = {*(u32*)U"a", *(u32*)U"b",          *(u32*)U"c", *(u32*)U"d",
                           *(u32*)U"e", *(u32*)U"\U0001035A", (u32)0};
    ConstStringU32 str_u32 = make_const_string(raw_str);

    Allocator allocator = make_arena_allocator();
    ConstStringU16 str = convert_utf32_to_utf16(&allocator, str_u32);
    Utf16Iterator it = make_utf16_iterator(str);

    const u32* raw_codepoint = raw_str;
    while (is_valid(&it)) {
        u32 codepoint = get_codepoint_and_advance(&it);
        CHECK("Calling get_codepoint_and_advance on an iterator returns the current codepoint and advance",
              codepoint == *raw_codepoint);
        raw_codepoint++;
    }

    destroy_arena_allocator(&allocator);
}

SECTION(utf16) {
    RUN_TEST_CASE(utf16_internal_validation);
    RUN_TEST_CASE(utf16_validation_1);
    RUN_TEST_CASE(utf16_conversion_1);
    RUN_TEST_CASE(utf16_conversion_2);
    RUN_TEST_CASE(utf16_iterator_1);
    RUN_TEST_CASE(utf16_iterator_2);
    RUN_TEST_CASE(utf16_iterator_3);
}

SECTION(strings_unicode) {
    RUN_SECTION(utf8);
    RUN_SECTION(utf16);
}