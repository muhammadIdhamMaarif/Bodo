cmake_minimum_required(VERSION 3.31)
project(Bodo)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bodo main.cpp
        Core/Abstract/AVLTree.h
        Core/PersonData/Patient.cpp
        Core/PersonData/Patient.h
        Core/Records/DiseaseHistory.cpp
        Core/Records/DiseaseHistory.h
        Core/PersonData/Person.cpp
        Core/PersonData/Person.h
        Core/Helper/BirthDateHelper.cpp
        Core/Helper/BirthDateHelper.h
        Core/Records/MedicalRecord.cpp
        Core/Records/MedicalRecord.h
        Core/PersonData/Doctor.cpp
        Core/PersonData/Doctor.h
        Core/Helper/DoctorHelper.h
        Core/Abstract/Queue.h
        Core/Abstract/LinkedQueue.h
        Interface/CLI/CLI11.hpp
        Core/Helper/InterfaceHelper.cpp
        Core/Helper/InterfaceHelper.h
        Core/Helper/ColorList.h
        Core/Helper/TextInspector.h
        Interface/CLI/CommandLineInterface.cpp
        Interface/CLI/CommandLineInterface.h
        Interface/GUI/GraphicalUserInterface.cpp
        Interface/GUI/GraphicalUserInterface.h
        Animation/DonutSpinning.hpp
        Animation/SplashScreen.hpp
        Animation/SplashScreenText.h
        Interface/CLI/DoctorManager.cpp
        Interface/CLI/DoctorManager.h
        Interface/CLI/PatientManagement.cpp
        Interface/CLI/PatientManagement.h
        Interface/CLI/BookAppointmentManager.cpp
        Interface/CLI/BookAppointmentManager.h
        Data/PatientData.h
        Core/Records/PatientRecord.hpp
        StreamingAssets/json.hpp
        StreamingAssets/SaveLoad.hpp
        Data/DoctorData.h
        Core/Abstract/AVLTreeDoctor.h
        Core/PersonData/BookAppointment.hpp
        Core/PersonData/BookAppointment.cpp
)
