//
// Created by Acer on 06/06/2025.
//

#ifndef PATIENT_H
#define PATIENT_H
#include <string>
#include "DiseaseHistory.h"

#if __cplusplus >= 202002L
    #include <chrono>
    using BirthDate = std::chrono::year_month_day;
#else
    #include <ctime>
    using BirthDate = std::tm;
#endif

namespace Data {

    class Patient {
    private:
        static int      nextID;
        int             ID;
        std::string     Nama;
        std::string     TempatLahir;
        BirthDate       TanggalLahir;
        char            JenisKelamin;
        std::string     GolonganDarah;
        std::string     Alamat;
        std::string     Agama;
        std::string     NomorTelepon;
        std::string     Email;
        DiseaseHistory  RiwayatPenyakit;

    public:
        // Constructor dan Destructor
        Patient();
        Patient(std::string nama,
                std::string tempatLahir,
                BirthDate tanggalLahir,
                char jenisKelamin,
                std::string golonganDarah,
                std::string alamat,
                std::string agama,
                std::string nomorTelepon = "",
                std::string email = "");

        ~Patient() = default;

        // Getters
        [[nodiscard]] int GetID() const;
        [[nodiscard]] const std::string& GetNama() const;
        [[nodiscard]] const std::string& GetTempatLahir() const;
        [[nodiscard]] BirthDate GetTanggalLahir() const;
        [[nodiscard]] char GetJenisKelamin() const;
        [[nodiscard]] std::string GetGolonganDarah() const;
        [[nodiscard]] const std::string& GetAlamat() const;
        [[nodiscard]] const std::string& GetAgama() const;
        [[nodiscard]] const std::string& GetNomorTelepon() const;
        [[nodiscard]] const std::string& GetEmail() const;
        [[nodiscard]] const DiseaseHistory& GetRiwayatPenyakit() const;

        // Setters
        void SetNama(const std::string& nama);
        void SetTempatLahir(const std::string& tempatLahir);
        void SetTanggalLahir(const BirthDate& tanggalLahir);
        void SetJenisKelamin(char jenisKelamin);
        void SetGolonganDarah(const std::string& golonganDarah);
        void SetAlamat(const std::string& alamat);
        void SetAgama(const std::string& agama);
        void SetNomorTelepon(const std::string& nomorTelepon);
        void SetEmail(const std::string& email);
        void SetRiwayatPenyakit(const DiseaseHistory& riwayat);

        // Other Methods
        [[nodiscard]] std::string toString() const;

    };

}

#endif //PATIENT_H
