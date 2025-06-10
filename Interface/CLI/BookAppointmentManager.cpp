//
// Created by Acer on 08/06/2025.
//

#include "BookAppointmentManager.h"

#include <iostream>

#include "CommandLineInterface.h"
#include "PatientManagement.h"
#include "../../Core/Abstract/LinkedQueue.h"
#include "../../Core/Helper/ColorList.h"
#include "../../Core/Helper/TextInspector.h"
#include "../../Core/PersonData/Doctor.h"
#include "../../Data/DoctorData.h"
#include "../../Data/PatientData.h"
#include "../../Core/PersonData/BookAppointment.hpp"

namespace ManagerBooking {

    LinkedQueue<Appointment> queue;

    void SearchPatient(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                SearchPatientByID(id);
                return;
            }
        } catch (const std::out_of_range) {
            DataNotFoundErrorMessageWithOptionToAddNewOne();
            return;
        } catch (const std::exception) {
            SearchPatientByName(param);
        }
    }
    void SearchPatientByID(int id) {
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        bool found = false;
        Data::Patient patientFound(false);
        for (const Data::Patient& patient : Database::PatientLinear) {
            if (patient.GetID() == id) {
                found = true;
                patientFound = patient;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessageWithOptionToAddNewOne(); return;}
        SearchPatientAction(patientFound);
    }
    void SearchPatientByName(const std::string& param) {
        Data::Patient* patientFound = Database::Patient.SearchPatient(param);
        if (patientFound == nullptr) { DataNotFoundErrorMessageWithOptionToAddNewOne(); return; }
        SearchPatientAction(*patientFound);
    }

    void SearchPatientAction(const Data::Patient& patient) {

        std::cout << Color::CYAN << Text::DataFound << Color::RESET;
        std::cout << patient.toString();
        std::cout << Color::YELLOW << "\nBook with this patient? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::CYAN << "\n\n   Enter Doctor's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Data::Doctor doctor = ManagerBooking::SearchDoctor(Manager::trim(dummy));
        if (doctor == Data::Doctor(false)) return;

        std::cout << Color::CYAN << "Choose Appointment Date : " << Color::RESET;
        std::string appointmentDate;
        std::getline(std::cin, appointmentDate);
        std::cout << Color::RESET;

        std::cout << Color::CYAN << "Choose Appointment Time : " << Color::RESET;
        std::string appointmentTime;
        std::getline(std::cin, appointmentTime);
        std::cout << Color::RESET;

        std::cout << Color::CYAN << "Choose Reason           : " << Color::RESET;
        std::string reason;
        std::getline(std::cin, reason);
        std::cout << Color::RESET;

        Appointment appointment;
        appointment.setPatientId(patient.GetID());
        appointment.setDoctorId(doctor.GetID());
        appointment.setAppointmentDate(appointmentDate);
        appointment.setAppointmentTime(appointmentTime);
        appointment.setReason(reason);

        queue.Enqueue(appointment);

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::BookSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy1;
        std::getline(std::cin, dummy1);
        CLI::MainMenuSelector();

    }

    void DataNotFoundErrorMessageWithOptionToAddNewOne() {
        std::cout << "\033[2J\033[H";
        std::cout << Color::RED << Text::DataNotFound << Color::RESET;
        std::cout << Color::YELLOW << "\nCreate new patient? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }
        Manager::AddNewPatient();
    }

    Data::Doctor SearchDoctor(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                return SearchDoctorByID(id);
            }
        } catch (const std::out_of_range) {
            Manager::DataNotFoundErrorMessage();
            return Data::Doctor(false);
        } catch (const exception) {
            return SearchDoctorByName(param);
        }
    }
    Data::Doctor SearchDoctorByID(int id) {
        bool found = false;
        Data::Doctor doctorFound(false);
        for (const Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetID() == id) {
                found = true;
                doctorFound = doctor;
                break;
            }
        }
        if (!found) { Manager::DataNotFoundErrorMessage(); return Data::Doctor(false); }
        return SearchDoctorAction(doctorFound);
    }
    Data::Doctor SearchDoctorByName(const std::string& name) {
        Data::Doctor* doctor = Database::DoctorAVL.Search(name);
        if (doctor == nullptr) { Manager::DataNotFoundErrorMessage(); Data::Doctor(false); }
        return SearchDoctorAction(*doctor);
    }
    Data::Doctor SearchDoctorAction(const Data::Doctor& doctor) {
        std::cout << Color::CYAN << Text::DataFound << Color::RESET;
        std::cout << doctor.toString(-1);
        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nBook with this doctor? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return Data::Doctor(false); }

        return doctor;
    }

    void ViewAllAppointment() {
        std::cout << Color::BRIGHT_YELLOW << Text::AllAppointment << Text::AllPatientDataDash << Color::RESET;
        auto* node = queue.GetFront();
        int index = 1;
        while (node) {
            std::cout << "\nAppointment #" << index++ << ": " << node->data << "\n";
            node = node->next;
        }
        std::cout << Color::BRIGHT_YELLOW << Text::AllPatientDataDash << Color::RESET;
        std::cout << Color::YELLOW << Text::AllPatientDataConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void RemoveFrontQueue() {
        queue.Dequeue();
        Interface::TextRainbowDiagonalColor(R"(
  ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
 |___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
  _    ___            _      ___                      ___                          _    _
 | |  | __| _ ___ _ _| |_   / _ \ _  _ ___ _  _ ___  | _ \___ _ __  _____ _____ __| |  | |
 | |  | _| '_/ _ \ ' \  _| | (_) | || / -_) || / -_) |   / -_) '  \/ _ \ V / -_) _` |  | |
 | |  |_||_| \___/_||_\__|  \__\_\\_,_\___|\_,_\___| |_|_\___|_|_|_\___/\_/\___\__,_|  | |
 |_|                                                                                   |_|
  ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
 |___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|

)");
        //  "======================================================================================="
        std::cout << Color::YELLOW <<
            "=====================     Press \"Enter\" to return to Main Menu     =====================" << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

} // Manager