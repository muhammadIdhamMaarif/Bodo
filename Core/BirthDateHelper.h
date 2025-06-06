//
// Created by Acer on 07/06/2025.
//

#ifndef BIRTHDATEHELPER_H
#define BIRTHDATEHELPER_H

#include <ctime>

#if __cplusplus >= 202002L
    #include <chrono>
#endif

using BirthDate =
#if __cplusplus >= 202002L
    std::chrono::year_month_day;
#else
        std::tm;
#endif

BirthDate makeBirthDate(int year, int month, int day);

#endif //BIRTHDATEHELPER_H
