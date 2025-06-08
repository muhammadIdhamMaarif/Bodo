//
// Created by Acer on 08/06/2025.
//

#ifndef PATIENTRECORD_HPP
#define PATIENTRECORD_HPP

#include "../Abstract/AVLTree.h"


class PatientRecord {
private:
    AVLTree::AVL<Data::Patient> Data;
public:
    void AddPatient(const Data::Patient& newPatient) {
        Data.insert(newPatient);
    }

    void SearchPatient(int id);
    void SearchPatient(std::string name);
    void EditPatientInformation(int id);
    void EditPatientInformation(std::string name);
    void DeletePatient(int id);
    void DeletePatient(std::string name);
    void AddDiseaseHistory(int id);
    void AddDiseaseHistory(std::string name);
    void ViewPatientDiseaseHistory(int id);
    void ViewPatientDiseaseHistory(std::string name);
    bool HasDiseaseHistory(int id);
    bool HasDiseaseHistory(std::string name);
    void AddMedicalCheckupRecord(int id, Data::Checkup checkup);
    void AddMedicalCheckupRecord(std::string name, Data::Checkup checkup);
    void ViewPatientMedicalRecord(int id);
    void ViewPatientMedicalRecord(std::string name);
    void PatientSummary(int id);
    void PatientSummary(std::string name);
    void ExportPatientDataToFile(std::string filename);
    void ImportPatientDataFromFile(std::string path);
};


#endif //PATIENTRECORD_HPP
