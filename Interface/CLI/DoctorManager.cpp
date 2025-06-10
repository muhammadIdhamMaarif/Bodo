//
// Created by Acer on 08/06/2025.
//

#include "DoctorManager.h"

#include <iostream>

#include "CLI11.hpp"
#include "CommandLineInterface.h"
#include "PatientManagement.h"
#include "../../Core/Helper/ColorList.h"
#include "../../Data/DoctorData.h"
#include "../../StreamingAssets/json.hpp"

// struct Ulasan {
//     time_t tanggal;
//     std::string nama;     // Nama Pengulas
//     std::string komentar;       // Komentar
//     int rating;                 // Dari 1-5
// };
//
// struct RumahSakit {
//     std::string nama;           // Nama Rumah Sakit
//     std::string lokasi;         // "Jl, Desa, Kecamatan, Kota, Provinsi"
//     std::string jamBuka;        // "24 hours", "08:00-23:00"
//     std::string nomorTelepon;   // "(SO41) 47OIOS"
//     Ulasan ulasan;              // "Yuita", "Gacor Rumah Sakitnya" "5"
//     std::string penghargaan;    // "1st Best Hospital in Malang by Ministry of Health"
//
//     [[nodiscard]] std::string GetNamaRumahSakit() const { return nama; }
// };
//
// struct SesiPraktik {
//     std::string hari;           // Contoh: "Senin"
//     std::string jamMulai;       // Format: "08:00"
//     std::string jamSelesai;     // Format: "10:00"
//     std::string sesi;           // Contoh: "Pagi" / "Sore"
// };
//
// struct PengalamanPraktik {
//     std::string;      // "RSUD Kota Molang"
//     std::string waktu;          // "13 Tahun 9 Bulan"
//     std::string jabatan;        // "Chief Financial Officer"
// };

namespace Manager {

    std::optional<int> safeStringToInt(const std::string& input) {
        try {
            size_t idx;
            int result = std::stoi(input, &idx);

            // Check if the entire string was parsed (no junk after number)
            if (idx == input.length())
                return result;
            else
                return std::nullopt;

        } catch (...) {
            return std::nullopt;
        }
    }

    time_t convertToTimeT(const std::string& dateStr) {
        int day, month, year;
        char sep1, sep2;

        std::istringstream iss(dateStr);
        iss >> day >> sep1 >> month >> sep2 >> year;

        if (sep1 != '-' || sep2 != '-' || iss.fail()) {
            std::cerr << "Invalid date format!" << std::endl;
            return -1;
        }

        struct tm timeInfo = {};
        timeInfo.tm_mday = day;
        timeInfo.tm_mon = month - 1;
        timeInfo.tm_year = year - 1900;
        timeInfo.tm_hour = 0;
        timeInfo.tm_min = 0;
        timeInfo.tm_sec = 0;

        return mktime(&timeInfo);
    }

