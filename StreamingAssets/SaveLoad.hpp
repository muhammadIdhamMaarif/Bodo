#ifndef SAVELOAD_HPP
#define SAVELOAD_HPP

#include "json.hpp"
#include <fstream>
#include <format>
#include <iostream>
#include "../Core/PersonData/Patient.h"
#include "../Data/PatientData.h"
#include <filesystem>

#include "../Core/PersonData/BookAppointment.hpp"
#include "../Core/PersonData/Doctor.h"
#include "../Data/DoctorData.h"

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

    inline std::string TimeToString(time_t rawTime, const std::string& format = "%d-%m-%Y") {
        std::tm* timeInfo = std::localtime(&rawTime); // Use localtime or gmtime
        std::ostringstream oss;
        oss << std::put_time(timeInfo, format.c_str());
        return oss.str();
    }

    inline time_t StringToTime(const std::string& dateStr, const std::string& format = "%d-%m-%Y") {
        std::tm timeInfo = {};
        std::istringstream iss(dateStr);
        iss >> std::get_time(&timeInfo, format.c_str());
        if (iss.fail()) {
            throw std::runtime_error("Failed to parse date string: " + dateStr);
        }
        return std::mktime(&timeInfo); // Assumes local time
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
            jPasien["riwayatPeriksa"] = json::array();

            // struct Checkup {
            //     std::time_t tanggal;         // Tanggal checkup/treatment
            //     std::string dokter;          // Nama doketer
            //     std::string keluhan;         // Keluhan pasien
            //     std::string tindakan;        // Diagnosis / treatment
            //     std::string resep;           // resep dokter dengan tulisanya yang cantik
            // };

            for (const Data::Checkup& checkup : pasien.GetRiwayatPeriksa().GetAllRecords()) {
                json periksa;
                periksa["tanggal"] = checkup.tanggal;
                periksa["dokter"] = checkup.dokter;
                periksa["keluhan"] = checkup.keluhan;
                periksa["tindakan"] = checkup.tindakan;
                periksa["resep"] = checkup.resep;

                jPasien["riwayatPeriksa"].push_back(periksa);
            }

            jPatients["data"].push_back(jPasien);
        }

        // DOCTOR SECTION
        json jDoctors = {
            {"name", "Doctor"},
            {"data", json::array()}
        };

        for (const Data::Doctor& doctor : Database::DoctorList) {
            json jDoctor;
            jDoctor["id"] = doctor.GetID();
            jDoctor["nama"] = doctor.GetNama();
            jDoctor["tempatLahir"] = doctor.GetTempatLahir();
            jDoctor["tanggalLahir"] = toString(doctor.GetTanggalLahir());
            jDoctor["jenisKelamin"] = std::string(1, doctor.GetJenisKelamin());
            jDoctor["golonganDarah"] = doctor.GetGolonganDarah();
            jDoctor["alamat"] = doctor.GetAlamat();
            jDoctor["agama"] = doctor.GetAgama();
            jDoctor["nomorTelepon"] = doctor.GetNomorTelepon();
            jDoctor["email"] = doctor.GetEmail();
            jDoctor["profil"] = doctor.GetProfilDokter();
            jDoctor["spesialis"] = doctor.GetSpesialis();

            jDoctor["jadwal"] = json::array();
            for (const SesiPraktik& praktik : doctor.GetSesiPraktik()) {
                json sesi;
                sesi["hari"] = praktik.hari;
                sesi["jamMulai"] = praktik.jamMulai;
                sesi["jamSelesai"] = praktik.jamSelesai;
                sesi["sesi"] = praktik.sesi;

                jDoctor["jadwal"].push_back(sesi);
            }

            jDoctor["pengalamanPraktik"] = json::array();
            for (const PengalamanPraktik& praktik : doctor.GetPengalamanPraktik()) {
                json pengalaman;
                pengalaman["rumahSakit"] = praktik.rumahSakit;
                pengalaman["waktu"] = praktik.waktu;
                pengalaman["jabatan"] = praktik.jabatan;

                jDoctor["pengalamanPraktik"].push_back(pengalaman);
            }

            jDoctor["riwayatPendidikan"] = json::array();
            for (const std::string& pendidikan : doctor.GetRiwayatPendidikan()) {
                jDoctor["riwayatPendidikan"].push_back(pendidikan);
            }

            jDoctor["ulasan"] = json::array();
            for (const Ulasan& ulasan : doctor.GetUlasanDokter()) {
                json review;
                review["tanggal"] = TimeToString(ulasan.tanggal);
                review["nama"] = ulasan.nama;
                review["komentar"] = ulasan.komentar;
                review["rating"] = ulasan.rating;

                jDoctor["ulasan"].push_back(review);
            }

            jDoctor["tindakanMedis"] = json::array();
            for (const std::string& medis : doctor.GetTindakanSpesialis()) {
                jDoctor["tindakanMedis"].push_back(medis);
            }

            jDoctors["data"].push_back(jDoctor);
        }

        // APPOINTMENT SECTION
        json jAppointment = {
            {"name", "Appointment"},
            {"data", json::array()}
        };

        JSON.push_back(jPatients);
        JSON.push_back(jDoctors);
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

        int maxIDPatient = -1;
        int maxIDDoctor = -1;
        int maxIDAppointment = -1;

        json JSON;
        file >> JSON;
        file.close();

        for (const auto& section : JSON) {
            if (section["name"] == "Patient") {
                for (const auto& jPasien : section["data"]) {
                    Data::Patient pasien;
                    pasien.SetID(jPasien["id"]);
                    maxIDPatient = std::max(maxIDPatient, pasien.GetID());
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

                    for (const auto& checkup : jPasien["riwayatPeriksa"]) {
                        Data::Checkup newCheckup;
                        newCheckup.tanggal = checkup["tanggal"];
                        newCheckup.dokter = checkup["dokter"];
                        newCheckup.keluhan = checkup["keluhan"];
                        newCheckup.tindakan = checkup["tindakan"];
                        newCheckup.resep = checkup["resep"];
                        pasien.TambahMedicalRecords(newCheckup);
                    }

                    Database::PatientLinear.push_back(pasien);
                    Database::Patient.AddPatient(pasien);
                }
            }

            else if (section["name"] == "Doctor") {
                for (const auto& jDoctor : section["data"]) {
                    Data::Doctor doctor;
                    doctor.SetID(jDoctor["id"]);
                    maxIDDoctor = std::max(maxIDDoctor, doctor.GetID());
                    doctor.SetNama(jDoctor["nama"]);
                    doctor.SetTempatLahir(jDoctor["tempatLahir"]);
                    doctor.SetTanggalLahir(fromString(jDoctor["tanggalLahir"]));
                    doctor.SetJenisKelamin(jDoctor["jenisKelamin"].get<std::string>()[0]);
                    doctor.SetGolonganDarah(jDoctor["golonganDarah"]);
                    doctor.SetAlamat(jDoctor["alamat"]);
                    doctor.SetAgama(jDoctor["agama"]);
                    doctor.SetNomorTelepon(jDoctor["nomorTelepon"]);
                    doctor.SetEmail(jDoctor["email"]);
                    doctor.SetProfilDokter(jDoctor["profil"]);
                    doctor.SetSpesialis(jDoctor["spesialis"]);

                    for (const auto& sesi : jDoctor["jadwal"]) {
                        SesiPraktik newSesiPraktik;
                        newSesiPraktik.hari = sesi["hari"];
                        newSesiPraktik.jamMulai = sesi["jamMulai"];
                        newSesiPraktik.jamSelesai = sesi["jamSelesai"];
                        newSesiPraktik.sesi = sesi["sesi"];
                        doctor.TambahJadwal(newSesiPraktik);
                    }

                    for (const auto& pengalaman : jDoctor["pengalamanPraktik"]) {
                        PengalamanPraktik newPengalamanPraktik;
                        newPengalamanPraktik.rumahSakit = pengalaman["rumahSakit"];
                        newPengalamanPraktik.waktu = pengalaman["waktu"];
                        newPengalamanPraktik.jabatan = pengalaman["jabatan"];
                        doctor.TambahPengalaman(newPengalamanPraktik);
                    }

                    for (const auto& pendidikan : jDoctor["riwayatPendidikan"]) {
                        doctor.TambahRiwayatPendidikan(pendidikan);
                    }

                    for (const auto& review : jDoctor["ulasan"]) {
                        Ulasan newUlasan;
                        newUlasan.tanggal = StringToTime(review["tanggal"]);
                        newUlasan.nama = review["nama"];
                        newUlasan.komentar = review["komentar"];
                        newUlasan.rating = review["rating"];
                        doctor.TambahUlasan(newUlasan);
                    }

                    for (const auto& medis : jDoctor["tindakanMedis"]) {
                        doctor.TambahTindakan(medis);
                    }

                    Database::DoctorList.push_back(doctor);
                    Database::DoctorAVL.insert(doctor);
                }
            }

            // Buat Book Appointment

        }
        Data::Patient::UpdateNextIDFromExisting(maxIDPatient);
        Data::Doctor::UpdateNextIDFromExisting(maxIDDoctor);
        Appointment::setNextID(1);
    }

    inline void LoadData() {
        LoadPatientRecords();
    }

    inline void SaveData() {
        SavePatientRecords();
    }
}

#endif // SAVELOAD_HPP
