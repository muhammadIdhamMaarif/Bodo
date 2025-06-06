cmake_minimum_required(VERSION 3.31)
project(Bodo)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bodo main.cpp
        AVLTree.h
        Patient.cpp
        Patient.h
        DiseaseHistory.cpp
        DiseaseHistory.h)