    Data::Doctor DoctorInputField() {
        std::string nama, tempatLahir, tanggalLahir, jenisKelamin, golonganDarah,
                    alamat, agama, nomorTelepon, email, profilDokter, spesialis;

        bool valid = true;

        std::vector<SesiPraktik>        sesiPraktik;
        std::vector<PengalamanPraktik>  pengalamanPraktikDokter;
        std::vector<std::string>        riwayatPendidikan;
        std::vector<Ulasan>             ulasanDokter;
        std::vector<std::string>        tindakanSpesialis;

        Data::Doctor newDoctor(false);

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
        std::cout << Color::CYAN << "Doctor Profile        : \n" << Color::CYAN_VIBRANT << " > " << Color::RESET;
        std::getline(std::cin, profilDokter);
        std::cout << Color::CYAN << "Specialist            : " << Color::RESET;
        std::getline(std::cin, spesialis);

        std::cout << Color::YELLOW   << "Practice Schedule     : \n" << Color::RESET;
        int index = 1;
        while (true) {
            SesiPraktik newSesiPraktik;
            std::cout << Color::CYAN_VIBRANT << "     > Schedule " << index++ << "\n" << Color::RESET;
            std::cout << Color::CYAN         << "           Day Name (Sunday, .. ) : " << Color::RESET;
            std::getline(std::cin, newSesiPraktik.hari);
            std::cout << Color::CYAN         << "           Start Hour (00:00)     : " << Color::RESET;
            std::getline(std::cin, newSesiPraktik.jamMulai);
            std::cout << Color::CYAN         << "           End Hour (00:00)       : " << Color::RESET;
            std::getline(std::cin, newSesiPraktik.jamSelesai);
            std::cout << Color::CYAN         << "           Session (Day,Night)    : " << Color::RESET;
            std::getline(std::cin, newSesiPraktik.sesi);

            sesiPraktik.push_back(newSesiPraktik);

            std::cout << Color::BRIGHT_YELLOW << "\nAdd More? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
            std::string inputSubmit;
            std::getline(std::cin, inputSubmit);
            if (std::toupper(inputSubmit[0]) != 'Y') { break; }
            std::cout << '\n';
        }

        std::cout << Color::YELLOW   << "Doctor's Experience   : \n" << Color::RESET;
        index = 1;
        while (true) {
            PengalamanPraktik newPengalamanPraktik;
            std::cout << Color::CYAN_VIBRANT << "     > Experience " << index++ << "\n" << Color::RESET;
            std::cout << Color::CYAN         << "           Hospital Name          : " << Color::RESET;
            std::getline(std::cin, newPengalamanPraktik.rumahSakit);
            std::cout << Color::CYAN         << "           Position               : " << Color::RESET;
            std::getline(std::cin, newPengalamanPraktik.jabatan);
            std::cout << Color::CYAN         << "           Year Worked            : " << Color::RESET;
            std::getline(std::cin, newPengalamanPraktik.waktu);

            pengalamanPraktikDokter.push_back(newPengalamanPraktik);

            std::cout << Color::BRIGHT_YELLOW << "\nAdd More? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
            std::string inputSubmit;
            std::getline(std::cin, inputSubmit);
            if (std::toupper(inputSubmit[0]) != 'Y') { break; }
            std::cout << '\n';
        }

        std::cout << Color::YELLOW   << "Doctor Education      : \n" << Color::RESET;
        std::cout << Color::GREEN    << "    If done, press \"Enter\" with blank input.\n" << Color::RESET;
        while (true) {
            std::string temp;
            std::cout << Color::CYAN << "     > " << Color::RESET;
            std::getline(std::cin, temp);
            if (temp == "") break;
            riwayatPendidikan.push_back(temp);
        }

        std::cout << Color::YELLOW   << "Doctor's Reviews      : \n" << Color::RESET;
        index = 1;
        while (true) {
            Ulasan newUlasan;
            std::string dateInput, ratingInput;
            std::cout << Color::CYAN_VIBRANT << "     > Reviews " << index++ << "\n" << Color::RESET;
            std::cout << Color::CYAN         << "           Date (DD-MM-YYYY)      : " << Color::RESET;
            std::getline(std::cin, dateInput);
            newUlasan.tanggal = convertToTimeT(dateInput);
            std::cout << Color::CYAN         << "           Username               : " << Color::RESET;
            std::getline(std::cin, newUlasan.nama);
            std::cout << Color::CYAN         << "           Comment                : " << Color::RESET;
            std::getline(std::cin, newUlasan.komentar);
            std::cout << Color::CYAN         << "           Rating (1-5)           : " << Color::RESET;
            std::getline(std::cin, ratingInput);
            auto rating = safeStringToInt(ratingInput);
            if (rating && *rating >= 1 && *rating <= 5) {
                newUlasan.rating = *rating;
            } else {
                valid = false;
            }

            ulasanDokter.push_back(newUlasan);

            std::cout << Color::BRIGHT_YELLOW << "\nAdd More? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
            std::string inputSubmit;
            std::getline(std::cin, inputSubmit);
            if (std::toupper(inputSubmit[0]) != 'Y') { break; }
            std::cout << '\n';
        }


        std::cout << Color::YELLOW   << "Doctor Medical Action : \n" << Color::RESET;
        std::cout << Color::GREEN    << "    If done, press \"Enter\" with blank input.\n" << Color::RESET;
        while (true) {
            std::string temp;
            std::cout << Color::CYAN << "     > " << Color::RESET;
            std::getline(std::cin, temp);
            if (temp == "") break;
            tindakanSpesialis.push_back(temp);
        }

        std::cout << Color::BRIGHT_YELLOW << "Submit Doctor? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return NULL; }
        else {
            try {
                if (!valid) throw std::runtime_error("Invalid input data");
                newDoctor.SetNama(trim(nama));
                newDoctor.SetTempatLahir(trim(tempatLahir));
                newDoctor.SetTanggalLahir(ParseDate(tanggalLahir));
                newDoctor.SetJenisKelamin(jenisKelamin[0]);
                newDoctor.SetGolonganDarah(trim(golonganDarah));
                newDoctor.SetAlamat(trim(alamat));
                newDoctor.SetAgama(trim(agama));
                newDoctor.SetNomorTelepon(trim(nomorTelepon));
                newDoctor.SetEmail(trim(email));
                newDoctor.SetProfilDokter(trim(profilDokter));
                newDoctor.SetSpesialis(trim(spesialis));
                newDoctor.SetJadwalPraktik(sesiPraktik);
                newDoctor.SetPengalamanPraktik(pengalamanPraktikDokter);
                newDoctor.SetRiwayatPendidikan(riwayatPendidikan);
                newDoctor.SetUlasanDokter(ulasanDokter);
                newDoctor.SetTindakanSpesialis(tindakanSpesialis);
            } catch (...) {
                std::string dummy;
                std::cout << Color::RED << "\nPlease enter the correct format!\n" << Color::BRIGHT_YELLOW << "Press \"Enter\" back to Main Menu\n" << Color::RESET;
                std::getline(std::cin, dummy);
                CLI::MainMenuSelector();
                return NULL;
            }

            return newDoctor;
        }
    }

