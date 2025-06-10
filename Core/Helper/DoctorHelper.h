
// ============================================================================
// | DoctorHelper.h                                                           |
// | Kegunaan : Mendefinisikan struct pendukung untuk class Doctor            |
// |                                                                          |
// | Penjelasan Singkat Kode :                                                |
// |    Berisi definisi struct Ulasan, RumahSakit, SesiPraktik, dan           |
// |    PengalamanPraktik yang menyimpan informasi tambahan terkait dokter    |
// |    seperti jadwal, pengalaman, ulasan, dan informasi rumah sakit.        |
// |                                                                          |
// | Penjelasan Struct :                                                      |
// |    - Ulasan                                                              |
// |          Menyimpan data ulasan pasien termasuk tanggal, nama, komentar,  |
// |          dan rating (1-5).                                               |
// |    - RumahSakit                                                          |
// |          Menyimpan informasi rumah sakit seperti nama, lokasi, jam buka, |
// |          nomor telepon, ulasan, dan penghargaan.                         |
// |    - SesiPraktik                                                         |
// |          Menyimpan jadwal praktik dokter berupa hari, jam mulai, jam     |
// |          selesai, dan sesi (pagi/sore).                                  |
// |    - PengalamanPraktik                                                   |
// |          Menyimpan pengalaman kerja dokter berupa rumah sakit, waktu     |
// |          bekerja, dan jabatan.                                           |
// ============================================================================

#ifndef DOCTORHELPER_H
#define DOCTORHELPER_H

#include <string>
#include <ctime>

struct Ulasan {
    time_t tanggal;
    std::string nama;     // Nama Pengulas
    std::string komentar;       // Komentar
    int rating;                 // Dari 1-5
};

struct RumahSakit {
    std::string nama;           // Nama Rumah Sakit
    std::string lokasi;         // "Jl, Desa, Kecamatan, Kota, Provinsi"
    std::string jamBuka;        // "24 hours", "08:00-23:00"
    std::string nomorTelepon;   // "(SO41) 47OIOS"
    Ulasan ulasan;              // "Yuita", "Gacor Rumah Sakitnya" "5"
    std::string penghargaan;    // "1st Best Hospital in Malang by Ministry of Health"

    [[nodiscard]] std::string GetNamaRumahSakit() const { return nama; }
};

struct SesiPraktik {
    std::string hari;           // Contoh: "Senin"
    std::string jamMulai;       // Format: "08:00"
    std::string jamSelesai;     // Format: "10:00"
    std::string sesi;           // Contoh: "Pagi" / "Sore"
};

struct PengalamanPraktik {
    std::string rumahSakit;      // "RSUD Kota Molang"
    std::string waktu;          // "13 Tahun 9 Bulan"
    std::string jabatan;        // "Chief Financial Officer"
};


#endif //DOCTORHELPER_H
