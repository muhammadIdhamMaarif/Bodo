
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
    Doctor();
    Doctor(const std::string& nama, const std::string& spesialis, const std::string& profil);

    [[nodiscard]] int GetID() const;
    [[nodiscard]] std::string toString() const;

    void SetProfilDokter(const std::string& profil);
    void SetSpesialis(const std::string& spesialis);

    void TambahJadwal(const SesiPraktik& sesi);
    void TambahPengalaman(const PengalamanPraktik& pengalaman);
    void TambahRiwayatPendidikan(const std::string& pendidikan);
    void TambahUlasan(const Ulasan& ulasan);
    void TambahTindakan(const std::string& tindakan);

};

} // Data

#endif //DOCTOR_H
