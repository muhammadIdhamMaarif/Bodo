#include <iostream>
#include "Core/PersonData/Patient.h"
#include "Core/Helper/BirthDateHelper.h"

int main() {
    using namespace Data;

    // Create a patient with default constructor
    Patient patient1;

    // Set patient information manually (you can add setters if needed)
    patient1.SetNama("Ragil Saputra");
    patient1.SetTempatLahir("Bandung");
    patient1.SetJenisKelamin('L');
    patient1.SetGolonganDarah("O");
    patient1.SetAlamat("Jl. Merdeka No. 123");
    patient1.SetAgama("Islam");
    patient1.SetNomorTelepon("081234567890");
    patient1.SetEmail("ragil@example.com");
    patient1.SetTanggalLahir(makeBirthDate(2005, 12, 15));

    // Add some diseases
    patient1.TambahRiwayatPenyakit("Demam Berdarah");
    patient1.TambahRiwayatPenyakit("Malaria");

    // Print patient info
    std::cout << patient1.toString() << std::endl;

    return 0;
}