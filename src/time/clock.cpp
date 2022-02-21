#include <reborn/math.h>
#include <reborn/time/clock.h>

#if defined(OS_WINDOWS)

#include <windows.h>

static Rational performance_counter_frequency = {0};

internal inl void init_performance_counter_frequency() {
    if (performance_counter_frequency.den == 0) {
        LARGE_INTEGER value;
        BOOL result = QueryPerformanceFrequency(&value);
        ASSERT(result);
        performance_counter_frequency.num = 1;
        performance_counter_frequency.den = value.QuadPart;
    }
}

internal inl FloatingTimePoint get_floating_time_native() {
    init_performance_counter_frequency();
    LARGE_INTEGER value;
    QueryPerformanceCounter(&value);
    return FloatingTimePoint{(f64)value.QuadPart, performance_counter_frequency};
}

Rational to_lowest_form(Rational r) {
    i64 v = gcd(r.num, r.den);
    return Rational{r.num / v, r.den / v};
}

FloatingTimePoint convert_with_ratio(FloatingTimePoint t, Rational r) {
    Rational temp_ratio = to_lowest_form(Rational{t.ratio.num * r.den, t.ratio.den * r.num});
    return FloatingTimePoint{t.value * temp_ratio.num / temp_ratio.den, r};
}

FloatingTimePoint convert_floating_to_ns(FloatingTimePoint t) { return convert_with_ratio(t, Rational{1, 1000000000}); }

FloatingTimePoint convert_floating_to_us(FloatingTimePoint t) { return convert_with_ratio(t, Rational{1, 1000000}); }

FloatingTimePoint convert_floating_to_ms(FloatingTimePoint t) { return convert_with_ratio(t, Rational{1, 1000}); }

FloatingTimePoint convert_floating_to_s(FloatingTimePoint t) { return convert_with_ratio(t, Rational{1, 1}); }

FloatingTimePoint get_floating_time_ns() { return convert_floating_to_ns(get_floating_time_native()); }

FloatingTimePoint get_floating_time_us() { return convert_floating_to_us(get_floating_time_native()); }

FloatingTimePoint get_floating_time_ms() { return convert_floating_to_ms(get_floating_time_native()); }

FloatingTimePoint get_floating_time_s() { return convert_floating_to_s(get_floating_time_native()); }

internal inl TimePoint get_time_native() {
    init_performance_counter_frequency();
    LARGE_INTEGER value;
    QueryPerformanceCounter(&value);
    return TimePoint{value.QuadPart, performance_counter_frequency};
}

TimePoint convert_with_ratio(TimePoint t, Rational r) {
    Rational temp_ratio = to_lowest_form(Rational{t.ratio.num * r.den, t.ratio.den * r.num});
    return TimePoint{t.value * temp_ratio.num / temp_ratio.den, r};
}

TimePoint convert_to_ns(TimePoint t) { return convert_with_ratio(t, Rational{1, 1000000000}); }

TimePoint convert_to_us(TimePoint t) { return convert_with_ratio(t, Rational{1, 1000000}); }

TimePoint convert_to_ms(TimePoint t) { return convert_with_ratio(t, Rational{1, 1000}); }

TimePoint convert_to_s(TimePoint t) { return convert_with_ratio(t, Rational{1, 1}); }

TimePoint get_time_ns() { return convert_to_ns(get_time_native()); }

TimePoint get_time_us() { return convert_to_us(get_time_native()); }

TimePoint get_time_ms() { return convert_to_ms(get_time_native()); }

TimePoint get_time_s() { return convert_to_s(get_time_native()); }

#else
#error "Not implemented"
#endif