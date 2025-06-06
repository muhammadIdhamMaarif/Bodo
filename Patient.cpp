//
// Created by Acer on 06/06/2025.
//

#include "Patient.h"
#include <iostream>

namespace Data {

    int Patient::nextID = 1;

    #if __cplusplus >= 202002L
        // C++20 version
        BirthDate makeBirthDate(int year, int month, int day) {
            return std::chrono::year{year} /
                   std::chrono::month{static_cast<unsigned>(month)} /
                   std::chrono::day{static_cast<unsigned>(day)};
        }

        void printDate(const BirthDate& date) {
            std::cout << static_cast<int>(date.year()) << "-"
                      << static_cast<unsigned>(date.month()) << "-"
                      << static_cast<unsigned>(date.day());
        }

    #else
        // Pre-C++20 version
        BirthDate makeBirthDate(int year, int month, int day) {
            std::tm date{};
            date.tm_year = year - 1900;
            date.tm_mon = month - 1;
            date.tm_mday = day;
            return date;
        }

        void printDate(const BirthDate& date) {
            std::cout << (date.tm_year + 1900) << "-"
                      << (date.tm_mon + 1) << "-"
                      << date.tm_mday;
        }
    #endif

    Patient::Patient()
    :   ID(nextID++),
        #if __cplusplus >= 202002L
              TanggalLahir(std::chrono::year{1970} / std::chrono::month{1} / std::chrono::day{1}),
        #else
              TanggalLahir([] {
                  std::tm temp{};
                  temp.tm_year = 70;
                  temp.tm_mon = 0;
                  temp.tm_mday = 1;
                  return temp;
              }()),
        #endif
        JenisKelamin('U')
        {}

    Patient::Patient(std::string nama,
                     std::string tempatLahir,
                     BirthDate tanggalLahir,
                     char jenisKelamin,
                     std::string golonganDarah,
                     std::string alamat,
                     std::string agama,
                     std::string nomorTelepon,
                     std::string email)
        :   ID(nextID++),
            Nama(std::move(nama)),
            TempatLahir(std::move(tempatLahir)),
            TanggalLahir(tanggalLahir),
            JenisKelamin(jenisKelamin),
            GolonganDarah(std::move(golonganDarah)),
            Alamat(std::move(alamat)),
            Agama(std::move(agama)),
            NomorTelepon(std::move(nomorTelepon)),
            Email(std::move(email))
        {}

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
           << RiwayatPenyakit.toString() << "\n";

        return ss.str();
    }

} // Data Namespace mwhehe :3