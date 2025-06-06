
// ============================================================================
// | Patient.h                                                            |
// | Kegunaan : Implementasi class Patient untuk menyimpan data pasien        |
// |                                                                          |
// | Penjelasan Singkat Kode :                                                |
// |    File ini berisi definisi method untuk class Patient, termasuk         |
// |    konstruktor, getter, setter, dan fungsi untuk mengelola data pasien   |
// |    seperti biodata dan riwayat penyakit.                                 |
// |                                                                          |
// | Penjelasan Method :                                                      |
// |    1. Patient()                                                          |
// |          Konstruktor default dengan nilai awal dan auto increment ID.    |
// |    2. Patient(...)                                                       |
// |          Konstruktor parameter untuk inisialisasi lengkap atribut pasien |
// |    3. GetID(), GetNama(), dll                                            |
// |          Getter untuk mengakses atribut pasien                           |
// |    4. SetNama(), SetAlamat(), dll                                        |
// |          Setter untuk mengubah nilai atribut pasien                      |
// |    5. TambahRiwayatPenyakit                                              |
// |          Menambahkan nama penyakit ke dalam daftar riwayat penyakit      |
// |    6. toString                                                           |
// |          Mengembalikan data lengkap pasien dalam format string           |
// ============================================================================

#ifndef PATIENT_H
#define PATIENT_H
#include <string>
#include "../Records/DiseaseHistory.h"
#include "../Records/MedicalRecord.h"
#include "Person.h"

namespace Data {

    class Patient : Person {
    private:
        static int      nextID;
        int             ID;
        DiseaseHistory  RiwayatPenyakit;
        MedicalRecord   RiwayatPeriksa;

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