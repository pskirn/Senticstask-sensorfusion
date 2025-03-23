#include "timestamp.h"
#include <cstdio>

Timestamp::Timestamp()
    : year(0), month(0), day(0), hour(0), minute(0), second(0), millisecond(0) {}


Timestamp::Timestamp(const std::string& str){
    sscanf(str.c_str(), "%d-%d-%d %d:%d:%d.%d", 
        &year, &month, &day, &hour, &minute, & second, &millisecond);
}

bool Timestamp::operator<(const Timestamp& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    if (day != other.day) return day < other.day;
    if (hour != other.hour) return hour < other.hour;
    if (minute != other.minute) return minute < other.minute;
    if (second != other.second) return second < other.second;
    return millisecond < other.millisecond;
}

bool Timestamp::operator==(const Timestamp& other) const {
    return year == other.year && month == other.month && day ==other.day &&
        hour == other.hour && minute == other.minute && second == other.second &&
        millisecond == other.millisecond;
}

bool Timestamp::operator<=(const Timestamp& other) const {
    return *this < other || *this == other;
}

std::string Timestamp::toString() const {
    char buffer[32];
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
        year, month, day, hour, minute, second, millisecond);
    return std::string(buffer);
}