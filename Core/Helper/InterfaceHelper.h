#ifndef INTERFACEHELPER_H
#define INTERFACEHELPER_H
#include "ColorList.h"
#include "TextInspector.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>

#ifdef _WIN32
#include <windows.h>
#endif
using namespace Color;
using namespace Text;

namespace Interface {

    void ClearScreen();
    void DrawInputBox(const std::string& prompt, const std::string& currentInput);
    std::string GetInput(const std::string& prompt);
    void DrawHeader();
    void PrintNamaKelompok();

} // Interface

#endif //INTERFACEHELPER_H
