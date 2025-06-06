//
// Created by Acer on 06/06/2025.
//

#ifndef PATIENT_H
#define PATIENT_H
#include <string>
#include "DiseaseHistory.h"
#include "Person.h"

namespace Data {

    class Patient : Person {
    private:
        static int      nextID;
        int             ID;
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

        // Adders
        void TambahRiwayatPenyakit(const std::string& penyakit);

        // Other Methods
        [[nodiscard]] std::string toString() const;

    };

}

#endif //PATIENT_H
