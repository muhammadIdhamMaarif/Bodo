
// ============================================================================
// | Doctor.cpp                                                               |
// | Kegunaan : Mengimplementasi fungsi yang dideklarasikan pada header       |
// |                                                                          |
// | Penjelasan Singkat Kode :                                                |
// |    Implementasi class Doctor yang menyimpan data dokter,                 |
// |    meliputi profil, jadwal praktik, pengalaman, pendidikan, ulasan,      |
// |    dan tindakan medis/spesialisasi.                                      |
// |                                                                          |
// | Penjelasan Method :                                                      |
// |    - Doctor()                                                            |
// |          Konstruktor default yang memberikan ID unik otomatis.           |
// |    - Doctor(const std::string&, const std::string&, const std::string&)  |
// |          Konstruktor dengan parameter nama, spesialis, dan profil.       |
// |    - GetID()                                                             |
// |          Mengembalikan ID unik dokter.                                   |
// |    - SetProfilDokter(const std::string&)                                 |
// |          Mengatur profil dokter.                                         |
// |    - SetSpesialis(const std::string&)                                    |
// |          Mengatur bidang spesialisasi dokter.                            |
// |    - TambahJadwal(const SesiPraktik&)                                    |
// |          Menambah sesi jadwal praktik dokter.                            |
// |    - TambahPengalaman(const PengalamanPraktik&)                          |
// |          Menambah pengalaman praktik dokter.                             |
// |    - TambahRiwayatPendidikan(const std::string&)                         |
// |          Menambah riwayat pendidikan dokter.                             |
// |    - TambahUlasan(const Ulasan&)                                         |
// |          Menambah ulasan pasien terhadap dokter.                         |
// |    - TambahTindakan(const std::string&)                                  |
// |          Menambah tindakan medis atau spesialisasi.                      |
// |    - toString()                                                          |
// |          Mengembalikan representasi string lengkap data dokter.          |
// ============================================================================

#include "Doctor.h"
#include <sstream>
#include <iomanip>
#include <string>

namespace Data {

int Doctor::nextID = 1;

Doctor::Doctor() : ID(nextID++) {}

Doctor::Doctor(const std::string& nama, const std::string& spesialis, const std::string& profil)
    : ID(nextID++) {
    Nama = nama;
    Spesialis = spesialis;
    ProfilDokter = profil;
}

int Doctor::GetID() const {
    return ID;
}

void Doctor::SetProfilDokter(const std::string& profil) {
    ProfilDokter = profil;
}

void Doctor::SetSpesialis(const std::string& spesialis) {
    Spesialis = spesialis;
}

void Doctor::TambahJadwal(const SesiPraktik& sesi) {
    JadwalPraktik.push_back(sesi);
}

void Doctor::TambahPengalaman(const PengalamanPraktik& pengalaman) {
    PengalamanPraktikDokter.push_back(pengalaman);
}

void Doctor::TambahRiwayatPendidikan(const std::string& pendidikan) {
    RiwayatPendidikan.push_back(pendidikan);
}

void Doctor::TambahUlasan(const Ulasan& ulasan) {
    UlasanDokter.push_back(ulasan);
}

void Doctor::TambahTindakan(const std::string& tindakan) {
    TindakanSpesialis.push_back(tindakan);
}

std::string Doctor::toString() const {
    std::stringstream ss;
    ss << "ID Dokter: " << ID << "\n"
       << "Nama: " << Nama << "\n"
       << "Spesialis: " << Spesialis << "\n"
       << "Profil: " << ProfilDokter << "\n\n";

    ss << "Jadwal Praktik:\n";
    for (const auto& sesi : JadwalPraktik) {
        ss << "- " << sesi.hari << " (" << sesi.sesi << "): "
           << sesi.jamMulai << " - " << sesi.jamSelesai << "\n";
    }

    ss << "\nPengalaman Praktik:\n";
    for (const auto& exp : PengalamanPraktikDokter) {
        ss << "- " << exp.jabatan << " di " << exp.rumahSakit.GetNamaRumahSakit()
           << " (" << exp.waktu << ")\n";
    }

    ss << "\nRiwayat Pendidikan:\n";
    for (const auto& edu : RiwayatPendidikan) {
        ss << "- " << edu << "\n";
    }

    ss << "\nTindakan Medis/Spesialis:\n";
    for (const auto& tindakan : TindakanSpesialis) {
        ss << "- " << tindakan << "\n";
    }

    ss << "\nUlasan Pasien:\n";
    for (const auto& review : UlasanDokter) {
        std::tm* tm_ptr = std::localtime(&review.tanggal);
        ss << "- " << review.nama << " (" << std::put_time(tm_ptr, "%Y-%m-%d") << "): "
           << review.komentar << " [" << review.rating << "/5]\n";
    }

    return ss.str();
}

} // namespace Data
