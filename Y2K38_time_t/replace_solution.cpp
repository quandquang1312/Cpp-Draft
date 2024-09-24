#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <format>

// Constants
const int SECONDS_IN_A_MINUTE = 60;
const int SECONDS_IN_AN_HOUR = 3600;
const int SECONDS_IN_A_DAY = 86400;

#define LOWER_YEAR 1900

// Function to determine if a year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to convert seconds since epoch to ISO 8601 formatted string
std::string getIso8601UtcTimeStamp_r(const std::chrono::system_clock::time_point& ts) {
    // Get the total seconds since epoch
    int64_t totalSeconds = std::chrono::duration_cast<std::chrono::seconds>(ts.time_since_epoch()).count();

    // Calculate the number of days and the remaining seconds of the current day
    int64_t days = totalSeconds / SECONDS_IN_A_DAY;
    int64_t secondsOfDay = totalSeconds % SECONDS_IN_A_DAY;

    // Calculate the year
    int year = LOWER_YEAR; // Starting from epoch
    while (days >= (isLeapYear(year) ? 366 : 365)) {
        days -= (isLeapYear(year) ? 366 : 365);
        year++;
    }

    // Calculate the month and day
    int month = 1; // January
    int day = days + 1; // Day of the month (1-based)
    int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Adjust for leap years
    if (isLeapYear(year)) {
        monthDays[1] = 29; // February in a leap year
    }

    // Calculate the month
    while (day > monthDays[month - 1]) {
        day -= monthDays[month - 1];
        month++;
    }

    // Calculate the hour, minute, and second
    int hour = secondsOfDay / SECONDS_IN_AN_HOUR;
    int minute = (secondsOfDay % SECONDS_IN_AN_HOUR) / SECONDS_IN_A_MINUTE;
    int second = secondsOfDay % SECONDS_IN_A_MINUTE;

    // Create ISO 8601 formatted string
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << year << "-"
        << std::setw(2) << month << "-"
        << std::setw(2) << day << "T"
        << std::setw(2) << hour << ":"
        << std::setw(2) << minute << ":"
        << std::setw(2) << second << "Z"; // Z for UTC

    return oss.str();
}

std::string replace2(const std::chrono::system_clock::time_point& tp) {
    using namespace std::chrono_literals;
    std::chrono::time_point tp = std::chrono::sys_days{2016y/1/16} + 11h + 25min;
    std::string s = std::format("{:%Y%m%d%H%M}", tp);
    std::cout << s << '\n';  
}