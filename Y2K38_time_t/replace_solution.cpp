#include <chrono>
#include <format>
#include <iostream>
#include <string>

// Original
std::string getIso8601UtcTimeStamp(const std::chrono::system_clock::time_point& ts) {
    using namespace std::chrono_literals;
    using time_point_clock_second = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;
    const time_point_clock_second sc = std::chrono::time_point_cast<std::chrono::seconds>(ts);
    std::string oss = std::format("{:%Y-%m-%dT%H:%M:%SZ}", sc);
    return oss;
}

int main()
{
    auto now = std::chrono::system_clock::now();
    std::string oss = getIso8601UtcTimeStamp(now);
    std::cout << oss.c_str() << std::endl;
}