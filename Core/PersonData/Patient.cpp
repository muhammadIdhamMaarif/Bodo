
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

#include "../Helper/ColorList.h"

namespace Data {

    int Patient::nextID = 1;

    Patient::Patient(bool isIncrementing)
    :   ID(nextID++)
        {
            if (!isIncrementing) { nextID--; }
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
        ss << Color::CYAN << "     ID            : " << Color::RESET << ID << "\n"
           << Color::CYAN << "     Nama          : " << Color::RESET << Nama << "\n"
           << Color::CYAN << "     Tempat Lahir  : " << Color::RESET << TempatLahir << "\n";

        #if __cplusplus >= 202002L
        ss << Color::CYAN << "     Tanggal Lahir : " << Color::RESET
           << static_cast<int>(TanggalLahir.year()) << "-"
           << static_cast<unsigned>(TanggalLahir.month()) << "-"
           << static_cast<unsigned>(TanggalLahir.day()) << "\n";
        #else
        ss << Color::CYAN << "     Tanggal Lahir : " << Color::RESET
           << (TanggalLahir.tm_year + 1900) << "-"
           << (TanggalLahir.tm_mon + 1) << "-"
           << TanggalLahir.tm_mday << "\n";
        #endif

        ss << Color::CYAN << "     Jenis Kelamin : " << Color::RESET << JenisKelamin << "\n"
           << Color::CYAN << "     Gol. Darah    : " << Color::RESET << GolonganDarah << "\n"
           << Color::CYAN << "     Alamat        : " << Color::RESET << Alamat << "\n"
           << Color::CYAN << "     Agama         : " << Color::RESET << Agama << "\n"
           << Color::CYAN << "     Nomor Telepon : " << Color::RESET << NomorTelepon << "\n"
           << Color::CYAN << "     Email         : " << Color::RESET << Email << "\n"
           << RiwayatPenyakit.toString() << "";

        return ss.str();
    }

} // Data Namespace mwhehe :3