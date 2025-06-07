#include "Core/PersonData/Patient.h"
#include "Core/Helper/InterfaceHelper.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace Data;

void init();
void WelcomeMenu();
void OnCommandLineInterface();
void OnGraphicalUserInterface();
void ClearScreen();

int main(int argc, char** argv) {
    init();
    Interface::DrawHeader();
    Interface::PrintNamaKelompok();
    // WelcomeMenu();
    return 0;
}

void WelcomeMenu() {
    std::string name = Interface::GetInput("Enter your name");
    Interface::ClearScreen();
    std::cout << GREEN << "Hello, " << BOLD << name << RESET << GREEN << "! Welcome to the Cool CLI!\n" << RESET;
}

void OnCommandLineInterface() {

}

void OnGraphicalUserInterface() {

}

void init() {
    #ifdef _WIN32
        // Enable ANSI escape codes sekali waktu mulai
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    #endif
}
