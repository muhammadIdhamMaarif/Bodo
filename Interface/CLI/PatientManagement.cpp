//
// Created by Acer on 08/06/2025.
//

#include "PatientManagement.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>

#include "CommandLineInterface.h"
#include "../../Core/Helper/ColorList.h"
#include "../../Core/Helper/TextInspector.h"
#include "../../Core/PersonData/Patient.h"
#include "../../Data/PatientData.h"
#include <limits>

namespace Manager {

    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) {
            return ""; // String is all whitespace
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    Data::Patient PatientInputField() {
        std::string nama, tempatLahir, tanggalLahir, jenisKelamin, golonganDarah,
                    alamat, agama, nomorTelepon, email;
        DiseaseHistory riwayatPenyakit;

        Data::Patient newPatient(false);

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

        std::cout << Color::YELLOW   << "Disease History       : \n" << Color::RESET;
        std::cout << Color::GREEN    << "    If done, press \"Enter\" with blank input.\n" << Color::RESET;
        while (true) {
            std::string temp;
            std::cout << Color::CYAN << "     > " << Color::RESET;
            std::getline(std::cin, temp);
            if (temp == "") break;
            riwayatPenyakit.AddDisease(temp);
        }
        std::cout << Color::BRIGHT_YELLOW << "Submit Patient? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); }
        else {
            try {
                newPatient.SetTanggalLahir(ParseDate(tanggalLahir));
                newPatient.SetAgama(trim(agama));
                newPatient.SetAlamat(trim(alamat));
                newPatient.SetGolonganDarah(trim(golonganDarah));
                newPatient.SetJenisKelamin(jenisKelamin[0]);
                newPatient.SetEmail(trim(email));
                newPatient.SetNama(trim(nama));
                newPatient.SetNomorTelepon(trim(nomorTelepon));
                newPatient.SetTempatLahir(trim(tempatLahir));
                newPatient.SetRiwayatPenyakit(riwayatPenyakit);
            } catch (exception& e) {
                std::string dummy;
                std::cout << Color::RED << "\nPlease enter the correct format!\n" << Color::BRIGHT_YELLOW << "Press \"Enter\" back to Main Menu\n" << Color::RESET;
                std::getline(std::cin, dummy);
                CLI::MainMenuSelector();
                return NULL;
            }

            return newPatient;
        }
    }

    void AddNewPatient() {
        std::cout << Color::BRIGHT_YELLOW << Text::InsertPatient << Color::RESET;

        Data::Patient newPatient;
        newPatient = PatientInputField();
        if (newPatient == NULL) return;

        Database::Patient.AddPatient(newPatient);
        Database::PatientLinear.push_back(newPatient);
        std::cout << "\033[2J\033[H";

        Interface::TextRainbowDiagonalColor(Text::PatientSuccessfullyAdded);
        std::cout << Color::BRIGHT_YELLOW <<  Text::PatientAddedSuccessfullyConfirmation << Color::RESET;

        std::string dummy;
        std::getline(std::cin, dummy);

        CLI::MainMenuSelector();
        return;
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

    void SearchPatient(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                SearchPatientByID(id);
                return;
            }
        } catch (const std::out_of_range& e) {
            DataNotFoundErrorMessage();
            return;
        } catch (const exception& e) {
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
        if (!found) { DataNotFoundErrorMessage(); return;}

        std::cout << Color::CYAN << Text::DataFound << Color::RESET;

        std::cout << patientFound.toString();

        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }
    void SearchPatientByName(const std::string& param) {
        Data::Patient* foundPatient = Database::Patient.SearchPatient(param);
        if (foundPatient == nullptr) { DataNotFoundErrorMessage(); return; }

        std::cout << Color::CYAN << Text::DataFound << Color::RESET;

        std::cout << foundPatient->toString();

        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void DataNotFoundErrorMessage() {
        std::cout << "\033[2J\033[H";
        std::cout << Color::RED << Text::DataNotFound << Color::YELLOW << Text::PatientAddedSuccessfullyConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void ViewAllPatients() {
        std::cout << Color::YELLOW << Text::AllPatientData << Color::RESET;
        std::cout << Color::YELLOW << Text::AllPatientDataDash << Color::RESET << "\n\n";
        for (const Data::Patient& pasien : Database::PatientLinear) {
            std::cout << pasien.toString() << "\n\n";
        }
        std::cout << Color::YELLOW << Text::AllPatientDataDash << Color::RESET;
        std::cout << Color::YELLOW << Text::AllPatientDataConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void EditPatientInformation(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                EditPatientInformationByID(id);
                return;
            }
        } catch (const std::out_of_range& e) {
            DataNotFoundErrorMessage();
            return;
        } catch (const exception& e) {
            EditPatientInformationByName(param);
        }
    }
    void EditPatientInformationByID(int id) {
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
        if (!found) { DataNotFoundErrorMessage(); return;}

        std::cout << Color::CYAN << Text::DataFound << Color::RESET;

        std::cout << patientFound.toString();

        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nContinue Edit? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::BRIGHT_YELLOW << Text::PatientEdited << Color::RESET;

        int originalID = patientFound.GetID();

        Data::Patient patientEdited(false);
        patientEdited = PatientInputField();
        patientEdited.SetID(originalID);
        for (Data::Patient& patient : Database::PatientLinear) {
            if (patient.GetID() == id) {
                patient = patientEdited;
                break;
            }
        }

        Data::Patient* patientFoundPointer = Database::Patient.SearchPatient(patientFound.GetNama());

        patientFoundPointer->SetNama(patientEdited.GetNama());
        patientFoundPointer->SetTempatLahir(patientEdited.GetTempatLahir());
        patientFoundPointer->SetTanggalLahir(patientEdited.GetTanggalLahir());
        patientFoundPointer->SetJenisKelamin(patientEdited.GetJenisKelamin());
        patientFoundPointer->SetGolonganDarah(patientEdited.GetGolonganDarah());
        patientFoundPointer->SetAlamat(patientEdited.GetAlamat());
        patientFoundPointer->SetAgama(patientEdited.GetAgama());
        patientFoundPointer->SetNomorTelepon(patientEdited.GetNomorTelepon());
        patientFoundPointer->SetEmail(patientEdited.GetEmail());
        patientFoundPointer->SetRiwayatPenyakit(patientEdited.GetRiwayatPenyakit());

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }
    void EditPatientInformationByName(const std::string& name) {
        Data::Patient* patientFound = Database::Patient.SearchPatient(name);

        if (patientFound == NULL) { DataNotFoundErrorMessage(); return; }

        std::cout << Color::CYAN << Text::DataFound << Color::RESET;

        std::cout << patientFound->toString();

        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nContinue Edit? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        int originalID = patientFound->GetID();
        std::cout << Color::BRIGHT_YELLOW << Text::PatientEdited << Color::RESET;

        Data::Patient editedData(false);
        editedData = PatientInputField();
        editedData.SetID(originalID);

        patientFound->SetID(originalID);
        patientFound->SetNama(editedData.GetNama());
        patientFound->SetTempatLahir(editedData.GetTempatLahir());
        patientFound->SetTanggalLahir(editedData.GetTanggalLahir());
        patientFound->SetJenisKelamin(editedData.GetJenisKelamin());
        patientFound->SetGolonganDarah(editedData.GetGolonganDarah());
        patientFound->SetAlamat(editedData.GetAlamat());
        patientFound->SetAgama(editedData.GetAgama());
        patientFound->SetNomorTelepon(editedData.GetNomorTelepon());
        patientFound->SetEmail(editedData.GetEmail());
        patientFound->SetRiwayatPenyakit(editedData.GetRiwayatPenyakit());

        for (Data::Patient& patient : Database::PatientLinear) {
            if (patient.GetID() == originalID) {
                patient = editedData;
                break;
            }
        }

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void DeletePatient(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                DeletePatientByID(id);
                return;
            }
        } catch (const std::out_of_range& e) {
            DataNotFoundErrorMessage();
            return;
        } catch (const exception& e) {
            DeletePatientByName(param);
        }
    }
    void DeletePatientByID(int id) {
        bool found = false;
        Data::Patient patientFound(false);
        std::vector<Data::Patient>::iterator iteratorDeleted;
        for (auto it = Database::PatientLinear.begin(); it != Database::PatientLinear.end(); ++it) {
            if (it->GetID() == id) {
                patientFound = *it;
                iteratorDeleted = it;
                found = true;
                break;
            }
        }
        if (!found) {
            DataNotFoundErrorMessage();
            return;
        }


        std::cout << Color::RED << Text::DataFound << Color::RESET;

        std::stringstream ssdisease;
        ssdisease << Color::RED <<  "     Riwayat Penyakit: " << "\n";
        int index = 0;
        for (const auto& penyakit : patientFound.GetRiwayatPenyakit().GetDiseases()) {
            ssdisease << Color::RED << "        " << std::setfill('0') << std::setw(3)
               << ++index << ". " << penyakit << "\n" << Color::RESET;
        }

        std::stringstream ss;
        ss << Color::RED << "     ID            : " << Color::RED << patientFound.GetID() << "\n"
           << Color::RED << "     Nama          : " << Color::RED << patientFound.GetNama() << "\n"
           << Color::RED << "     Tempat Lahir  : " << Color::RED << patientFound.GetTempatLahir() << "\n";

#if __cplusplus >= 202002L
        ss << Color::RED << "     Tanggal Lahir : " << Color::RED
           << static_cast<int>(patientFound.GetTanggalLahir().year()) << "-"
           << static_cast<unsigned>(patientFound.GetTanggalLahir().month()) << "-"
           << static_cast<unsigned>(patientFound.GetTanggalLahir().day()) << "\n";
#else
        ss << Color::RED << "     Tanggal Lahir : " << Color::RESET
           << (patientFound.GetTanggalLahir().tm_year + 1900) << "-"
           << (patientFound.GetTanggalLahir().tm_mon + 1) << "-"
           << patientFound.GetTanggalLahir().tm_mday << "\n";
#endif

        ss << Color::RED << "     Jenis Kelamin : " << Color::RED << patientFound.GetJenisKelamin() << "\n"
           << Color::RED << "     Gol. Darah    : " << Color::RED << patientFound.GetGolonganDarah() << "\n"
           << Color::RED << "     Alamat        : " << Color::RED << patientFound.GetAlamat() << "\n"
           << Color::RED << "     Agama         : " << Color::RED << patientFound.GetAgama() << "\n"
           << Color::RED << "     Nomor Telepon : " << Color::RED << patientFound.GetNomorTelepon() << "\n"
           << Color::RED << "     Email         : " << Color::RED << patientFound.GetEmail() << "\n"
           << ssdisease.str() << "";

        std::cout << ss.str();

        std::cout << Color::RED << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nPatient will be deleted permanently and cannot be retrieved again!";
        std::cout << Color::BRIGHT_YELLOW << "\nDelete This User? (" << Color::CYAN << "Y" << Color::BRIGHT_YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        Database::PatientLinear.erase(iteratorDeleted);
        Database::Patient.DeletePatient(patientFound);

        std::cout << "\033[2J\033[H" << Color::RESET; //clear screen
        std::cout << Color::RED << Text::DeleteSuccess << Color::RESET;
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
        return;
    }
    void DeletePatientByName(std::string name) {
        Data::Patient* patientFoundPtr;
        patientFoundPtr = Database::Patient.SearchPatient(name);
        if (patientFoundPtr == nullptr) { DataNotFoundErrorMessage(); return; }
        Data::Patient patientFound(false);
        patientFound = *(patientFoundPtr);

        std::cout << Color::RED << Text::DataFound << Color::RESET;

        std::stringstream ssdisease;
        ssdisease << Color::RED <<  "     Riwayat Penyakit: " << "\n";
        int index = 0;
        for (const auto& penyakit : patientFound.GetRiwayatPenyakit().GetDiseases()) {
            ssdisease << Color::RED << "        " << std::setfill('0') << std::setw(3)
               << ++index << ". " << penyakit << "\n" << Color::RESET;
        }

        std::stringstream ss;
        ss << Color::RED << "     ID            : " << Color::RED << patientFound.GetID() << "\n"
           << Color::RED << "     Nama          : " << Color::RED << patientFound.GetNama() << "\n"
           << Color::RED << "     Tempat Lahir  : " << Color::RED << patientFound.GetTempatLahir() << "\n";

#if __cplusplus >= 202002L
        ss << Color::RED << "     Tanggal Lahir : " << Color::RED
           << static_cast<int>(patientFound.GetTanggalLahir().year()) << "-"
           << static_cast<unsigned>(patientFound.GetTanggalLahir().month()) << "-"
           << static_cast<unsigned>(patientFound.GetTanggalLahir().day()) << "\n";
#else
        ss << Color::RED << "     Tanggal Lahir : " << Color::RESET
           << (patientFound.GetTanggalLahir().tm_year + 1900) << "-"
           << (patientFound.GetTanggalLahir().tm_mon + 1) << "-"
           << patientFound.GetTanggalLahir().tm_mday << "\n";
#endif

        ss << Color::RED << "     Jenis Kelamin : " << Color::RED << patientFound.GetJenisKelamin() << "\n"
           << Color::RED << "     Gol. Darah    : " << Color::RED << patientFound.GetGolonganDarah() << "\n"
           << Color::RED << "     Alamat        : " << Color::RED << patientFound.GetAlamat() << "\n"
           << Color::RED << "     Agama         : " << Color::RED << patientFound.GetAgama() << "\n"
           << Color::RED << "     Nomor Telepon : " << Color::RED << patientFound.GetNomorTelepon() << "\n"
           << Color::RED << "     Email         : " << Color::RED << patientFound.GetEmail() << "\n"
           << ssdisease.str() << "";

        std::cout << ss.str();

        std::cout << Color::RED << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nPatient will be deleted permanently and cannot be retrieved again!";
        std::cout << Color::BRIGHT_YELLOW << "\nDelete This User? (" << Color::CYAN << "Y" << Color::BRIGHT_YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        bool found = false;
        for (auto it = Database::PatientLinear.begin(); it != Database::PatientLinear.end(); ++it) {
            if (it->GetID() == patientFound.GetID()) {
                Database::PatientLinear.erase(it);
                found = true;
                break;
            }
        }
        if (!found) {
            DataNotFoundErrorMessage();
            return;
        }

        Database::Patient.DeletePatient(patientFound);

        std::cout << "\033[2J\033[H" << Color::RESET; //clear screen
        std::cout << Color::RED << Text::DeleteSuccess << Color::RESET;
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
        return;
    }

    void AddDiseaseHistory(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                AddDiseaseHistoryByID(id);
                return;
            }
        } catch (const std::out_of_range& e) {
            DataNotFoundErrorMessage();
            return;
        } catch (const exception& e) {
            AddDiseaseHistoryByName(param);
        }
    }
    void AddDiseaseHistoryByID(int id) {
        bool found = false;
        Data::Patient* patientFound;
        for (Data::Patient& patient : Database::PatientLinear) {
            if (patient.GetID() == id) {
                found = true;
                patientFound = &patient;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}

        std::cout << Color::CYAN << Text::DataFound << Color::RESET;

        std::cout << patientFound->toString();

        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nAdd Disease History? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::BRIGHT_YELLOW << Text::AddDisease << Color::RESET;

        std::vector<std::string> addedDisease;
        std::cout << Color::BRIGHT_YELLOW << "If done, press \"Enter\" with blank input.\n" << Color::RESET;
        while (true) {
            std::string temp;
            std::cout << Color::CYAN << " > " << Color::RESET;
            std::getline(std::cin, temp);
            if (temp == "") break;
            addedDisease.push_back(temp);
        }
        std::cout << Color::BRIGHT_YELLOW << "Submit Updates? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); }

        Data::Patient* patientFoundPtr = Database::Patient.SearchPatient(patientFound->GetNama());
        for (std::string newDisease : addedDisease) {
            patientFound->TambahRiwayatPenyakit(newDisease);
            patientFoundPtr->TambahRiwayatPenyakit(newDisease);
        }

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }
    void AddDiseaseHistoryByName(std::string name) {
        Data::Patient* patientFoundPtr = Database::Patient.SearchPatient(name);
        if (patientFoundPtr == nullptr) { DataNotFoundErrorMessage(); return; }

        bool found = false;
        Data::Patient* patientFound;
        for (Data::Patient& patient : Database::PatientLinear) {
            if (patient.GetID() == patientFoundPtr->GetID()) {
                found = true;
                patientFound = &patient;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}

        std::cout << Color::CYAN << Text::DataFound << Color::RESET;

        std::cout << patientFound->toString();

        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nAdd Disease History? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::BRIGHT_YELLOW << Text::AddDisease << Color::RESET;

        std::vector<std::string> addedDisease;
        std::cout << Color::BRIGHT_YELLOW << "If done, press \"Enter\" with blank input.\n" << Color::RESET;
        while (true) {
            std::string temp;
            std::cout << Color::CYAN << " > " << Color::RESET;
            std::getline(std::cin, temp);
            if (temp == "") break;
            addedDisease.push_back(temp);
        }
        std::cout << Color::BRIGHT_YELLOW << "Submit Updates? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); }

        for (std::string newDisease : addedDisease) {
            patientFound->TambahRiwayatPenyakit(newDisease);
            patientFoundPtr->TambahRiwayatPenyakit(newDisease);
        }

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();

    }

    void AddMedicalCheckupRecord(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                AddMedicalCheckupRecordByID(id);
                return;
            }
        } catch (const std::out_of_range& e) {
            DataNotFoundErrorMessage();
            return;
        } catch (const exception& e) {
            AddMedicalCheckupRecordByName(param);
        }
    }
    void AddMedicalCheckupRecordByID(int id) {
        bool found = false;
        Data::Patient* patientFound;
        for (Data::Patient& patient : Database::PatientLinear) {
            if (patient.GetID() == id) {
                found = true;
                patientFound = &patient;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        Data::Patient* patientFoundPtr = Database::Patient.SearchPatient(patientFound->GetNama());

        std::cout << Color::CYAN << Text::DataFound << Color::RESET;

        std::cout << patientFound->toString();

        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nAdd Medical Checkup Record(s)? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::BRIGHT_YELLOW << Text::MedicalRecords << Color::RESET;

        // Checkup Class
        // std::time_t tanggal;         // Tanggal checkup/treatment
        // std::string dokter;          // Nama doketer
        // std::string keluhan;         // Keluhan pasien
        // std::string tindakan;        // Diagnosis / treatment
        // std::string resep;           // resep dokter dengan tulisanya yang cantik

        // Medical Record Class
        // std::vector<Checkup>

        std::vector<Data::Checkup> checkupList;

        while (true) {
            Data::Checkup newCheckup;
            newCheckup.tanggal = std::time(nullptr);
            std::cout << Color::CYAN << "    Nama Doktor : " << Color::RESET;
            std::getline(std::cin, newCheckup.dokter);
            std::cout << Color::CYAN << "    Keluhan     : " << Color::RESET;
            std::getline(std::cin, newCheckup.keluhan);
            std::cout << Color::CYAN << "    Tindakan    : " << Color::RESET;
            std::getline(std::cin, newCheckup.tindakan);
            std::cout << Color::CYAN << "    Resep       : " << Color::RESET;
            std::getline(std::cin, newCheckup.resep);

            checkupList.push_back(newCheckup);

            std::cout << Color::BRIGHT_YELLOW << "Add more? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
            std::getline(std::cin, inputSubmit);
            std::cout << Color::RESET;
            if (std::toupper(inputSubmit[0]) == 'N') { break; }
        }

        std::cout << Color::BRIGHT_YELLOW << "Submit Records Update(s)? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); }

        for (Data::Checkup& checkup : checkupList) {
            patientFound->TambahMedicalRecords(checkup);
            patientFoundPtr->TambahMedicalRecords(checkup);
        }

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }
    void AddMedicalCheckupRecordByName(std::string name) {
        Data::Patient* patientFoundPtr = Database::Patient.SearchPatient(name);
        if (patientFoundPtr == nullptr) { DataNotFoundErrorMessage(); return; }

        bool found = false;
        Data::Patient* patientFound;
        for (Data::Patient& patient : Database::PatientLinear) {
            if (patient.GetID() == patientFoundPtr->GetID()) {
                found = true;
                patientFound = &patient;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}

        std::cout << Color::CYAN << Text::DataFound << Color::RESET;

        std::cout << patientFound->toString();

        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nAdd Medical Checkup Record(s)? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::BRIGHT_YELLOW << Text::MedicalRecords << Color::RESET;

        // Checkup Class
        // std::time_t tanggal;         // Tanggal checkup/treatment
        // std::string dokter;          // Nama doketer
        // std::string keluhan;         // Keluhan pasien
        // std::string tindakan;        // Diagnosis / treatment
        // std::string resep;           // resep dokter dengan tulisanya yang cantik

        // Medical Record Class
        // std::vector<Checkup>

        std::vector<Data::Checkup> checkupList;

        while (true) {
            Data::Checkup newCheckup;
            newCheckup.tanggal = std::time(nullptr);
            std::cout << Color::CYAN << "    Nama Doktor : " << Color::RESET;
            std::getline(std::cin, newCheckup.dokter);
            std::cout << Color::CYAN << "    Keluhan     : " << Color::RESET;
            std::getline(std::cin, newCheckup.keluhan);
            std::cout << Color::CYAN << "    Tindakan    : " << Color::RESET;
            std::getline(std::cin, newCheckup.tindakan);
            std::cout << Color::CYAN << "    Resep       : " << Color::RESET;
            std::getline(std::cin, newCheckup.resep);

            checkupList.push_back(newCheckup);

            std::cout << Color::BRIGHT_YELLOW << "Add more? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
            std::getline(std::cin, inputSubmit);
            std::cout << Color::RESET;
            if (std::toupper(inputSubmit[0]) == 'N') { break; }
        }

        std::cout << Color::BRIGHT_YELLOW << "Submit Records Update(s)? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); }

        for (Data::Checkup& checkup : checkupList) {
            patientFound->TambahMedicalRecords(checkup);
            patientFoundPtr->TambahMedicalRecords(checkup);
        }

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void ViewPatientMedicalRecord(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                ViewPatientMedicalRecordByID(id);
                return;
            }
        } catch (const std::out_of_range& e) {
            DataNotFoundErrorMessage();
            return;
        } catch (const exception& e) {
            ViewPatientMedicalRecordByName(param);
        }
    }
    void ViewPatientMedicalRecordByID(int id) {
        bool found = false;
        Data::Patient* patientFound;
        for (Data::Patient& patient : Database::PatientLinear) {
            if (patient.GetID() == id) {
                found = true;
                patientFound = &patient;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}


    }
    void ViewPatientMedicalRecordByName(std::string name) {

    }

    void PatientSummary(int id);
    void PatientSummary(std::string name);

    void ExportPatientDataToFile() {
        std::cout << Text::ExportFIle;

        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }
    void ImportPatientDataFromFile() {
        std::cout << Text::ImportFile;

        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

} // Manager