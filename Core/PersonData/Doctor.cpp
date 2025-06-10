
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

#include "../Helper/ColorList.h"

namespace Data {

int Doctor::nextID = 1;

Doctor::Doctor(bool isIncrimenting) : ID(nextID++) {
    if (!isIncrimenting) {nextID--;}
}

Doctor::Doctor(const std::string& nama, const std::string& spesialis, const std::string& profil)
    : ID(nextID++) {
    Nama = nama;
    Spesialis = spesialis;
    ProfilDokter = profil;
}

    void Doctor::TambahJadwal(const SesiPraktik& sesi) { JadwalPraktik.push_back(sesi); }
    void Doctor::TambahPengalaman(const PengalamanPraktik& pengalaman) { PengalamanPraktikDokter.push_back(pengalaman); }
    void Doctor::TambahRiwayatPendidikan(const std::string& pendidikan) { RiwayatPendidikan.push_back(pendidikan); }
    void Doctor::TambahUlasan(const Ulasan& ulasan) { UlasanDokter.push_back(ulasan); }
    void Doctor::TambahTindakan(const std::string& tindakan) { TindakanSpesialis.push_back(tindakan); }

    // Getters
    const std::string& Doctor::GetProfilDokter() const { return ProfilDokter; };
    const std::string& Doctor::GetSpesialis() const { return Spesialis; };
    int Doctor::GetID() const { return ID; }
    const std::string& Doctor::GetNama() const { return Nama; }
    const std::string& Doctor::GetTempatLahir() const { return TempatLahir; }
    BirthDate Doctor::GetTanggalLahir() const { return TanggalLahir; }
    char Doctor::GetJenisKelamin() const { return JenisKelamin; }
    std::string Doctor::GetGolonganDarah() const { return GolonganDarah; }
    const std::string& Doctor::GetAlamat() const { return Alamat; }
    const std::string& Doctor::GetAgama() const { return Agama; }
    const std::string& Doctor::GetNomorTelepon() const { return NomorTelepon; }
    const std::string& Doctor::GetEmail() const { return Email; }
    const std::vector<SesiPraktik>& Doctor::GetSesiPraktik() const { return JadwalPraktik; }
    const std::vector<PengalamanPraktik>& Doctor::GetPengalamanPraktik() const { return PengalamanPraktikDokter; }
    const std::vector<Ulasan>& Doctor::GetUlasanDokter() const { return UlasanDokter; }
    const std::vector<std::string>& Doctor::GetRiwayatPendidikan() const { return RiwayatPendidikan; };
    const std::vector<std::string>& Doctor::GetTindakanSpesialis() const { return TindakanSpesialis; }

    // Setters
    void Doctor::SetID(const int& id) { ID = id; };
    void Doctor::SetNama(const std::string& nama) { Nama = nama; }
    void Doctor::SetTempatLahir(const std::string& tempatLahir) { TempatLahir = tempatLahir; }
    void Doctor::SetTanggalLahir(const BirthDate& tanggalLahir) { TanggalLahir = tanggalLahir; }
    void Doctor::SetJenisKelamin(char jenisKelamin) { JenisKelamin = jenisKelamin; }
    void Doctor::SetGolonganDarah(const std::string& golonganDarah) { GolonganDarah = golonganDarah; }
    void Doctor::SetAlamat(const std::string& alamat) { Alamat = alamat; }
    void Doctor::SetAgama(const std::string& agama) { Agama = agama; }
    void Doctor::SetNomorTelepon(const std::string& nomorTelepon) { NomorTelepon = nomorTelepon; }
    void Doctor::SetEmail(const std::string& email) { Email = email; }
    void Doctor::SetProfilDokter(const std::string& profil) { ProfilDokter = profil; }
    void Doctor::SetSpesialis(const std::string& spesialis) { Spesialis = spesialis; }
    void Doctor::SetJadwalPraktik(const std::vector<SesiPraktik>& sesi) { JadwalPraktik = sesi; }
    void Doctor::SetPengalamanPraktik(const std::vector<PengalamanPraktik>& pengalaman) { PengalamanPraktikDokter = pengalaman; }
    void Doctor::SetRiwayatPendidikan(const std::vector<std::string>& riwayatPendidikan) { RiwayatPendidikan = riwayatPendidikan; }
    void Doctor::SetUlasanDokter(const std::vector<Ulasan>& ulasanDokter) { UlasanDokter = ulasanDokter; }
    void Doctor::SetTindakanSpesialis(const std::vector<std::string>& tindakanSpesialis) { TindakanSpesialis = tindakanSpesialis; }

