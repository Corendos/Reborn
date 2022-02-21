#ifndef REBORN_TIME_CLOCK_H
#define REBORN_TIME_CLOCK_H

#include <reborn/time/types.h>

FloatingTimePoint convert_with_ratio(FloatingTimePoint t, Rational r);
FloatingTimePoint convert_floating_to_ns(FloatingTimePoint t);
FloatingTimePoint convert_floating_to_us(FloatingTimePoint t);
FloatingTimePoint convert_floating_to_ms(FloatingTimePoint t);
FloatingTimePoint convert_floating_to_s(FloatingTimePoint t);

FloatingTimePoint get_floating_time_ns();
FloatingTimePoint get_floating_time_us();
FloatingTimePoint get_floating_time_ms();
FloatingTimePoint get_floating_time_s();

TimePoint convert_with_ratio(TimePoint t, Rational r);
TimePoint convert_to_ns(TimePoint t);
TimePoint convert_to_us(TimePoint t);
TimePoint convert_to_ms(TimePoint t);
TimePoint convert_to_s(TimePoint t);

TimePoint get_time_ns();
TimePoint get_time_us();
TimePoint get_time_ms();
TimePoint get_time_s();

#endif // REBORN_TIME_CLOCK_H
