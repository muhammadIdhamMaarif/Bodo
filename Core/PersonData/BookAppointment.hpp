#ifndef BOOKAPPOINTMENT_HPP
#define BOOKAPPOINTMENT_HPP

#include <string>
#include "Doctor.h"
#include "Patient.h"
#include "../../Data/DoctorData.h"
#include "../../Data/PatientData.h"
#include "../Helper/ColorList.h"

class Appointment {
private:
    static int nextID;
    int appointmentId;
    int patientId;
    int doctorId;
    std::string appointmentDate;   // Format: YYYY-MM-DD
    std::string appointmentTime;   // Format: HH:MM
    std::string reason;
    std::string status;            // Scheduled, Completed, Cancelled

public:
    // Default Constructor
    Appointment() {
        appointmentId = nextID++;
        patientId = -1;
        doctorId = -1;
        appointmentDate = "";
        appointmentTime = "";
        reason = "";
        status = "Scheduled";
    }

    // Parameterized Constructor
    Appointment(
        const std::string& appointmentId,
        const int& patientId,
        const int& doctorId,
        const std::string& department,
        const std::string& appointmentDate,
        const std::string& appointmentTime,
        const std::string& reason = ""
    ) {
        this->appointmentId = nextID++;
        this->patientId = patientId;
        this->doctorId = doctorId;
        this->appointmentDate = appointmentDate;
        this->appointmentTime = appointmentTime;
        this->reason = reason;
        this->status = "Scheduled";
    }

    // Getters
    int getAppointmentId() const { return appointmentId; }
    int getPatientId() const { return patientId; }
    int getDoctorId() const { return doctorId; }
    std::string getAppointmentDate() const { return appointmentDate; }
    std::string getAppointmentTime() const { return appointmentTime; }
    std::string getReason() const { return reason; }
    std::string getStatus() const { return status; }

    // Setters
    void setPatientId(const int& data) { patientId = data; }
    void setDoctorId(const int& data) { doctorId = data; }
    void setAppointmentDate(const std::string& data) { appointmentDate = data; }
    void setAppointmentTime(const std::string& data) { appointmentTime = data; }
    void setReason(const std::string& data) { reason = data; }
    void setStatus(const std::string& data) { status = data; }

    static int getNextID() { return nextID; }
    static void setNextID(int id) { nextID = id; }

    // Utility Functions
    void reschedule(const std::string& newDate, const std::string& newTime) {
        appointmentDate = newDate;
        appointmentTime = newTime;
        status = "Rescheduled";
    }

    void cancel() {
        status = "Cancelled";
    }

    void markCompleted() {
        status = "Completed";
    }
};

inline Data::Patient CariPasienByIDSpesial(int id) {
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool found = false;
    Data::Patient patientFound(false);
    for (const Data::Patient& patient : Database::PatientLinear) {
        if (patient.GetID() == id) {
            found = true;
            patientFound = patient;
            break;
        }
    }
    return patientFound;
}
inline Data::Doctor CariDokterByIDSpesial(int id) {
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool found = false;
    Data::Doctor patientFound(false);
    for (const Data::Doctor& patient : Database::DoctorList) {
        if (patient.GetID() == id) {
            found = true;
            patientFound = patient;
            break;
        }
    }
    return patientFound;
}

inline std::ostream& operator<<(std::ostream& os, const Appointment& appt) {
    os << Color::CYAN << "\n  ID           : " << Color::GREEN << appt.getAppointmentId()
       << Color::CYAN << "\n  Patient Name : " << Color::RESET << CariPasienByIDSpesial(appt.getPatientId()).GetNama()
       << Color::CYAN << "\n  Doctor Name  : " << Color::RESET << CariDokterByIDSpesial(appt.getDoctorId()).GetNama()
       << Color::CYAN << "\n  Date         : " << Color::RESET << appt.getAppointmentDate()
       << Color::CYAN << "\n  Time         : " << Color::RESET << appt.getAppointmentTime()
       << Color::CYAN << "\n  Reason       : " << Color::RESET << appt.getReason()
       << Color::CYAN << "\n  Status       : " << Color::RESET << appt.getStatus()
       << "\n";
    return os;
}

#endif // BOOKAPPOINTMENT_HPP
