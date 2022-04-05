/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details at https://github.com/Corendos/Reborn
 */

#include <reborn/time/clock.h>

TEST_CASE(floating_conversion_1) {
    // NOTE(Corentin): 1s
    FloatingTimePoint t{1, Rational{1, 1}};
    FloatingTimePoint t_as_ns = convert_floating_to_ns(t);
    FloatingTimePoint t_as_us = convert_floating_to_us(t);
    FloatingTimePoint t_as_ms = convert_floating_to_ms(t);
    CHECK("1s should be equal to 1000000000ns",
          t_as_ns.value == 1000000000.0 && t_as_ns.ratio.num == 1 && t_as_ns.ratio.den == 1000000000);
    CHECK("1s should be equal to 1000000us",
          t_as_us.value == 1000000.0 && t_as_us.ratio.num == 1 && t_as_us.ratio.den == 1000000);
    CHECK("1s should be equal to 1000ms",
          t_as_ms.value == 1000.0 && t_as_ms.ratio.num == 1 && t_as_ms.ratio.den == 1000);
}

TEST_CASE(floating_conversion_2) {
    // NOTE(Corentin): 1 tick is a 1/20 th of a second
    FloatingTimePoint t_as_ticks{1, Rational{1, 20}};
    // NOTE(Corentin): a tick is a 20th of a second
    FloatingTimePoint t = convert_floating_to_s(t_as_ticks);
    CHECK("1 tick should be equal to 0.050s", t.value == 0.05 && t.ratio.num == 1 && t.ratio.den == 1);
}

TEST_CASE(conversion_1) {
    // NOTE(Corentin): 1s
    TimePoint t{1, Rational{1, 1}};
    TimePoint t_as_ns = convert_to_ns(t);
    TimePoint t_as_us = convert_to_us(t);
    TimePoint t_as_ms = convert_to_ms(t);
    CHECK("1s should be equal to 1000000000ns",
          t_as_ns.value == 1000000000 && t_as_ns.ratio.num == 1 && t_as_ns.ratio.den == 1000000000);
    CHECK("1s should be equal to 1000000us",
          t_as_us.value == 1000000 && t_as_us.ratio.num == 1 && t_as_us.ratio.den == 1000000);
    CHECK("1s should be equal to 1000ms", t_as_ms.value == 1000 && t_as_ms.ratio.num == 1 && t_as_ms.ratio.den == 1000);
}

TEST_CASE(conversion_2) {
    // NOTE(Corentin): 1 tick is a 1/20 th of a second
    TimePoint t_as_ticks{1, Rational{1, 20}};
    // NOTE(Corentin): a tick is a 20th of a second
    TimePoint t = convert_to_s(t_as_ticks);
    CHECK("1 tick should be equal to 0s (as integer)", t.value == 0 && t.ratio.num == 1 && t.ratio.den == 1);
}

SECTION(clock) {
    RUN_TEST_CASE(floating_conversion_1);
    RUN_TEST_CASE(floating_conversion_2);

    RUN_TEST_CASE(conversion_1);
    RUN_TEST_CASE(conversion_2);
}

SECTION(time) { RUN_SECTION(clock); }
