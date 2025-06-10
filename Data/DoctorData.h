//
// Created by Acer on 10/06/2025.
//

#ifndef DOCTORDATA_H
#define DOCTORDATA_H
#include "../Core/Abstract/AVLTreeDoctor.h"
#include "../Core/PersonData/Doctor.h"

namespace Database {
    inline AVLTreeDoctor::AVLDoctor DoctorAVL;
    inline std::vector<Data::Doctor> DoctorList;
}

#endif //DOCTORDATA_H