    std::string Doctor::toString(int doctorNo) const {
        std::stringstream ss;
        if (doctorNo != -1) {
            ss << Color::YELLOW << "\n===================\n"
               << Color::YELLOW << "DOKTER NO " << doctorNo
               << Color::YELLOW << "\n===================\n";
        }
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
           << Color::CYAN << "     Email         : " << Color::RESET << Email << "\n";

        ss << Color::CYAN_VIBRANT << "     Jadwal Praktik : \n";
        int index = 0;
        for (const SesiPraktik& sesi : JadwalPraktik) {
            ss << Color::GREEN << "        " << std::setfill('0') << std::setw(3) << ++index
                          << Color::CYAN << ". Hari      : " << Color::RESET << sesi.hari
                          << Color::CYAN << "\n             Mulai     : " << Color::RESET << sesi.jamMulai
                          << Color::CYAN << "\n             selesai   : " << Color::RESET << sesi.jamSelesai
                          << Color::CYAN << "\n             Sesi      : " << Color::RESET << sesi.sesi << "\n" << Color::RESET;
        }

        ss << Color::CYAN_VIBRANT << "     Pengalaman Praktik : \n";
        index = 0;
        for (const PengalamanPraktik& praktik : PengalamanPraktikDokter) {
            ss << Color::GREEN << "        " << std::setfill('0') << std::setw(3) << ++index
                          << Color::CYAN << ". Rumah Sakit : " << Color::RESET << praktik.rumahSakit
                          << Color::CYAN << "\n             Jabatan     : " << Color::RESET << praktik.jabatan
                          << Color::CYAN << "\n             Waktu       : " << Color::RESET << praktik.waktu << "\n" << Color::RESET;
        }

        ss << Color::CYAN_VIBRANT << "     Riwayat Pendidikan : \n";
        index = 0;
        for (const std::string& pendidikan : RiwayatPendidikan) {
            ss << Color::GREEN << "        " << std::setfill('0') << std::setw(3) << ++index
                          << Color::CYAN << ". " << Color::RESET << pendidikan << "\n" << Color::RESET;
        }

        ss << Color::CYAN_VIBRANT << "     Ulasan Dokter : \n";
        index = 0;
        for (const Ulasan& ulasan : UlasanDokter) {
            ss << Color::GREEN << "        " << std::setfill('0') << std::setw(3) << ++index
                          << Color::CYAN << ". Rumah Sakit : " << Color::RESET << ulasan.tanggal
                          << Color::CYAN << "\n             Nama        : " << Color::RESET << ulasan.nama
                          << Color::CYAN << "\n             Komentar    : " << Color::RESET << ulasan.komentar
                          << Color::CYAN << "\n             Waktu       : " << Color::RESET << ulasan.rating << "\n" << Color::RESET;
        }

        ss << Color::CYAN_VIBRANT << "     Tindakan Specialis : \n";
        index = 0;
        for (const std::string& spesialis : TindakanSpesialis) {
            ss << Color::GREEN << "        " << std::setfill('0') << std::setw(3) << ++index
                          << Color::CYAN << ". " << Color::RESET << spesialis << "\n" << Color::RESET;
        }
        ss << "\n";

        return ss.str();
    }

