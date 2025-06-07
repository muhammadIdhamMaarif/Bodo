//
// Created by Acer on 07/06/2025.
//

#ifndef COMMANDLINEINTERFACE_H
#define COMMANDLINEINTERFACE_H
#include "../../Core/Helper/ColorList.h"
#include "../../Core/Helper/TextInspector.h"
#include "../../Core/Helper/InterfaceHelper.h"
#include <string>
#include <chrono>
using namespace Color;
using namespace Text;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

namespace CLI {

    void OnCommandLineInterface();
    int GetKeyPress();
    std::string SetWhitespaces(std::string s);
    void SetColor(int color);
    void MainMenuSelector();
    void SelectorMainMenu(const std::string menu[], const int numChoices, std::string header);
    void SelectorManageDoctor(const std::string menu[], const int numChoices, std::string header);
    void SelectorManagePatient(const std::string menu[], const int numChoices, std::string header);
    void SelectorBookAppointment(const std::string menu[], const int numChoices, std::string header);
    void DrawMenu(const std::string choices[], int size, int selected, std::string header);

} // CLI

#endif //COMMANDLINEINTERFACE_H
