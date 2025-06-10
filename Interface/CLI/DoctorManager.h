//
// Created by Acer on 08/06/2025.
//

#ifndef DOCTORMANAGER_H
#define DOCTORMANAGER_H
#include "../../Core/PersonData/Doctor.h"

namespace Manager {

    std::string trim(const std::string& str);
    std::chrono::year_month_day ParseDate(const std::string& dateStr);
    std::optional<int> safeStringToInt(const std::string& input);
    time_t convertToTimeT(const std::string& dateStr);

    Data::Doctor DoctorInputField();
    void AddNewDoctor();
    void ViewAllDoctor();

    void SearchDoctor(const std::string& param);
    void SearchDoctorByID(int id);
    void SearchDoctorByName(const std::string& name);
    void SearchDoctorAction(const Data::Doctor& doctor);

    void UpdateDoctor(const std::string& param);
    void UpdateDoctorByID(int id);
    void UpdateDoctorByName(const std::string& name);
    void UpdateDoctorAction(const Data::Doctor* arr, Data::Doctor* avl);

    void DeleteDoctor(const std::string& param);
    void DeleteDoctorByID(int id);
    void DeleteDoctorByName(const std::string& name);
    void DeteleDoctorAction(const Data::Doctor* arr, Data::Doctor* avl);

    void AddDoctorSchedule(const std::string& param);
    void AddDoctorScheduleByID(int id);
    void AddDoctorScheduleByName(const std::string& name);
    void AdddoctorScheduleAction(Data::Doctor* arr, Data::Doctor* avl);

    void AddDoctorExperience(const std::string& param);
    void AddDoctorExperienceByID(int id);
    void AddDoctorExperienceByName(const std::string& name);
    void AddDoctorExperienceAction(Data::Doctor* arr, Data::Doctor* avl);

    void AddDoctorEducationHistory(const std::string& param);
    void AddDoctorEducationHistoryByID(int id);
    void AddDoctorEducationHistoryByName(const std::string& name);
    void ADdDoctorEducationHistoryAction(Data::Doctor* arr, Data::Doctor* avl);

    void AddDoctorReview(const std::string& param);
    void AddDoctorReviewByID(int id);
    void AddDoctorReviewByName(const std::string& name);
    void AddDoctorReviewAction(Data::Doctor* arr, Data::Doctor* avl);

    void AddMedicalSpecialization(const std::string& param);
    void AddMedicalSpecializationByID(int id);
    void AddMedicalSpecializationByName(const std::string& name);
    void AddMedicalSpecializationAction(Data::Doctor* arr, Data::Doctor* avl);

    void FilterDoctorBySpecialization();

    void SortDoctorByName();

    void CopyDoctor(Data::Doctor* target, const Data::Doctor& data);





} // Manager

#endif //DOCTORMANAGER_H