    std::string Doctor::toStringRed(int doctorNo) const {
    std::stringstream ss;
    if (doctorNo != -1) {
        ss << Color::RED << "\n===================\n"
           << Color::RED << "DOKTER NO " << doctorNo
           << Color::RED << "\n===================\n";
    }
    ss << Color::RED << "     ID            : " << Color::RED << ID << "\n"
       << Color::RED << "     Nama          : " << Color::RED << Nama << "\n"
       << Color::RED << "     Tempat Lahir  : " << Color::RED << TempatLahir << "\n";

#if __cplusplus >= 202002L
    ss << Color::RED << "     Tanggal Lahir : " << Color::RED
       << static_cast<int>(TanggalLahir.year()) << "-"
       << static_cast<unsigned>(TanggalLahir.month()) << "-"
       << static_cast<unsigned>(TanggalLahir.day()) << "\n";
#else
    ss << Color::RED << "     Tanggal Lahir : " << Color::RED
       << (TanggalLahir.tm_year + 1900) << "-"
       << (TanggalLahir.tm_mon + 1) << "-"
       << TanggalLahir.tm_mday << "\n";
#endif

    ss << Color::RED << "     Jenis Kelamin : " << Color::RED << JenisKelamin << "\n"
       << Color::RED << "     Gol. Darah    : " << Color::RED << GolonganDarah << "\n"
       << Color::RED << "     Alamat        : " << Color::RED << Alamat << "\n"
       << Color::RED << "     Agama         : " << Color::RED << Agama << "\n"
       << Color::RED << "     Nomor Telepon : " << Color::RED << NomorTelepon << "\n"
       << Color::RED << "     Email         : " << Color::RED << Email << "\n";

    ss << Color::RED << "     Jadwal Praktik : \n";
    int index = 0;
    for (const SesiPraktik& sesi : JadwalPraktik) {
        ss << Color::RED << "        " << std::setfill('0') << std::setw(3) << ++index
                      << Color::RED << ". Hari      : " << Color::RED << sesi.hari
                      << Color::RED << "\n             Mulai     : " << Color::RED << sesi.jamMulai
                      << Color::RED << "\n             selesai   : " << Color::RED << sesi.jamSelesai
                      << Color::RED << "\n             Sesi      : " << Color::RED << sesi.sesi << "\n" << Color::RED;
    }

    ss << Color::RED << "     Pengalaman Praktik : \n";
    index = 0;
    for (const PengalamanPraktik& praktik : PengalamanPraktikDokter) {
        ss << Color::RED << "        " << std::setfill('0') << std::setw(3) << ++index
                      << Color::RED << ". Rumah Sakit : " << Color::RED << praktik.rumahSakit
                      << Color::RED << "\n             Jabatan     : " << Color::RED << praktik.jabatan
                      << Color::RED << "\n             Waktu       : " << Color::RED << praktik.waktu << "\n" << Color::RED;
    }

    ss << Color::RED << "     Riwayat Pendidikan : \n";
    index = 0;
    for (const std::string& pendidikan : RiwayatPendidikan) {
        ss << Color::RED << "        " << std::setfill('0') << std::setw(3) << ++index
                      << Color::RED << ". " << Color::RED << pendidikan << "\n" << Color::RED;
    }

    ss << Color::RED << "     Ulasan Dokter : \n";
    index = 0;
    for (const Ulasan& ulasan : UlasanDokter) {
        ss << Color::RED << "        " << std::setfill('0') << std::setw(3) << ++index
                      << Color::RED << ". Rumah Sakit : " << Color::RED << ulasan.tanggal
                      << Color::RED << "\n             Nama        : " << Color::RED << ulasan.nama
                      << Color::RED << "\n             Komentar    : " << Color::RED << ulasan.komentar
                      << Color::RED << "\n             Waktu       : " << Color::RED << ulasan.rating << "\n" << Color::RED;
    }

    ss << Color::RED << "     Tindakan Specialis : \n";
    index = 0;
    for (const std::string& spesialis : TindakanSpesialis) {
        ss << Color::RED << "        " << std::setfill('0') << std::setw(3) << ++index
                      << Color::RED << ". " << Color::RED << spesialis << "\n" << Color::RESET;
    }
    ss << "\n";

    return ss.str();
}

} // namespace Data
