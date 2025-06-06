
// ============================================================================
// | Patient.cpp                                                              |
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

#include "Patient.h"
#include "../Helper/BirthDateHelper.h"
#include <iostream>

namespace Data {

    int Patient::nextID = 1;

    Patient::Patient()
    :   ID(nextID++)
        {
            TanggalLahir = makeBirthDate(1970, 1, 1);
            JenisKelamin = 'U';
        }

    Patient::Patient(std::string nama,
                     std::string tempatLahir,
                     BirthDate tanggalLahir,
                     char jenisKelamin,
                     std::string golonganDarah,
                     std::string alamat,
                     std::string agama,
                     std::string nomorTelepon,
                     std::string email)
        :   ID(nextID++)
        {
            Nama = std::move(nama),
            TempatLahir = std::move(tempatLahir),
            TanggalLahir = tanggalLahir,
            JenisKelamin = jenisKelamin,
            GolonganDarah = std::move(golonganDarah),
            Alamat = std::move(alamat),
            Agama = std::move(agama),
            NomorTelepon = std::move(nomorTelepon),
            Email = std::move(email);
        }

    // Getters
    int Patient::GetID() const { return ID; }
    const std::string& Patient::GetNama() const { return Nama; }
    const std::string& Patient::GetTempatLahir() const { return TempatLahir; }
    BirthDate Patient::GetTanggalLahir() const { return TanggalLahir; }
    char Patient::GetJenisKelamin() const { return JenisKelamin; }
    std::string Patient::GetGolonganDarah() const { return GolonganDarah; }
    const std::string& Patient::GetAlamat() const { return Alamat; }
    const std::string& Patient::GetAgama() const { return Agama; }
    const std::string& Patient::GetNomorTelepon() const { return NomorTelepon; }
    const std::string& Patient::GetEmail() const { return Email; }
    const DiseaseHistory& Patient::GetRiwayatPenyakit() const { return RiwayatPenyakit; }

    // Setters
    void Patient::SetNama(const std::string& nama) { Nama = nama; }
    void Patient::SetTempatLahir(const std::string& tempatLahir) { TempatLahir = tempatLahir; }
    void Patient::SetTanggalLahir(const BirthDate& tanggalLahir) { TanggalLahir = tanggalLahir; }
    void Patient::SetJenisKelamin(char jenisKelamin) { JenisKelamin = jenisKelamin; }
    void Patient::SetGolonganDarah(const std::string& golonganDarah) { GolonganDarah = golonganDarah; }
    void Patient::SetAlamat(const std::string& alamat) { Alamat = alamat; }
    void Patient::SetAgama(const std::string& agama) { Agama = agama; }
    void Patient::SetNomorTelepon(const std::string& nomorTelepon) { NomorTelepon = nomorTelepon; }
    void Patient::SetEmail(const std::string& email) { Email = email; }
    void Patient::SetRiwayatPenyakit(const DiseaseHistory& riwayat) { RiwayatPenyakit = riwayat; }

    // Adders
    void Patient::TambahRiwayatPenyakit(const std::string& penyakit) { RiwayatPenyakit.AddDisease(penyakit); }

    std::string Patient::toString() const {
        std::stringstream ss;
        ss << "ID: " << ID << "\n"
           << "Nama: " << Nama << "\n"
           << "Tempat Lahir: " << TempatLahir << "\n";

        #if __cplusplus >= 202002L
        ss << "Tanggal Lahir: " << static_cast<int>(TanggalLahir.year()) << "-"
           << static_cast<unsigned>(TanggalLahir.month()) << "-"
           << static_cast<unsigned>(TanggalLahir.day()) << "\n";
        #else
        ss << "Tanggal Lahir: " << (TanggalLahir.tm_year + 1900) << "-"
           << (TanggalLahir.tm_mon + 1) << "-"
           << TanggalLahir.tm_mday << "\n";
        #endif

        ss << "Jenis Kelamin: " << JenisKelamin << "\n"
           << "Golongan Darah: " << GolonganDarah << "\n"
           << "Alamat: " << Alamat << "\n"
           << "Agama: " << Agama << "\n"
           << "Nomor Telepon: " << NomorTelepon << "\n"
           << "Email: " << Email << "\n"
           << RiwayatPenyakit.toString() << "\n\n";

        return ss.str();
    }

} // Data Namespace mwhehe :3