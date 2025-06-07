#ifndef INTERFACEHELPER_H
#define INTERFACEHELPER_H
#include "ColorList.h"
#include "TextInspector.h"
#include "../../Interface/CLI/CommandLineInterface.h"
#include "../../Interface/GUI/GraphicalUserInterface.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif
using namespace Color;
using namespace Text;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13


namespace Interface {

    void ClearScreen();
    void DrawInputBox(const std::string& prompt, const std::string& currentInput);
    std::string GetInput(const std::string& prompt);
    void DrawHeader();
    void PrintNamaKelompok();
    void PressAnyKeyToStartProgram();

    // Pilihan buat tipe interface
    void InterfaceSelection();
    void SetColor(int color);
    void CommandLineInterfaceInvoke();
    void GraphicalUserInterfaceInvoke();
    void Exit();
    void DrawMenu(const std::string choices[], int size, int selected);


} // Interface

#endif //INTERFACEHELPER_H
