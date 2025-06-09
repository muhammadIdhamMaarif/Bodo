//
// Created by Acer on 08/06/2025.
//

#ifndef PATIENTMANAGEMENT_H
#define PATIENTMANAGEMENT_H
#include <chrono>
#include <string>

#include "../../Core/PersonData/Patient.h"
#include "../../Core/Records/MedicalRecord.h"

namespace Manager {

    std::string trim(const std::string& str);
    Data::Patient PatientInputField();
    void AddNewPatient();
    std::chrono::year_month_day ParseDate(const std::string& dateStr);
    void ViewAllPatients();
    void SearchPatient(const std::string& param);
    void SearchPatientByName(const std::string& param);
    void SearchPatientByID(int id);
    void DataNotFoundErrorMessage();
    void EditPatientInformation(const std::string& param);
    void EditPatientInformationByID(int id);
    void EditPatientInformationByName(const std::string& name);
    void DeletePatient(const std::string& param);
    void DeletePatientByID(int id);
    void DeletePatientByName(std::string name);
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

}// Manager

#endif //PATIENTMANAGEMENT_H
