//
// Created by Acer on 07/06/2025.
//

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
