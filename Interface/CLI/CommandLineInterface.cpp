//
// Created by Acer on 07/06/2025.
//

#include "CommandLineInterface.h"

#include <iostream>
#include <bits/ostream.tcc>
#include <regex>
#include "BookAppointmentManager.h"
#include "DoctorManager.h"
#include "PatientManagement.h"
#include "../../StreamingAssets/SaveLoad.hpp"
#include "BookAppointmentManager.h"

#ifdef _WIN32
    #define STRICT
    #define WIN32_LEAN_AND_MEAN
    #include <conio.h>
    #include <windows.h>
    #undef byte
#else
    #include <termios.h>
    #include <unistd.h>
    #include <cstdio>
#endif


namespace CLI {

    void OnCommandLineInterface() {
        MainMenuSelector();
    }

    // pengganti _getch() di non windows
    int GetKeyPress() {
        #ifdef _WIN32
            return _getch();
        #else
            struct termios oldt, newt;
            int ch;
            tcgetattr(STDIN_FILENO, &oldt);          // buat dapetin attribut terminal terkini
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);        // matiin buffering ama echo
            tcsetattr(STDIN_FILENO, TCSANOW, &newt); // pasang settings baru
            ch = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // balikin settings lama
            return ch;
        #endif
    }

    std::string SetWhitespaces(std::string s) {
        return (std::string(59 - s.length(), ' ') + "| |\n");
    }

    void SetColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void BookDoctorAppointment() {
        const std::string menu[] = {
            // 🗓️ Booked appointment with doctor
            "View All Available Doctors",
            "Search Doctor by Specialization",
            "View Doctor's Available Schedules",
            "Search Doctor by Name or ID",

            // 👤 Patient identification
            "Register New Patient",

            // 📅 Pemilihan Jadwal dan Booking
            "Book Appointment",

            // 🔍 Manajemen dan Riwayat Janji Temu
            "View All Appointments",
            "Remove Front Queue",

            // 🧾 Output dan Ekspor
            "Print Appointment Summary",

            // Misc
            "Back to Main Menu",
        };
        int size = sizeof(menu) / sizeof(menu[0]);
        SelectorBookAppointment(menu, size, Text::BookAppointment);
    }

    void ManagePatientData() {
        const std::string menu[] = {
            // 📌 Manajemen Data Pasien (CRUD)
            "Add New Patient",
            "View All Patients",
            "Search Patient",
            "Edit Patient Information",
            "Delete Patient",

            // 🧬 Manajemen Riwayat Penyakit (DiseaseHistory)
            "Add Disease History to Patient",
            "View Patient's Disease History",
            "Check if Patient Has No Disease History",

            // 🩺 Manajemen Riwayat Pemeriksaan Medis (MedicalRecord)
            "Add New Medical Checkup Record",
            "View All Medical Records",

            // 📊 Laporan dan Ringkasan (Optional Advanced)
            "Print Patient Summary",
            "Export Patient Data to File",
            "Import Patient Data from File",

            // Misc
            "Back to Main Menu",
        };
        int size = sizeof(menu) / sizeof(menu[0]);
        SelectorManagePatient(menu, size, Text::ManagePatientData);
    }

    void ManageDoctorData() {
        const std::string menu[] = {
            // 📌 Manajemen Data Dokter
             "Add New Doctor",
             "View All Doctors",
             "Search Doctor",
             "Update Doctor Profile",
             "Delete Doctor",
             "Add Doctor Schedule",
             "Add Doctor Experience",
             "Add Doctor Education History",
             "Add Doctor Review",
             "Add Medical Action / Specialization",
             "Filter Doctors by Specialization",
             "Sort Doctors by Name",

            // Misc
             "Back to Main Menu",
        };
        int size = sizeof(menu) / sizeof(menu[0]);
        SelectorManageDoctor(menu, size, Text::ManageDoctorData);
    }

    void MainMenuSelector() {
        SLManager::SaveData();
        const std::string menu[] = {
            "Book Doctor Appointment",
            "Manage Patient Data",
            "Manage Doctor Data",
            "Exit"
        };
        int size = sizeof(menu) / sizeof(menu[0]);
        SelectorMainMenu(menu, size, CommandLineMainMenuHeader);
    }

    void SelectorBookAppointment(const std::string menu[], const int numChoices, std::string header) {

        int selected = 0;

        while (true) {
            DrawMenu(menu, numChoices, selected, header);
            int key = GetKeyPress();

            if (key == 224) { // Arrow key prefix
                int arrow = GetKeyPress();
                if (arrow == KEY_UP) {
                    selected = (selected - 1 + numChoices) % numChoices;
                } else if (arrow == KEY_DOWN) {
                    selected = (selected + 1) % numChoices;
                }
            } else if (key == KEY_ENTER) {
                system("cls");
                // // 🗓️ Booked appointment with doctor
                // 0 "View All Available Doctors",
                // 1 "Search Doctor by Specialization",
                // 2 "View Doctor's Available Schedules",
                // 3 "Search Doctor by Name or ID",
                //
                // // 👤 Patient identification
                // 4 "Register New Patient",
                //
                // // 📅 Pemilihan Jadwal dan Booking
                // 5 "Book Appointment",
                //
                // // 🔍 Manajemen dan Riwayat Janji Temu
                // 6 "View All Appointments",
                // 7 "Remove Front Queue",
                //
                // // 🧾 Output dan Ekspor
                // 8 "Print Appointment Summary",
                //
                // // Misc
                // "Back to Main Menu",
                // "Exit"

                switch (selected) {
                    case 0: Manager::ViewAllDoctor(); return;
                    case 1: Manager::FilterDoctorBySpecialization(); return;
                    case 2: Manager::ViewAllDoctor(); return;
                    case 3: DoctorSearch(); return;
                    case 4: Manager::AddNewPatient(); return;
                    case 5: BookAppointment(); return;
                    case 6: ManagerBooking::ViewAllAppointment(); return;
                    case 7: ManagerBooking::RemoveFrontQueue(); return;
                    case 8: ManagerBooking::ViewAllAppointment(); return;
                    case 9: MainMenuSelector(); return;
                }
                std::cout << "\nPress any key to return to menu...";
                GetKeyPress();
            }
        }
    }

    void SelectorManagePatient(const std::string menu[], const int numChoices, std::string header) {

        int selected = 0;

        while (true) {
            DrawMenu(menu, numChoices, selected, header);
            int key = GetKeyPress();

            if (key == 224) { // Arrow key prefix
                int arrow = GetKeyPress();
                if (arrow == KEY_UP) {
                    selected = (selected - 1 + numChoices) % numChoices;
                } else if (arrow == KEY_DOWN) {
                    selected = (selected + 1) % numChoices;
                }
            } else if (key == KEY_ENTER) {
                system("cls");
                // 📌 Manajemen Data Pasien (CRUD)
                // 0 "Add New Patient",
                // 1 "View All Patients",
                // 2 "Search Patient",
                // 3 "Edit Patient Information",
                // 4 "Delete Patient",
                //
                // // 🧬 Manajemen Riwayat Penyakit (DiseaseHistory)
                // 5 "Add Disease History to Patient",
                // 6 "View Patient's Disease History",
                // 7 "Check if Patient Has No Disease History",
                //
                // // 🩺 Manajemen Riwayat Pemeriksaan Medis (MedicalRecord)
                // 8 "Add New Medical Checkup Record",
                // 9 "View All Medical Records",
                //
                // // 📊 Laporan dan Ringkasan (Optional Advanced)
                // 10 "Print Patient Summary",
                // 11 "Export Patient Data to File",
                // 12 "Import Patient Data from File",
                //
                // // Misc
                // "Back to Main Menu",
                // "Exit"

                switch (selected) {
                    case 0: Manager::AddNewPatient(); return;
                    case 1: Manager::ViewAllPatients(); return;
                    case 2: SearchByIDCase(); return;
                    case 3: EditPatient(); return;
                    case 4: DeletePatient(); return;
                    case 5: AddDisease(); return;
                    case 6: SearchByIDCase(); return;
                    case 7: SearchByIDCase(); return;
                    case 8: AddMC(); return;
                    case 9: Manager::ViewAllPatients(); return;
                    case 10: SearchByIDCase(); return;
                    case 11: Manager::ExportPatientDataToFile(); return;
                    case 12: Manager::ImportPatientDataFromFile(); return;
                    case 13: MainMenuSelector(); return;
                }
                std::cout << "\nPress any key to return to menu...";
                GetKeyPress();
            }
        }
    }

    void SelectorManageDoctor(const std::string menu[], const int numChoices, std::string header) {

        int selected = 0;

        while (true) {
            DrawMenu(menu, numChoices, selected, header);
            int key = GetKeyPress();

            if (key == 224) { // Arrow key prefix
                int arrow = GetKeyPress();
                if (arrow == KEY_UP) {
                    selected = (selected - 1 + numChoices) % numChoices;
                } else if (arrow == KEY_DOWN) {
                    selected = (selected + 1) % numChoices;
                }
            } else if (key == KEY_ENTER) {
                system("cls");

               //  // 📌 Manajemen Data Dokter
               //  0 "Add New Doctor",
               //  1 "View All Doctors",
               //  2 "Search Doctor",
               //  3 "Update Doctor Profile",
               //  4 "Delete Doctor",
               //  5 "Add Doctor Schedule",
               //  6 "Add Doctor Experience",
               //  7 "Add Doctor Education History",
               //  8 "Add Doctor Review",
               //  9 "Add Medical Action / Specialization",
               //  10 "Filter Doctors by Specialization",
               //  11 "Sort Doctors by Name",
               //
               // // Misc
               //  "Back to Main Menu",

                switch (selected) {
                    case 0: Manager::AddNewDoctor(); return;
                    case 1: Manager::ViewAllDoctor(); return;
                    case 2: DoctorSearch(); return;
                    case 3: DoctorUpdate(); return;
                    case 4: DoctorDelete(); return;
                    case 5: DoctorAddSesiPraktik(); return;
                    case 6: DoctorAddPengalamanPraktik(); return;
                    case 7: DoctorAddRiwayatPendidikan(); return;
                    case 8: DoctorAddUlasanDokter(); return;
                    case 9: DoctorAddTindakanSpesialis(); return;
                    case 10: Manager::FilterDoctorBySpecialization(); return;
                    case 11: Manager::ViewAllDoctor(); return;
                    case 12: MainMenuSelector(); return;
                }
                std::cout << "\nPress any key to return to menu...";
                GetKeyPress();
            }
        }
    }

    void SelectorMainMenu(const std::string menu[], const int numChoices, std::string header) {

        int selected = 0;

        while (true) {
            DrawMenu(menu, numChoices, selected, header);
            int key = GetKeyPress();

            if (key == 224) { // Arrow key prefix
                int arrow = GetKeyPress();
                if (arrow == KEY_UP) {
                    selected = (selected - 1 + numChoices) % numChoices;
                } else if (arrow == KEY_DOWN) {
                    selected = (selected + 1) % numChoices;
                }
            } else if (key == KEY_ENTER) {
                system("cls");
                switch (selected) {
                    case 0: BookDoctorAppointment(); return;
                    case 1: ManagePatientData(); return;
                    case 2: ManageDoctorData(); return;
                    case 3: Interface::Exit(); return;
                }
                std::cout << "\nPress any key to return to menu...";
                GetKeyPress();
            }
        }
    }

    void DrawMenu(const std::string choices[], int size, int selected, std::string header) {
        system("cls");
        std::cout << BRIGHT_YELLOW << header << RESET;
        std::cout << BRIGHT_YELLOW << "  _                                                                 _ \n";
        std::cout << BRIGHT_YELLOW << " | | " << YELLOW << UpDownArrowEnterText << "           " << BRIGHT_YELLOW << "| |\n" << RESET;

        for (int i = 0; i < size; i++) {
            if (i == selected) {
                SetColor(14); // Yellow
                std::cout << " | |  ";
                SetColor(11); // Cyan
                std::cout << "> " << choices[i];
                SetColor(14); //Yellow
                std::cout << SetWhitespaces(choices[i]);
                SetColor(7);  // Reset ke default
            }

            else {
                SetColor(14); // Yellow
                std::cout << " | |    ";
                SetColor(7); // Default
                std::cout << choices[i];
                SetColor(14); // Yellow
                std::cout << SetWhitespaces(choices[i]);
                SetColor(7); // Default
            }
        }
        std::cout << BRIGHT_YELLOW << " |_|                                                               |_|\n" << RESET;
        std::cout << BRIGHT_YELLOW << CommandLineMainMenuDash << RESET;
    }

    void SearchByIDCase() {
        std::cout << Color::CYAN << "\n\n   Enter Patient's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::SearchPatient(Manager::trim(dummy));
    }

    void EditPatient() {
        std::cout << Color::CYAN << "\n\n   Enter Patient's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::EditPatientInformation(Manager::trim(dummy));
    }

    void DeletePatient() {
        std::cout << Color::CYAN << "\n\n   Enter Patient's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::DeletePatient(Manager::trim(dummy));
    }

    void AddDisease() {
        std::cout << Color::CYAN << "\n\n   Enter Patient's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::AddDiseaseHistory(Manager::trim(dummy));
    }

    void PermissionDenied() {
        std::cout << Color::RED << Text::PermissionDenied << Color::RESET;

        std::cout << Color::YELLOW << Text::AllPatientDataConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void AddMC() {
        std::cout << Color::CYAN << "\n\n   Enter Patient's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::AddMedicalCheckupRecord(Manager::trim(dummy));
    }

    void ViewMC() {
        std::cout << Color::CYAN << "\n\n   Enter Patient's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::ViewPatientMedicalRecord(Manager::trim(dummy));
    }

    void DoctorSearch() {
        std::cout << Color::CYAN << "\n\n   Enter Doctor's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::SearchDoctor(Manager::trim(dummy));
    }

    void DoctorUpdate() {
        std::cout << Color::CYAN << "\n\n   Enter Doctor's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::UpdateDoctor(Manager::trim(dummy));
    }

    void DoctorDelete() {
        std::cout << Color::CYAN << "\n\n   Enter Doctor's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::DeleteDoctor(Manager::trim(dummy));
    }

    void DoctorAddSesiPraktik() {
        std::cout << Color::CYAN << "\n\n   Enter Doctor's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::AddDoctorSchedule(Manager::trim(dummy));
    }

    void DoctorAddPengalamanPraktik() {
        std::cout << Color::CYAN << "\n\n   Enter Doctor's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::AddDoctorExperience(Manager::trim(dummy));
    }

    void DoctorAddRiwayatPendidikan() {
        std::cout << Color::CYAN << "\n\n   Enter Doctor's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::AddDoctorEducationHistory(Manager::trim(dummy));
    }

    void DoctorAddUlasanDokter() {
        std::cout << Color::CYAN << "\n\n   Enter Doctor's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::AddDoctorReview(Manager::trim(dummy));
    }

    void DoctorAddTindakanSpesialis() {
        std::cout << Color::CYAN << "\n\n   Enter Doctor's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        Manager::AddMedicalSpecialization(Manager::trim(dummy));
    }

    void BookAppointment() {
        std::cout << Color::YELLOW << Text::BookAppointmentText;
        std::cout << Color::CYAN << "\n\n   Enter Doctor's ID or Full Name : " << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        ManagerBooking::SearchPatient(Manager::trim(dummy));
    }

} // CLI
