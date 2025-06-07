//
// Created by Acer on 07/06/2025.
//

#include "CommandLineInterface.h"

#include <iostream>
#include <bits/ostream.tcc>
#include <regex>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
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
            "Choose Doctor's Schedule to Book Appointment",

            // 🔍 Manajemen dan Riwayat Janji Temu
            "View All Appointments for a Patient",
            "Cancel an Appointment",
            "Edit Appointment Schedule",

            // 🧾 Output dan Ekspor
            "Print Appointment Summary",

            // Misc
            "Back to Main Menu",
            "Exit"
        };
        int size = sizeof(menu) / sizeof(menu[0]);
        SelectorBookAppointment(menu, size, Text::BookAppointment);
    }

    void ManagePatientData() {
        const std::string menu[] = {
            // 📌 Manajemen Data Pasien (CRUD)
            "Add New Patient",
            "View All Patients",
            "Search Patient by ID",
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
            "Exit"
        };
        int size = sizeof(menu) / sizeof(menu[0]);
        SelectorManagePatient(menu, size, Text::ManagePatientData);
    }

    void ManageDoctorData() {
        const std::string menu[] = {
            // 📌 Manajemen Data Dokter
             "Add New Doctor",
             "View All Doctors",
             "Search Doctor by ID",
             "Search Doctor by Name",
             "Update Doctor Profile",
             "Delete Doctor",
             "Add Doctor Schedule",
             "Add Doctor Experience",
             "Add Doctor Education History",
             "Add Doctor Review",
             "Add Medical Action / Specialization",
             "View Doctor Full Profile",
             "Filter Doctors by Specialization",
             "Sort Doctors by Name",
             "Sort Doctors by Years of Experience",
             "Generate Doctor Report (TXT)",
             "Save All Data",
             "Load Data from File",

            // Misc
             "Back to Main Menu",
             "Exit"
        };
        int size = sizeof(menu) / sizeof(menu[0]);
        SelectorManageDoctor(menu, size, Text::ManageDoctorData);
    }

    void MainMenuSelector() {
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
                // "View All Available Doctors",
                // "Search Doctor by Specialization",
                // "View Doctor's Available Schedules",
                // "Search Doctor by Name or ID",
                //
                // // 👤 Patient identification
                // "Register New Patient",
                //
                // // 📅 Pemilihan Jadwal dan Booking
                // "Choose Doctor's Schedule to Book Appointment",
                //
                // // 🔍 Manajemen dan Riwayat Janji Temu
                // "View All Appointments for a Patient",
                // "Cancel an Appointment",
                // "Edit Appointment Schedule",
                //
                // // 🧾 Output dan Ekspor
                // "Print Appointment Summary",
                //
                // // Misc
                // "Back to Main Menu",
                // "Exit"

                switch (selected) {
                    case 0: ; return;
                    case 1: ; return;
                    case 2: ; return;
                    case 3: ; return;
                    case 4: ; return;
                    case 5: ; return;
                    case 6: ; return;
                    case 7: ; return;
                    case 8: ; return;
                    case 9: ; return;
                    case 10: MainMenuSelector(); return;
                    case 11: Interface::Exit(); return;
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
                // "Add New Patient",
                // "View All Patients",
                // "Search Patient by ID",
                // "Edit Patient Information",
                // "Delete Patient",
                //
                // // 🧬 Manajemen Riwayat Penyakit (DiseaseHistory)
                // "Add Disease History to Patient",
                // "View Patient's Disease History",
                // "Check if Patient Has No Disease History",
                //
                // // 🩺 Manajemen Riwayat Pemeriksaan Medis (MedicalRecord)
                // "Add New Medical Checkup Record",
                // "View All Medical Records",
                //
                // // 📊 Laporan dan Ringkasan (Optional Advanced)
                // "Print Patient Summary",
                // "Export Patient Data to File",
                // "Import Patient Data from File",
                //
                // // Misc
                // "Back to Main Menu",
                // "Exit"

                switch (selected) {
                    case 0: ; return;
                    case 1: ; return;
                    case 2: ; return;
                    case 3: ; return;
                    case 4: ; return;
                    case 5: ; return;
                    case 6: ; return;
                    case 7: ; return;
                    case 8: ; return;
                    case 9: ; return;
                    case 10: ; return;
                    case 11: ; return;
                    case 12: ; return;
                    case 13: MainMenuSelector(); return;
                    case 14: Interface::Exit(); return;
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

             // "Add New Doctor",
             // "View All Doctors",
             // "Search Doctor by ID",
             // "Search Doctor by Name",
             // "Update Doctor Profile",
             // "Delete Doctor",
             // "Add Doctor Schedule",
             // "Add Doctor Experience",
             // "Add Doctor Education History",
             // "Add Doctor Review",
             // "Add Medical Action / Specialization",
             // "View Doctor Full Profile",
             // "Filter Doctors by Specialization",
             // "Sort Doctors by Name",
             // "Sort Doctors by Years of Experience",
             // "Generate Doctor Report (TXT)",
             // "Save All Data",
             // "Load Data from File",
             // "Back to Main Menu",
             // "Exit"

                switch (selected) {
                    case 0: ; return;
                    case 1: ; return;
                    case 2: ; return;
                    case 3: ; return;
                    case 4: ; return;
                    case 5: ; return;
                    case 6: ; return;
                    case 7: ; return;
                    case 8: ; return;
                    case 9: ; return;
                    case 10: ; return;
                    case 11: ; return;
                    case 12: ; return;
                    case 13: ; return;
                    case 14: ; return;
                    case 15: ; return;
                    case 16: ; return;
                    case 17: ; return;
                    case 18: MainMenuSelector(); return;
                    case 19: Interface::Exit(); return;
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



} // CLI