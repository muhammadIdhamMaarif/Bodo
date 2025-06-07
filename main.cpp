#include "Core/PersonData/Patient.h"
#include "Core/Helper/InterfaceHelper.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace Data;

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

int main(int argc, char** argv) {
    init();
    system("cls");
    Interface::DrawHeader();
    Interface::PrintNamaKelompok();
    Interface::PressAnyKeyToStartProgram();
    return 0;
}

