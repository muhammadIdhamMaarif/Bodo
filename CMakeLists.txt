cmake_minimum_required(VERSION 3.31)
project(Bodo)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bodo main.cpp
        Core/AVLTree.h
        Core/Patient.cpp
        Core/Patient.h
        Core/DiseaseHistory.cpp
        Core/DiseaseHistory.h
        Core/Person.cpp
        Core/Person.h
        Core/BirthDateHelper.cpp
        Core/BirthDateHelper.h
)
