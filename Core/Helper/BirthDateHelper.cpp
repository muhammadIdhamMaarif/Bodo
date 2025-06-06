
// ============================================================================
// | BirthDataHelper.cpp                                                      |
// | Kegunaan : Implementasi fungsi pembantu untuk Birth Date                 |
// |                        q                                                 |
// | Penjelasan Singkat Kode :                                                |
// |    Mengecek apakah user menggunakan C++ 20 atau lebih baru, jika iya,    |
// |    maka akan implementasi datetime dengan menggunakan chrono, dan jika   |
// |    tidak maka akan implmenetasi dengan ctime.                            |
// |                                                                          |
// | Penjelasan Method :                                                      |
// |    1. makeBirthDate                                                      |
// |          Digunakan untuk mengubah parameter menjadi class chrono atau    |
// |          ctime sesuai dengan versi C++ yang digunakan                    |
// ============================================================================

#include "BirthDateHelper.h"

#if __cplusplus >= 202002L
inline BirthDate makeBirthDate(int year, int month, int day) {
    return std::chrono::year{year} /
           std::chrono::month{static_cast<unsigned>(month)} /
           std::chrono::day{static_cast<unsigned>(day)};
}

#else
inline BirthDate makeBirthDate(int year, int month, int day) {
    std::tm date{};
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    return date;
}
#endif