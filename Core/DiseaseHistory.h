
// ============================================================================
// | DiseaseHistory.h                                                         |
// | Kegunaan : Deklarasi class DiseaseHistory untuk menyimpan riwayat        |
// |           penyakit pasien                                                |
// |                                                                          |
// | Penjelasan Singkat Kode :                                                |
// |    Mendefinisikan struktur data dan fungsi untuk menangani riwayat       |
// |    penyakit menggunakan vektor string sebagai container utama.           |
// |                                                                          |
// | Penjelasan Method :                                                      |
// |    1. AddDisease                                                         |
// |          Menambahkan string nama penyakit ke dalam vektor `diseases`.    |
// |    2. GetDiseases                                                        |
// |          Mengembalikan referensi const ke daftar penyakit.               |
// |    3. IsEmpty                                                            |
// |          Mengecek apakah daftar penyakit kosong.                         |
// |    4. toString                                                           |
// |          Mengubah seluruh daftar penyakit menjadi string terformat.      |
// ============================================================================

#ifndef DISEASEHISTORY_H
#define DISEASEHISTORY_H

#include <vector>
#include <string>

class DiseaseHistory {
private:
    std::vector<std::string> diseases;      // Daftar riwayat penyakit

public:
    DiseaseHistory() = default;
    void AddDisease(const std::string& disease);
    [[nodiscard]] const std::vector<std::string>& GetDiseases() const;
    [[nodiscard]] bool IsEmpty() const;
    [[nodiscard]] std::string toString() const;
};


#endif //DISEASEHISTORY_H