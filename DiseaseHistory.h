//
// Created by Acer on 06/06/2025.
//

#ifndef DISEASEHISTORY_H
#define DISEASEHISTORY_H

#include <vector>
#include <string>

class DiseaseHistory {
private:
    std::vector<std::string> diseases;

public:
    DiseaseHistory() = default;
    void AddDisease(const std::string& disease);
    [[nodiscard]] const std::vector<std::string>& GetDiseases() const;
    [[nodiscard]] bool IsEmpty() const;
    [[nodiscard]] std::string toString() const;
};


#endif //DISEASEHISTORY_H
