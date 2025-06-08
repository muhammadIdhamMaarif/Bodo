
// ============================================================================
// | DiseaseHistory.cpp                                                       |
// | Kegunaan : Menyimpan dan mengelola riwayat penyakit seorang pasien       |
// |                                                                          |
// | Penjelasan Singkat Kode :                                                |
// |    Implementasi class DiseaseHistory untuk menambahkan, mengambil,       |
// |    mengecek, dan mencetak daftar penyakit pasien.                        |
// |                                                                          |
// | Penjelasan Method :                                                      |
// |    1. AddDisease                                                         |
// |          Menambahkan nama penyakit ke dalam daftar vektor `diseases`.    |
// |    2. GetDiseases                                                        |
// |          Mengembalikan referensi ke seluruh daftar penyakit.             |
// |    3. IsEmpty                                                            |
// |          Mengecek apakah daftar penyakit kosong.                         |
// |    4. toString                                                           |
// |          Mengembalikan string format dari seluruh riwayat penyakit.      |
// ============================================================================

#include "DiseaseHistory.h"
#include <sstream>
#include <iomanip>

#include "../Helper/ColorList.h"

void DiseaseHistory::AddDisease(const std::string& disease) {
    diseases.push_back(disease);
}

const std::vector<std::string>& DiseaseHistory::GetDiseases() const {
    return diseases;
}

bool DiseaseHistory::IsEmpty() const {
    return diseases.empty();
}

std::string DiseaseHistory::toString() const {
    std::stringstream ss;
    ss << "Riwayat Penyakit: " << "\n";
    int index = 0;
    for (const auto& penyakit : diseases) {
        ss << Color::GREEN << "   " << std::setfill('0') << std::setw(3)
           << ++index << ". " << penyakit << "\n" << Color::RESET;
    }
    return ss.str();
}