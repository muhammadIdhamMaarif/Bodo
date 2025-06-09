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

    void AddDiseaseHistory(const std::string& param);
    void AddDiseaseHistoryByID(int id);
    void AddDiseaseHistoryByName(std::string name);

    void ViewPatientDiseaseHistory(const std::string& param);
    void ViewPatientDiseaseHistoryByID(int id);
    void ViewPatientDiseaseHistoryByName(std::string name);

    bool HasDiseaseHistory(const std::string& param);
    bool HasDiseaseHistoryByID(int id);
    bool HasDiseaseHistoryByName(std::string name);

    void AddMedicalCheckupRecord(const std::string& param);
    void AddMedicalCheckupRecordByID(int id);
    void AddMedicalCheckupRecordByName(std::string name);

    void ViewPatientMedicalRecord(const std::string& param);
    void ViewPatientMedicalRecordByID(int id);
    void ViewPatientMedicalRecordByName(std::string name);

    void PatientSummary(int id);
    void PatientSummary(std::string name);

    void ExportPatientDataToFile();
    void ImportPatientDataFromFile();

}// Manager

#endif //PATIENTMANAGEMENT_H
