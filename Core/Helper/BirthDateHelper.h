
// ============================================================================
// | BirthDataHelper.h                                                        |
// | Kegunaan : Deklarasi fungsi pembantu untuk Birth Date                    |
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

#ifndef BIRTHDATEHELPER_H
#define BIRTHDATEHELPER_H

#include <ctime>

#if __cplusplus >= 202002L
    #include <chrono>
#endif

using BirthDate =
#if __cplusplus >= 202002L
    std::chrono::year_month_day;
#else
        std::tm;
#endif

BirthDate makeBirthDate(int year, int month, int day);

#endif //BIRTHDATEHELPER_H
