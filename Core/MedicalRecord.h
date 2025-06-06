
// ============================================================================
// | MedicalRecord.h                                                          |
// | Kegunaan : Deklarasi struktur data rekam medis dan kelas pengelolanya.   |
// |                                                                          |
// | Penjelasan Singkat Kode :                                                |
// |    Header ini mendefinisikan struktur `Checkup` untuk menyimpan          |
// |    informasi pemeriksaan pasien, serta kelas `MedicalRecord` yang        |
// |    bertugas mengelola seluruh riwayat pemeriksaan tersebut.              |
// |                                                                          |
// | Penjelasan Method :                                                      |
// |    1. AddRecord                                                          |
// |          Menambahkan satu data pemeriksaan ke dalam daftar rekam medis.  |
// |    2. GetAllRecords                                                      |
// |          Mengambil seluruh daftar rekam medis pasien.                    |
// |    3. toString                                                           |
// |          Mengembalikan seluruh rekam medis dalam bentuk string rapi.     |
// ============================================================================

#ifndef MEDICAL_RECORD_H
#define MEDICAL_RECORD_H

#include <string>
#include <vector>
#include <ctime>

namespace Data {

    struct Checkup {
        std::time_t tanggal;         // Tanggal checkup/treatment
        std::string dokter;          // Nama doketer
        std::string keluhan;         // Keluhan pasien
        std::string tindakan;        // Diagnosis / treatment
        std::string resep;           // resep dokter dengan tulisanya yang cantik
    };

    class MedicalRecord {
    private:
        std::vector<Checkup> records;   // Daftar riwayat periksa pasien

    public:
        void AddRecord(const Checkup& record);
        const std::vector<Checkup>& GetAllRecords() const;

        std::string toString() const;
    };

}

#endif // MEDICAL_RECORD_H
