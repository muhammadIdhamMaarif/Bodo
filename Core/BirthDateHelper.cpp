//
// Created by Acer on 07/06/2025.
//

#include "BirthDateHelper.h"

#if __cplusplus >= 202002L
inline BirthDate makeBirthDate(int year, int month, int day) {
    return std::chrono::year{year} /
           std::chrono::month{static_cast<unsigned>(month)} /
           std::chrono::day{static_cast<unsigned>(day)};
}

#else
inline BirthDate makeBirthDate(int year, int month, int day) {
    std::tm date{};
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    return date;
}
#endif
