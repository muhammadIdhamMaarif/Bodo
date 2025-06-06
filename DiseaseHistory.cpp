//
// Created by Acer on 06/06/2025.
//

#include "DiseaseHistory.h"
#include <sstream>

void DiseaseHistory::AddDisease(const std::string& disease) {
    diseases.push_back(disease);
}

const std::vector<std::string>& DiseaseHistory::GetDiseases() const {
    return diseases;
}

bool DiseaseHistory::IsEmpty() const {
    return diseases.empty();
}

std::string DiseaseHistory::toString() const {
    std::stringstream ss;
    ss << "Riwayat Penyakit: " << "\n";
    int index = 1;
    for (const auto& penyakit : diseases) {
        ss << index++ << ". " << penyakit << "\n";
    }
    return ss.str();
}
