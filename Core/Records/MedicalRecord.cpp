
// ============================================================================
// | MedicalRecord.cpp                                                        |
// | Kegunaan : Implementasi fungsi untuk menyimpan dan menampilkan           |
// |            riwayat pemeriksaan medis pasien.                             |
// |                                                                          |
// | Penjelasan Singkat Kode :                                                |
// |    File ini mengelola daftar rekam medis pasien yang berisi data         |
// |    pemeriksaan seperti tanggal, dokter, keluhan, tindakan, dan resep.    |
// |                                                                          |
// | Penjelasan Method :                                                      |
// |    1. AddRecord                                                          |
// |          Menambahkan satu entri pemeriksaan (Checkup) ke dalam records.  |
// |    2. GetAllRecords                                                      |
// |          Mengembalikan seluruh data pemeriksaan dalam bentuk vektor.     |
// |    3. toString                                                           |
// |          Mengembalikan string yang sudah diformat berisi seluruh         |
// |          informasi pemeriksaan, termasuk konversi waktu ke format        |
// |          yyyy-mm-dd.                                                     |
// ============================================================================

#include "MedicalRecord.h"
#include <sstream>
#include <iomanip>

#include "../Helper/ColorList.h"

namespace Data {

    void MedicalRecord::AddRecord(const Checkup& record) {
        records.push_back(record);
    }

    const std::vector<Checkup>& MedicalRecord::GetAllRecords() const {
        return records;
    }

    std::string MedicalRecord::toString() const {
        std::stringstream ss;
        ss << Color::CYAN << "Riwayat Pemeriksaan Medis :\n" << Color::RESET;
        int index = 0;
        for (const auto& r : records) {
            std::tm* tm_ptr = std::localtime(&r.tanggal);
            ss << Color::GREEN << std::setfill('0') << std::setw(3) << ++index
                          << std::put_time(tm_ptr, "%Y-%m-%d")
                          << "\n   Dokter: " << r.dokter
                          << "\n   Keluhan: " << r.keluhan
                          << "\n   Tindakan: " << r.tindakan
                          << "\n   Resep: " << r.resep << "\n\n";
        }
        return ss.str();
    }

}
