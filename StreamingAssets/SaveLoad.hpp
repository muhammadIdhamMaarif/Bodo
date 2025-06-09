#ifndef SAVELOAD_HPP
#define SAVELOAD_HPP

#include "json.hpp"
#include <fstream>
#include <format>
#include <iostream>
#include "../Core/PersonData/Patient.h"
#include "../Data/PatientData.h"
#include <filesystem>

namespace SLManager {
    using json = nlohmann::json;

    inline std::string toString(const std::chrono::year_month_day& ymd) {
        return std::format("{:%F}", ymd); // "YYYY-MM-DD"
    }

    inline std::chrono::year_month_day fromString(const std::string& dateStr) {
        int y, m, d;
        sscanf(dateStr.c_str(), "%d-%d-%d", &y, &m, &d);
        return std::chrono::year_month_day{
            std::chrono::year{y},
            std::chrono::month{static_cast<unsigned int>(m)},
            std::chrono::day{static_cast<unsigned int>(d)}
        };
    }

    inline void SavePatientRecords() {
        json JSON = json::array();

        // PATIENT SECTION
        json jPatients = {
            {"name", "Patient"},
            {"data", json::array()}
        };

        for (const Data::Patient& pasien : Database::PatientLinear) {
            json jPasien;
            jPasien["id"] = pasien.GetID();
            jPasien["nama"] = pasien.GetNama();
            jPasien["tempatLahir"] = pasien.GetTempatLahir();
            jPasien["tanggalLahir"] = toString(pasien.GetTanggalLahir());
            jPasien["jenisKelamin"] = std::string(1, pasien.GetJenisKelamin());
            jPasien["golonganDarah"] = pasien.GetGolonganDarah();
            jPasien["alamat"] = pasien.GetAlamat();
            jPasien["agama"] = pasien.GetAgama();
            jPasien["nomorTelepon"] = pasien.GetNomorTelepon();
            jPasien["email"] = pasien.GetEmail();

            // Save riwayat penyakit
            jPasien["riwayatPenyakit"] = json::array();
            DiseaseHistory riwayat = pasien.GetRiwayatPenyakit();
            for (const std::string& penyakit : riwayat.copyDisease()) {
                jPasien["riwayatPenyakit"].push_back(penyakit);
            }

            jPatients["data"].push_back(jPasien);
        }

        // DOCTOR SECTION
        json jDoctor = {
            {"name", "Doctor"},
            {"data", json::array()}
        };

        // APPOINTMENT SECTION
        json jAppointment = {
            {"name", "Appointment"},
            {"data", json::array()}
        };

        JSON.push_back(jPatients);
        JSON.push_back(jDoctor);
        JSON.push_back(jAppointment);

        std::string jsonString = JSON.dump(4);
        // std::cout << jsonString << std::endl;

        std::filesystem::create_directories("SaveData");

        std::ofstream file("SaveData/Data.json");
        if (file.is_open()) {
            file << jsonString;
            file.close();
        } else {
            std::cerr << "Error opening file for writing.\n";
        }
    }

    inline void LoadPatientRecords() {
        std::ifstream file("SaveData/Data.json");
        if (!file.is_open()) {
            std::cerr << "Failed to open file for reading.\n";
            return;
        }

        int maxID = -1;

        json JSON;
        file >> JSON;
        file.close();

        for (const auto& section : JSON) {
            if (section["name"] == "Patient") {
                for (const auto& jPasien : section["data"]) {
                    Data::Patient pasien;
                    pasien.SetID(jPasien["id"]);
                    maxID = std::max(maxID, pasien.GetID());
                    pasien.SetNama(jPasien["nama"]);
                    pasien.SetTempatLahir(jPasien["tempatLahir"]);
                    pasien.SetTanggalLahir(fromString(jPasien["tanggalLahir"]));
                    pasien.SetJenisKelamin(jPasien["jenisKelamin"].get<std::string>()[0]);
                    pasien.SetGolonganDarah(jPasien["golonganDarah"]);
                    pasien.SetAlamat(jPasien["alamat"]);
                    pasien.SetAgama(jPasien["agama"]);
                    pasien.SetNomorTelepon(jPasien["nomorTelepon"]);
                    pasien.SetEmail(jPasien["email"]);

                    DiseaseHistory riwayat;
                    for (const auto& penyakit : jPasien["riwayatPenyakit"]) {
                        riwayat.AddDisease(penyakit);
                    }
                    pasien.SetRiwayatPenyakit(riwayat);

                    Database::PatientLinear.push_back(pasien);
                    Database::Patient.AddPatient(pasien);
                }
            }
        }
        Data::Patient::UpdateNextIDFromExisting(maxID);
    }

    inline void LoadData() {
        LoadPatientRecords();
    }

    inline void SaveData() {
        SavePatientRecords();
    }
}

#endif // SAVELOAD_HPP