    void AddNewDoctor() {
        std::cout << Color::BRIGHT_YELLOW << Text::InsertDoctor << Color::RESET;

        Data::Doctor newDoctor = DoctorInputField();
        if (newDoctor == NULL) return;

        Database::DoctorAVL.insert(newDoctor);
        Database::DoctorList.push_back(newDoctor);
        std::cout << "\033[2J\033[H";

        Interface::TextRainbowDiagonalColor(Text::DoctorSuccessfullyAdded);
        std::cout << Color::BRIGHT_YELLOW <<  Text::PatientAddedSuccessfullyConfirmation << Color::RESET;

        std::string dummy;
        std::getline(std::cin, dummy);

        CLI::MainMenuSelector();
        return;
    }

    void ViewAllDoctor() {
        std::cout << Color::YELLOW << Text::AllDoctorData << Color::RESET;
        std::cout << Color::YELLOW << Text::AllPatientDataDash << Color::RESET << "\n\n";
        int index = 0;
        for (const Data::Doctor& dokter : Database::DoctorList) {
            std::cout << dokter.toString(++index) << "\n\n";
        }
        std::cout << Color::YELLOW << Text::AllPatientDataDash << Color::RESET;
        std::cout << Color::YELLOW << Text::AllPatientDataConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void SearchDoctor(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                SearchDoctorByID(id);
                return;
            }
        } catch (const std::out_of_range) {
            Manager::DataNotFoundErrorMessage();
            return;
        } catch (const exception) {
            SearchDoctorByName(param);
        }
    }
    void SearchDoctorByID(int id) {
        bool found = false;
        Data::Doctor doctorFound(false);
        for (const Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetID() == id) {
                found = true;
                doctorFound = doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        SearchDoctorAction(doctorFound);
    }
    void SearchDoctorByName(const std::string& name) {
        SearchDoctorAction(*Database::DoctorAVL.Search(name));
    }
    void SearchDoctorAction(const Data::Doctor& doctor) {
        std::cout << Color::CYAN << Text::DataFound << Color::RESET;
        std::cout << doctor.toString(-1);
        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void UpdateDoctor(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                UpdateDoctorByID(id);
                return;
            }
        } catch (const std::out_of_range) {
            Manager::DataNotFoundErrorMessage();
            return;
        } catch (const exception) {
            UpdateDoctorByName(param);
        }
    }
    void UpdateDoctorByID(int id) {
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetID() == id) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(doctorFound->GetNama());
        UpdateDoctorAction(doctorFound, doctorFoundPtr);
    }
    void UpdateDoctorByName(const std::string& name) {
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(name);
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetNama() == name) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        UpdateDoctorAction(doctorFound, doctorFoundPtr);
    }
    void UpdateDoctorAction(const Data::Doctor* arr, Data::Doctor* avl) {
        std::cout << Color::CYAN << Text::DataFound << Color::RESET;
        std::cout << arr->toString(-1);
        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nContinue Edit? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::BRIGHT_YELLOW << Text::DoctorEdited << Color::RESET;

        int originalID = arr->GetID();

        Data::Doctor doctorEdited(false);
        doctorEdited = DoctorInputField();
        doctorEdited.SetID(originalID);
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetID() == arr->GetID()) {
                doctor = doctorEdited;
                break;
            }
        }

        CopyDoctor(avl, doctorEdited);

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void DeleteDoctor(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                DeleteDoctorByID(id);
                return;
            }
        } catch (const std::out_of_range) {
            Manager::DataNotFoundErrorMessage();
            return;
        } catch (const exception) {
            DeleteDoctorByName(param);
        }
    }
    void DeleteDoctorByID(int id) {
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetID() == id) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(doctorFound->GetNama());
        DeteleDoctorAction(doctorFound, doctorFoundPtr);
    }
    void DeleteDoctorByName(const std::string& name) {
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(name);
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetNama() == name) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        DeteleDoctorAction(doctorFound, doctorFoundPtr);
    }
    void DeteleDoctorAction(const Data::Doctor* arr, Data::Doctor* avl) {
        std::cout << Color::RED << Text::DataFound << Color::RESET;
        std::cout << arr->toStringRed(-1);
        std::cout << Color::RED << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nDoctor will be deleted permanently and cannot be retrieved again!";
        std::cout << Color::BRIGHT_YELLOW << "\nDelete This Doctor? (" << Color::CYAN << "Y" << Color::BRIGHT_YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        bool found = false;
        for (auto it = Database::DoctorList.begin(); it != Database::DoctorList.end(); ++it) {
            if (it->GetID() == arr->GetID()) {
                Database::DoctorList.erase(it);
                found = true;
                break;
            }
        }
        if (!found) {
            DataNotFoundErrorMessage();
            return;
        }

        Database::DoctorAVL.remove(*arr);

        std::cout << "\033[2J\033[H" << Color::RESET; //clear screen
        std::cout << Color::RED << Text::DeleteSuccess << Color::RESET;
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
        return;
    }

    void AddDoctorSchedule(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                AddDoctorScheduleByID(id);
                return;
            }
        } catch (const std::out_of_range) {
            Manager::DataNotFoundErrorMessage();
            return;
        } catch (const exception) {
            AddDoctorScheduleByName(param);
        }
    }
    void AddDoctorScheduleByID(int id) {
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetID() == id) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(doctorFound->GetNama());
        AdddoctorScheduleAction(doctorFound, doctorFoundPtr);
    }
    void AddDoctorScheduleByName(const std::string& name) {
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(name);
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetNama() == name) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        DeteleDoctorAction(doctorFound, doctorFoundPtr);
    }
    void AdddoctorScheduleAction(Data::Doctor* arr, Data::Doctor* avl) {
        std::cout << Color::CYAN << Text::DataFound << Color::RESET;
        std::cout << arr->toString(-1);
        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nContinue? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::YELLOW   << "Practice Schedule     : \n" << Color::RESET;
        int index = 1;
        while (true) {
            SesiPraktik newSesiPraktik;
            std::cout << Color::CYAN_VIBRANT << "     > Schedule " << index++ << "\n" << Color::RESET;
            std::cout << Color::CYAN         << "           Day Name (Sunday, .. ) : " << Color::RESET;
            std::getline(std::cin, newSesiPraktik.hari);
            std::cout << Color::CYAN         << "           Start Hour (00:00)     : " << Color::RESET;
            std::getline(std::cin, newSesiPraktik.jamMulai);
            std::cout << Color::CYAN         << "           End Hour (00:00)       : " << Color::RESET;
            std::getline(std::cin, newSesiPraktik.jamSelesai);
            std::cout << Color::CYAN         << "           Session (Day,Night)    : " << Color::RESET;
            std::getline(std::cin, newSesiPraktik.sesi);

            arr->TambahJadwal(newSesiPraktik);
            avl->TambahJadwal(newSesiPraktik);

            std::cout << Color::BRIGHT_YELLOW << "\nAdd More? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
            std::string inputSubmit;
            std::getline(std::cin, inputSubmit);
            if (std::toupper(inputSubmit[0]) != 'Y') { break; }
            std::cout << '\n';
        }

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void AddDoctorExperience(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                AddDoctorExperienceByID(id);
                return;
            }
        } catch (const std::out_of_range) {
            Manager::DataNotFoundErrorMessage();
            return;
        } catch (const exception) {
            AddDoctorExperienceByName(param);
        }
    }
    void AddDoctorExperienceByID(int id) {
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetID() == id) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(doctorFound->GetNama());
        AddDoctorExperienceAction(doctorFound, doctorFoundPtr);
    }
    void AddDoctorExperienceByName(const std::string& name) {
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(name);
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetNama() == name) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        AddDoctorExperienceAction(doctorFound, doctorFoundPtr);
    }
    void AddDoctorExperienceAction(Data::Doctor* arr, Data::Doctor* avl) {
        std::cout << Color::CYAN << Text::DataFound << Color::RESET;
        std::cout << arr->toString(-1);
        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nContinue? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::YELLOW   << "Doctor's Experience   : \n" << Color::RESET;
        int index = 1;
        while (true) {
            PengalamanPraktik newPengalamanPraktik;
            std::cout << Color::CYAN_VIBRANT << "     > Experience " << index++ << "\n" << Color::RESET;
            std::cout << Color::CYAN         << "           Hospital Name          : " << Color::RESET;
            std::getline(std::cin, newPengalamanPraktik.rumahSakit);
            std::cout << Color::CYAN         << "           Position               : " << Color::RESET;
            std::getline(std::cin, newPengalamanPraktik.jabatan);
            std::cout << Color::CYAN         << "           Year Worked            : " << Color::RESET;
            std::getline(std::cin, newPengalamanPraktik.waktu);

            avl->TambahPengalaman(newPengalamanPraktik);
            arr->TambahPengalaman(newPengalamanPraktik);

            std::cout << Color::BRIGHT_YELLOW << "\nAdd More? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
            std::string inputSubmit;
            std::getline(std::cin, inputSubmit);
            if (std::toupper(inputSubmit[0]) != 'Y') { break; }
            std::cout << '\n';
        }

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void AddDoctorEducationHistory(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                AddDoctorEducationHistoryByID(id);
                return;
            }
        } catch (const std::out_of_range) {
            Manager::DataNotFoundErrorMessage();
            return;
        } catch (const exception) {
            AddDoctorEducationHistoryByName(param);
        }
    }
    void AddDoctorEducationHistoryByID(int id) {
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetID() == id) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(doctorFound->GetNama());
        ADdDoctorEducationHistoryAction(doctorFound, doctorFoundPtr);
    }
    void AddDoctorEducationHistoryByName(const std::string& name) {
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(name);
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetNama() == name) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        ADdDoctorEducationHistoryAction(doctorFound, doctorFoundPtr);
    }
    void ADdDoctorEducationHistoryAction(Data::Doctor* arr, Data::Doctor* avl) {
        std::cout << Color::CYAN << Text::DataFound << Color::RESET;
        std::cout << arr->toString(-1);
        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nContinue? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::YELLOW   << "Doctor Education      : \n" << Color::RESET;
        std::cout << Color::GREEN    << "    If done, press \"Enter\" with blank input.\n" << Color::RESET;
        while (true) {
            std::string temp;
            std::cout << Color::CYAN << "     > " << Color::RESET;
            std::getline(std::cin, temp);
            if (temp == "") break;
            arr->TambahRiwayatPendidikan(temp);
            avl->TambahRiwayatPendidikan(temp);
        }

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void AddDoctorReview(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                AddDoctorReviewByID(id);
                return;
            }
        } catch (const std::out_of_range) {
            Manager::DataNotFoundErrorMessage();
            return;
        } catch (const exception) {
            AddDoctorReviewByName(param);
        }
    }
    void AddDoctorReviewByID(int id) {
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetID() == id) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(doctorFound->GetNama());
        AddDoctorReviewAction(doctorFound, doctorFoundPtr);
    }
    void AddDoctorReviewByName(const std::string& name) {
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(name);
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetNama() == name) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        AddDoctorReviewAction(doctorFound, doctorFoundPtr);
    }
    void AddDoctorReviewAction(Data::Doctor* arr, Data::Doctor* avl) {
        std::cout << Color::CYAN << Text::DataFound << Color::RESET;
        std::cout << arr->toString(-1);
        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nContinue? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::YELLOW   << "Doctor's Reviews      : \n" << Color::RESET;
        int index = 1;
        while (true) {
            Ulasan newUlasan;
            std::string dateInput, ratingInput;
            std::cout << Color::CYAN_VIBRANT << "     > Reviews " << index++ << "\n" << Color::RESET;
            std::cout << Color::CYAN         << "           Date (DD-MM-YYYY)      : " << Color::RESET;
            std::getline(std::cin, dateInput);
            newUlasan.tanggal = convertToTimeT(dateInput);
            std::cout << Color::CYAN         << "           Username               : " << Color::RESET;
            std::getline(std::cin, newUlasan.nama);
            std::cout << Color::CYAN         << "           Comment                : " << Color::RESET;
            std::getline(std::cin, newUlasan.komentar);
            std::cout << Color::CYAN         << "           Rating (1-5)           : " << Color::RESET;
            std::getline(std::cin, ratingInput);
            auto rating = safeStringToInt(ratingInput);
            if (rating && *rating >= 1 && *rating <= 5) {
                newUlasan.rating = *rating;
            }

            arr->TambahUlasan(newUlasan);
            avl->TambahUlasan(newUlasan);

            std::cout << Color::BRIGHT_YELLOW << "\nAdd More? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::BRIGHT_YELLOW << ")? " << Color::CYAN_VIBRANT;
            std::string inputSubmit;
            std::getline(std::cin, inputSubmit);
            if (std::toupper(inputSubmit[0]) != 'Y') { break; }
            std::cout << '\n';
        }

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void AddMedicalSpecialization(const std::string& param) {
        try {
            size_t idx;
            int id = std::stoi(param, &idx);

            if (idx == param.length()) {
                AddMedicalSpecializationByID(id);
                return;
            }
        } catch (const std::out_of_range) {
            Manager::DataNotFoundErrorMessage();
            return;
        } catch (const exception) {
            AddMedicalSpecializationByName(param);
        }
    }
    void AddMedicalSpecializationByID(int id) {
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetID() == id) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(doctorFound->GetNama());
        AddMedicalSpecializationAction(doctorFound, doctorFoundPtr);
    }
    void AddMedicalSpecializationByName(const std::string& name) {
        Data::Doctor* doctorFoundPtr = Database::DoctorAVL.Search(name);
        bool found = false;
        Data::Doctor* doctorFound = nullptr;
        for (Data::Doctor& doctor : Database::DoctorList) {
            if (doctor.GetNama() == name) {
                found = true;
                doctorFound = &doctor;
                break;
            }
        }
        if (!found) { DataNotFoundErrorMessage(); return;}
        AddMedicalSpecializationAction(doctorFound, doctorFoundPtr);
    }
    void AddMedicalSpecializationAction(Data::Doctor* arr, Data::Doctor* avl) {
        std::cout << Color::CYAN << Text::DataFound << Color::RESET;
        std::cout << arr->toString(-1);
        std::cout << Color::CYAN << Text::DataFoundDash << Color::RESET;

        std::cout << Color::YELLOW << "\nContinue? (" << Color::CYAN << "Y" << Color::YELLOW << "/" << Color::RED << "N" << Color::YELLOW << ")? " << Color::CYAN_VIBRANT;
        std::string inputSubmit;
        std::getline(std::cin, inputSubmit);
        std::cout << Color::RESET;
        if (std::toupper(inputSubmit[0]) != 'Y') { CLI::MainMenuSelector(); return; }

        std::cout << Color::YELLOW   << "Doctor Medical Action : \n" << Color::RESET;
        std::cout << Color::GREEN    << "    If done, press \"Enter\" with blank input.\n" << Color::RESET;
        while (true) {
            std::string temp;
            std::cout << Color::CYAN << "     > " << Color::RESET;
            std::getline(std::cin, temp);
            if (temp == "") break;
            arr->TambahTindakan(temp);
            avl->TambahTindakan(temp);
        }

        std::cout << "\033[2J\033[H"; //clear screen
        Interface::TextRainbowDiagonalColor(Text::EditedSuccess);
        std::cout << Color::YELLOW << Text::DataFoundConfirmation << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
        CLI::MainMenuSelector();
    }

    void FilterDoctorBySpecialization() {
        std::cout << Text::ChooseSpecialist;
        std::cout << Color::YELLOW << "Choose By ID " << Color::CYAN << "(1-33): " << Color::CYAN_VIBRANT;
        std::string dummy;
        std::getline(std::cin, dummy);
        std::cout << Color::RESET;
        DataNotFoundErrorMessage();
    }

    void SortDoctorByName();

    void CopyDoctor(Data::Doctor* target, const Data::Doctor& data) {
        target->SetNama(data.GetNama());
        target->SetTempatLahir(data.GetTempatLahir());
        target->SetTanggalLahir(data.GetTanggalLahir());
        target->SetJenisKelamin(data.GetJenisKelamin());
        target->SetGolonganDarah(data.GetGolonganDarah());
        target->SetAlamat(data.GetAlamat());
        target->SetAgama(data.GetAgama());
        target->SetNomorTelepon(data.GetNomorTelepon());
        target->SetEmail(data.GetEmail());
        target->SetProfilDokter(data.GetProfilDokter());
        target->SetSpesialis(data.GetSpesialis());
        target->SetJadwalPraktik(data.GetSesiPraktik());
        target->SetPengalamanPraktik(data.GetPengalamanPraktik());
        target->SetRiwayatPendidikan(data.GetRiwayatPendidikan());
        target->SetUlasanDokter(data.GetUlasanDokter());
        target->SetTindakanSpesialis(data.GetTindakanSpesialis());
    }
} // Manager