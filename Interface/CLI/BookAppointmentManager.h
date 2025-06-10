//
// Created by Acer on 08/06/2025.
//

#ifndef BOOKAPPOINTMENTMANAGER_H
#define BOOKAPPOINTMENTMANAGER_H
#include <chrono>
#include <string>

#include "../../Core/PersonData/Doctor.h"
#include "../../Core/PersonData/Patient.h"

namespace ManagerBooking {

    void SearchPatient(const std::string& param);
    void SearchPatientByID(int id);
    void SearchPatientByName(const std::string& param);
    void SearchPatientAction(const Data::Patient& patient);
    void DataNotFoundErrorMessageWithOptionToAddNewOne();

    Data::Doctor SearchDoctor(const std::string& param);
    Data::Doctor SearchDoctorByID(int id);
    Data::Doctor SearchDoctorByName(const std::string& name);
    Data::Doctor SearchDoctorAction(const Data::Doctor& doctor);
    void ViewAllAppointment();
    void RemoveFrontQueue();

} // Manager

#endif //BOOKAPPOINTMENTMANAGER_H
