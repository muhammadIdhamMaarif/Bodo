//
// Created by Acer on 08/06/2025.
//

#include "PatientManagement.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

#include "CommandLineInterface.h"
#include "../../Core/Helper/ColorList.h"
#include "../../Core/Helper/TextInspector.h"
#include "../../Core/PersonData/Patient.h"
#include "../../Data/PatientData.h"

namespace Manager {

    void AddNewPatient() {
        std::string nama, tempatLahir, tanggalLahir, jenisKelamin, golonganDarah,
                    alamat, agama, nomorTelepon, email;
        DiseaseHistory riwayatPenyakit;

        std::cout << Color::BRIGHT_YELLOW << Text::InsertPatient << Color::RESET;

        Data::Patient newPatient;

        std::cout << Color::CYAN << "Full Name             : " << Color::RESET;
        std::getline(std::cin, nama);
        std::cout << Color::CYAN << "Birth Place           : " << Color::RESET;
        std::getline(std::cin, tempatLahir);
        std::cout << Color::CYAN << "Birthday (DD-MM-YYYY) : " << Color::RESET;
        std::getline(std::cin, tanggalLahir);
        std::cout << Color::CYAN << "Sex (M/F/O)           : " << Color::RESET;
        std::getline(std::cin, jenisKelamin);
        std::cout << Color::CYAN << "Blood Type            : " << Color::RESET;
        std::getline(std::cin, golonganDarah);
        std::cout << Color::CYAN << "Address               : " << Color::RESET;
        std::getline(std::cin, alamat);
        std::cout << Color::CYAN << "Religion              : " << Color::RESET;
        std::getline(std::cin, agama);
        std::cout << Color::CYAN << "Phone Number          : " << Color::RESET;
        std::getline(std::cin, nomorTelepon);
        std::cout << Color::CYAN << "Email                 : " << Color::RESET;
        std::getline(std::cin, email);

        std::cout << Color::YELLOW   << "Medical Records       : \n" << Color::RESET;
        std::cout << Color::GREEN    << "    If done, press \"Enter\" with blank input.\n" << Color::RESET;
        while (true) {
            std::string temp;
            std::cout << Color::CYAN << "     > " << Color::RESET;
            std::getline(std::cin, temp);
            if (temp == "") break;
            riwayatPenyakit.AddDisease(temp);
        }
        std::cout << Color::BRIGHT_YELLOW << "Submit Patient? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? ";
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); }
        else {
            try {
                newPatient.SetTanggalLahir(ParseDate(tanggalLahir));
                newPatient.SetAgama(agama);
                newPatient.SetAlamat(alamat);
                newPatient.SetGolonganDarah(golonganDarah);
                newPatient.SetJenisKelamin(jenisKelamin[0]);
                newPatient.SetEmail(email);
                newPatient.SetNama(nama);
                newPatient.SetNomorTelepon(nomorTelepon);
                newPatient.SetTempatLahir(tempatLahir);
                newPatient.SetRiwayatPenyakit(riwayatPenyakit);
            } catch (exception& e) {
                std::string dummy;
                std::cout << Color::RED << "\nPlease enter the correct format!\n" << Color::BRIGHT_YELLOW << "Press \"Enter\" back to Main Menu\n" << Color::RESET;
                std::getline(std::cin, dummy);
                CLI::MainMenuSelector();
                return;
            }

            Database::Patient.AddPatient(newPatient);
            std::cout << "\033[2J\033[H";

            Interface::TextRainbowDiagonalColor(Text::PatientSuccessfullyAdded);
            std::cout << Color::BRIGHT_YELLOW <<  Text::PatientAddedSuccessfullyConfirmation << Color::RESET;

            std::string dummy;
            std::getline(std::cin, dummy);

            CLI::MainMenuSelector();
            return;
        }
    }

    std::chrono::year_month_day ParseDate(const std::string& dateStr) {
        char dash1, dash2;
        int hari, bulan, tahun;
        std::istringstream iss(dateStr);

        // Extract values from "DD-MM-YYYY"
        if (iss >> hari >> dash1 >> bulan >> dash2 >> tahun && dash1 == '-' && dash2 == '-') {
            using namespace std::chrono;
            return year_month_day{year{tahun}, month{static_cast<unsigned>(bulan)}, day{static_cast<unsigned>(hari)}};
        } else {
            throw std::runtime_error("Invalid date format: expected DD-MM-YYYY");
        }
    }



} // Manager