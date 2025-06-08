//
// Created by Acer on 08/06/2025.
//

#ifndef PATIENTMANAGEMENT_H
#define PATIENTMANAGEMENT_H
#include <chrono>
#include <string>

namespace Manager {

    void AddNewPatient();
    std::chrono::year_month_day ParseDate(const std::string& dateStr);

}// Manager

#endif //PATIENTMANAGEMENT_H
