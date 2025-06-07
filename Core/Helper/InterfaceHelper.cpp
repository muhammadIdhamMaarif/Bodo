//
// Created by Acer on 07/06/2025.
//

#define NOMINMAX
#define STRICT
#define WIN32_LEAN_AND_MEAN

#include "InterfaceHelper.h"
#include "../../Interface/CLI/CommandLineInterface.h"
#include "../../Interface/GUI/GraphicalUserInterface.h"
#include "../../Animation/DonutSpinning.hpp"
#include <iostream>
#include <vector>
#include <regex>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <cstdio>
#endif

#undef byte  // Just to be safe


namespace Interface {

    // pengganti _getch() di non windows
    int GetKeyPress() {
    #ifdef _WIN32
        return _getch();
    #else
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);          // buat dapetin attribut terminal terkini
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);        // matiin buffering ama echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); // pasang settings baru
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // balikin settings lama
        return ch;
    #endif
    }


    // Bersihkan layar
    void ClearScreen() {
        std::cout << "\033[2J\033[H";
    }

    // Bikin kotakan
    void DrawInputBox(const std::string& prompt, const std::string& currentInput) {
        ClearScreen();
        std::cout << BOX_COLOR;
        // std::cout << "╔══════════════════════════════════════╗\n";
        // std::cout << "║         " << BOLD << "Cool CLI Input Field" << RESET << BOX_COLOR << "         ║\n";
        // std::cout << "╠══════════════════════════════════════╣\n";
        // std::cout << "║ " << CYAN << prompt << RESET << ": " << currentInput;
        // for (size_t i = currentInput.length(); i < 30; ++i) std::cout << " ";
        // std::cout << BOX_COLOR << " ║\n";
        // std::cout << "╚══════════════════════════════════════╝\n";
        std::cout << RESET;
    }

    // Masukin input real-time per char
    std::string GetInput(const std::string& prompt) {
        std::string input;
        char ch;

        // Matikan line buffering buat Unix-like terminals
        #ifdef _WIN32
            // Windows terminal setup
            HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
            DWORD mode;
            GetConsoleMode(hStdin, &mode);
            SetConsoleMode(hStdin, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
        #else
            system("stty raw");
        #endif

        while (true) {
            DrawInputBox(prompt, input);
            ch = getchar();

            if (ch == '\r' || ch == '\n') break;      // Enter key
            else if (ch == 127 || ch == 8) {          // Backspace
                if (!input.empty()) input.pop_back();
            } else if (isprint(ch)) {
                input += ch;
            }
        }

        #ifdef _WIN32
            SetConsoleMode(hStdin, mode);  // Restore mode
        #else
            system("stty cooked");         // Restore terminal
        #endif

        return input;
    }

    void TextRainbowDiagonalColor(const std::string art) {
        const std::vector<int> rainbowColors = SeamlessRainbowColor_15_Colors;

        int colorIndex = 0;
        int x = 0, y = 0;

        for (char c : art) {
            if (c == '\n') {
                std::cout << '\n';
                y++;
                x = 0;
                continue;
            }

            // Color diagonally (atas kiri ke bawah kanan)
            int diagonal = (x + y) % rainbowColors.size();
            int color = rainbowColors[diagonal];

            std::cout << "\033[38;5;" << color << "m" << c << "\033[0m";
            x++;
        }

        std::cout << std::endl;
    }

    void DrawHeader() {
        TextRainbowDiagonalColor(BodoHeader);
    }

    void PrintNamaKelompok() {
        std::cout << YELLOW << "=================================================================" << RESET << "\n";
        std::cout << YELLOW << "| " << YELLOW << "TUGAS AKHIR ALGORITMA DAN DATA STRUKTUR                       " << YELLOW << "|\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "Nama Kelompok :" << std::string(47, ' ') << YELLOW << "|\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "   1. " << GREEN_VIBRANT << "Muhammad Idham Ma'arif" << "          " << RED << "(245150300111024)" << YELLOW << "       |\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "   2. " << GREEN_VIBRANT << "Muhammad Varrel Diandra" << "         " << RED << "(245150307111029)" << YELLOW << "       |\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "   3. " << GREEN_VIBRANT << "Muhammad Rafi Alfarel K" << "         " << RED << "(245150307111018)" << YELLOW << "       |\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "   4. " << GREEN_VIBRANT << "Rafi Ibnushaleh" << "                 " << RED << "(245150301111012)" << YELLOW << "       |\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "   5. " << GREEN_VIBRANT << "Afif Rafi Ardiyanto" << "             " << RED << "(245150307111026)" << YELLOW << "       |\n";
        std::cout << YELLOW << "|                                                               |\n";
        std::cout << YELLOW << "=================================================================" << RESET << "\n\n\n";
    }

    void PressAnyKeyToStartProgram() {
        std::string temp;
        std::cout << RED << "====================   PRESS ENTER KEY TO START   ====================\n" << RESET;
        std::getline(std::cin, temp);
        InterfaceSelection();
    }

    void InterfaceSelection() {
        const std::string menu[] = {
            "Command-Line Interface",
            "Graphical User Interface",
            "Exit"
        };
        const int numChoices = sizeof(menu) / sizeof(menu[0]);
        int selected = 0;

        while (true) {
            DrawMenu(menu, numChoices, selected);
            int key = GetKeyPress();

            if (key == 224) { // Arrow key prefix
                int arrow = GetKeyPress();
                if (arrow == KEY_UP) {
                    selected = (selected - 1 + numChoices) % numChoices;
                } else if (arrow == KEY_DOWN) {
                    selected = (selected + 1) % numChoices;
                }
            } else if (key == KEY_ENTER) {
                system("cls");
                switch (selected) {
                    case 0: CommandLineInterfaceInvoke(); return;;
                    case 1: GraphicalUserInterfaceInvoke(); return;;
                    case 2: Exit(); return;
                }
                std::cout << "\nPress any key to return to menu...";
                GetKeyPress();
            }
        }

    }

    void SetColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void CommandLineInterfaceInvoke() {
        DonutSpinningAnimation(false);
    }

    void GraphicalUserInterfaceInvoke() {
        GUI::OnGraphicalUserInterface();
    }

    void Exit() {
        TextRainbowDiagonalColor(ThankYouExitText);
        std::cout << YELLOW << ItemSaved << RESET;
        std::cout << YELLOW << ExitConfirmation << RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
    }

    std::string ChooseWhitespaceForInteractionSelect(std::string s) {
        return (std::string(59 - s.length(), ' ') + "| |\n");
    }

    void DrawMenu(const std::string choices[], int size, int selected) {
        system("cls");
        std::cout << BRIGHT_YELLOW << ChooseInterface << RESET;
        std::cout << BRIGHT_YELLOW << UnderlineChooseInterface << RESET;
        std::cout << BRIGHT_YELLOW << "  _                                                                 _ \n";
        std::cout << BRIGHT_YELLOW << " | | " << YELLOW << UpDownArrowEnterText << "           " << BRIGHT_YELLOW << "| |\n" << RESET;

        for (int i = 0; i < size; i++) {
            if (i == selected) {
                SetColor(14); // Yellow
                std::cout << " | |  ";
                SetColor(11); // Cyan
                std::cout << "> " << choices[i];
                SetColor(14); //Yellow
                std::cout << ChooseWhitespaceForInteractionSelect(choices[i]);
                SetColor(7);  // Reset ke default
            }

            else {
                SetColor(14); // Yellow
                std::cout << " | |    ";
                SetColor(7); // Default
                std::cout << choices[i];
                SetColor(14); // Yellow
                std::cout << ChooseWhitespaceForInteractionSelect(choices[i]);
                SetColor(7); // Default
            }
        }
        std::cout << BRIGHT_YELLOW << " |_|                                                               |_|\n" << RESET;
        std::cout << BRIGHT_YELLOW << UnderlineChooseInterface << RESET;

    }

} // Interface