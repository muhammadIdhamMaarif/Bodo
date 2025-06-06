
// ============================================================================
// | Person.cpp                                                               |
// | Kegunaan : Membantu tanggal lahir (BirthDate) dalam Person               |
// |                                                                          |
// | Penjelasan Singkat Kode :                                                |
// |    File ini berisi implementasi fungsi `makeBirthDate()` yang mengubah   |
// |    input tahun, bulan, dan hari menjadi objek tanggal (`BirthDate`)      |
// |    sesuai versi C++ yang digunakan (C++20 atau lebih lama).              |
// |                                                                          |
// | Penjelasan Fungsi :                                                      |
// |    1. makeBirthDate(int year, int month, int day)                        |
// |          - Jika menggunakan C++20: menggunakan std::chrono               |
// |          - Jika di bawah C++20: menggunakan struct std::tm               |
// ============================================================================

#include "Person.h"

#if __cplusplus >= 202002L
        // C++20 version
        BirthDate makeBirthDate(int year, int month, int day) {
            return std::chrono::year{year} /
                   std::chrono::month{static_cast<unsigned>(month)} /
                   std::chrono::day{static_cast<unsigned>(day)};
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

#endif