
// ============================================================================
// | Doctor.h                                                                 |
// | Kegunaan : Menyimpan deklarasi class Doctor                              |
// | Penjelasan Singkat Kode :                                                |
// |    Mendefinisikan class Doctor yang merupakan turunan dari Person.       |
// |    Menyimpan informasi seperti lokasi praktik, jadwal, pengalaman,       |
// |    riwayat pendidikan, ulasan pasien, dan spesialisasi medis.            |
// |                                                                          |
// | Penjelasan Property :                                                    |
// |    - nextID               : Generator ID unik untuk setiap dokter        |
// |    - ID                   : ID unik dokter                               |
// |    - ProfilDokter         : Deskripsi profil dokter                      |
// |    - Spesialis            : Spesialis bidang dokter                      |
// |    - JadwalPraktik        : Jadwal kerja dokter                          |
// |    - PengalamanPraktik    : Riwayat pengalaman kerja                     |
// |    - RiwayatPendidikan    : Riwayat pendidikan formal dokter             |
// |    - Ulasan               : Kumpulan ulasan dari pasien                  |
// |    - TindakanSpesialis    : Jenis tindakan medis/spesialisasi dokter     |
// ============================================================================

#ifndef DOCTOR_H
#define DOCTOR_H
#include "Person.h"
#include "../Helper/DoctorHelper.h"
#include <string>

namespace Data {

class Doctor : Person{
private:
    static int                      nextID;
    int                             ID;
    std::string                     ProfilDokter;
    std::string                     Spesialis;
    std::vector<SesiPraktik>        JadwalPraktik;
    std::vector<PengalamanPraktik>  PengalamanPraktikDokter;
    std::vector<std::string>        RiwayatPendidikan;
    std::vector<Ulasan>             UlasanDokter;
    std::vector<std::string>        TindakanSpesialis;

public:
    Doctor(bool isIncrimenting = true);
    Doctor(const std::string& nama, const std::string& spesialis, const std::string& profil);

    [[nodiscard]] std::string toString(int doctorNo) const;
    [[nodiscard]] std::string toStringRed(int doctorNo) const;

    void TambahJadwal(const SesiPraktik& sesi);
    void TambahPengalaman(const PengalamanPraktik& pengalaman);
    void TambahRiwayatPendidikan(const std::string& pendidikan);
    void TambahUlasan(const Ulasan& ulasan);
    void TambahTindakan(const std::string& tindakan);

    friend bool operator<(const Doctor& lhs, const Doctor& rhs) {
        return lhs.GetNama() < rhs.GetNama();
    }

    friend bool operator>(const Doctor& lhs, const Doctor& rhs) {
        return lhs.GetNama() > rhs.GetNama();
    }

    friend bool operator<=(const Doctor& lhs, const Doctor& rhs) {
        return lhs.GetNama() <= rhs.GetNama();
    }

    friend bool operator>=(const Doctor& lhs, const Doctor& rhs) {
        return lhs.GetNama() >= rhs.GetNama();
    }

    friend bool operator==(const Doctor& lhs, const Doctor& rhs) {
        return lhs.GetNama() == rhs.GetNama();
    }

    friend bool operator!=(const Doctor& lhs, const Doctor& rhs) {
        return lhs.GetNama() != rhs.GetNama();
    }

    // Getters
    [[nodiscard]] const std::string& GetProfilDokter() const;
    [[nodiscard]] const std::string& GetSpesialis() const;
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
    [[nodiscard]] const std::vector<SesiPraktik>& GetSesiPraktik() const;
    [[nodiscard]] const std::vector<PengalamanPraktik>& GetPengalamanPraktik() const;
    [[nodiscard]] const std::vector<Ulasan>& GetUlasanDokter() const;
    [[nodiscard]] const std::vector<std::string>& GetRiwayatPendidikan() const;
    [[nodiscard]] const std::vector<std::string>& GetTindakanSpesialis() const;

    // Setters
    void SetID(const int& id);
    void SetNama(const std::string& nama);
    void SetTempatLahir(const std::string& tempatLahir);
    void SetTanggalLahir(const BirthDate& tanggalLahir);
    void SetJenisKelamin(char jenisKelamin);
    void SetGolonganDarah(const std::string& golonganDarah);
    void SetAlamat(const std::string& alamat);
    void SetAgama(const std::string& agama);
    void SetNomorTelepon(const std::string& nomorTelepon);
    void SetEmail(const std::string& email);
    void SetProfilDokter(const std::string& profil);
    void SetSpesialis(const std::string& spesialis);
    void SetJadwalPraktik(const std::vector<SesiPraktik>& sesi);
    void SetPengalamanPraktik(const std::vector<PengalamanPraktik>& pengalaman);
    void SetRiwayatPendidikan(const std::vector<std::string>& riwayatPendidikan);
    void SetUlasanDokter(const std::vector<Ulasan>& ulasanDokter);
    void SetTindakanSpesialis(const std::vector<std::string>& tindakanSpesialis);

    static void UpdateNextIDFromExisting(int maxID) { nextID = maxID; }
    static int GetNextID() { return nextID; }
    static void SetNextID(int id) { nextID = id; }

};

} // Data

#endif //DOCTOR_H

