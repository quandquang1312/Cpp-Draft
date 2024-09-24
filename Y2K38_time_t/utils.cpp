#include <cstdint>
#include <iostream>
#include <ctime>
#include <sstream>
#include <chrono>
#include <iomanip>

#define LOWER_YEAR 1900

using time_32t = int32_t;
time_32t toMyTimeT(const std::chrono::system_clock::time_point& tp) {
    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(tp).time_since_epoch().count();

    // Check for overflow
    if (seconds < std::numeric_limits<time_32t>::min() || seconds > std::numeric_limits<time_32t>::max()) {
        throw std::overflow_error("Time exceeds 32-bit limit");
    }
    
    return static_cast<time_32t>(seconds);
}

int64_t toMyTimeT64(const std::chrono::system_clock::time_point& tp) {
    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(tp).time_since_epoch().count();

    // Check for overflow
    if (seconds < std::numeric_limits<int64_t>::min() || seconds > std::numeric_limits<int64_t>::max()) {
        throw std::overflow_error("Time exceeds 32-bit limit");
    }
    
    return static_cast<int64_t>(seconds);
}

std::chrono::system_clock::time_point fromMyTimeT(time_32t t) {
    return std::chrono::system_clock::time_point(std::chrono::seconds(t));
}

std::chrono::system_clock::time_point createTimePoint(int year, int month, int day, int hour, int minute, int second) {
    std::tm tm = {};
    tm.tm_year = year - LOWER_YEAR; // Year since 1900
    tm.tm_mon = month - 1;    // Month is 0-based
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;

    std::time_t time = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(time);
}

// Original
std::string getIso8601UtcTimeStamp(const std::chrono::system_clock::time_point& ts) {
    const std::time_t time = std::chrono::system_clock::to_time_t(ts);
    std::ostringstream oss;
    struct tm tm {}; // gmtime_r is a C method that use the libC struct tm
    oss << std::put_time(gmtime_r(&time, &tm), "%FT%TZ");
    return oss.str();
}

// Replace
std::string replaceGetIso8601UtcTimeStamp(const std::chrono::system_clock::time_point& ts) {

    const std::time_t time = std::chrono::system_clock::to_time_t(ts);
    std::ostringstream oss;
    struct tm tm {}; // gmtime_r is a C method that use the libC struct tm
    oss << std::put_time(gmtime_r(&time, &tm), "%FT%TZ");
    return oss.str();
}

