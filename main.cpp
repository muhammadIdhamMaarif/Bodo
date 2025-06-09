#include "Core/PersonData/Patient.h"
#include "Core/Helper/InterfaceHelper.h"
#include <iostream>
#include <string>
#include "StreamingAssets/json.hpp"
#include "StreamingAssets/SaveLoad.hpp"
#ifdef _WIN32
#define NOMINMAX
#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#endif
using namespace Data;

using json = nlohmann::json;

void init() {
#ifdef _WIN32
    // Enable ANSI escape codes sekali waktu mulai
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#else
    std::cout << "Program does not support non Windows32 devices\n";
    exit(1);
#endif
}

void LoadFile() { SLManager::LoadData(); }
void SaveFile() { SLManager::SaveData(); }
inline void EnsureDataFileExists() {
    namespace fs = std::filesystem;

    const std::string dir = "SaveData";
    const std::string filepath = dir + "/Data.json";

    // Cek apakah direktori SaveData ada
    if (!fs::exists(dir)) {
        fs::create_directories(dir);
    }

    // Cek apakah Data.json ada
    if (!fs::exists(filepath)) {
        // Inisialisasi JSON kosong seperti permintaan
        json JSON = json::array({
            {
                {"data", json::array()},
                {"name", "Patient"}
            },
            {
                {"data", json::array()},
                {"name", "Doctor"}
            },
            {
                {"data", json::array()},
                {"name", "Appointment"}
            }
        });

        std::ofstream file(filepath);
        if (file.is_open()) {
            file << JSON.dump(4); // indentasi 4 spasi
            file.close();
        } else {
            std::cerr << "Failed to create default Data.json file.\n";
        }
    }
}


int main(int argc, char** argv) {
    init();
    system("cls");
    EnsureDataFileExists();
    LoadFile();
    Interface::DrawHeader();
    Interface::PrintNamaKelompok();
    Interface::PressAnyKeyToStartProgram();
    return 0;
}

