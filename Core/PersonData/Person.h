
// ============================================================================
// | Person.h                                                                 |
// | Kegunaan : Deklarasi kelas dasar Person                                  |
// |                                                                          |
// | Penjelasan Singkat Kode :                                                |
// |    Header ini mendeklarasikan kelas `Person` sebagai class dasar yang    |
// |    menyimpan data umum seseorang seperti nama, tanggal lahir, jenis      |
// |    kelamin, dan informasi kontak. Mendukung C++20 dan versi sebelumnya.  |
// |                                                                          |
// | Penjelasan Kelas :                                                       |
// |    1. class Person                                                       |
// |          - Menyediakan field proteksi untuk informasi identitas umum     |
// |          - Digunakan sebagai base class untuk turunan seperti Patient    |
// |    2. BirthDate                                                          |
// |          - Alias untuk std::chrono::year_month_day (C++20)               |
// |          - Alias untuk std::tm (pra-C++20)                               |
// ============================================================================

#ifndef PERSON_H
#define PERSON_H

#if __cplusplus >= 202002L
    #include <chrono>
    using BirthDate = std::chrono::year_month_day;
#else
#include <ctime>
using BirthDate = std::tm;
#endif

class Person {
protected:
    std::string     Nama;
    std::string     TempatLahir;
    BirthDate       TanggalLahir;
    char            JenisKelamin;
    std::string     GolonganDarah;
    std::string     Alamat;
    std::string     Agama;
    std::string     NomorTelepon;
    std::string     Email;
};

#endif //PERSON_H