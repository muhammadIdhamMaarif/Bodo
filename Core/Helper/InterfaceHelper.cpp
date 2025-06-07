//
// Created by Acer on 07/06/2025.
//

#include "InterfaceHelper.h"

namespace Interface {

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

    void DrawHeader() {
        const std::string art = BodoHeader;

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

    void PrintNamaKelompok() {
        std::cout << YELLOW << "=================================================================" << RESET << "\n";
        std::cout << YELLOW << "| " << YELLOW << "TUGAS AKHIR ALGORITMA DAN DATA STRUKTUR                       " << YELLOW << "|\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "Nama Kelompok :" << std::string(47, ' ') << YELLOW << "|\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "   1. " << GREEN_VIBRANT << "Muhammad Idham Ma'arif" << "          " << RED << "(245150300111024)" << YELLOW << "       |\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "   2. " << GREEN_VIBRANT << "Muhammad Varrel diandra" << "         " << RED << "(245150307111029)" << YELLOW << "       |\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "   3. " << GREEN_VIBRANT << "Muhammad Rafi Alfarel K" << "         " << RED << "(245150307111018)" << YELLOW << "       |\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "   4. " << GREEN_VIBRANT << "Rafi Ibnushaleh" << "                 " << RED << "(245150301111012)" << YELLOW << "       |\n";
        std::cout << YELLOW << "| " << CYAN_VIBRANT << "   5. " << GREEN_VIBRANT << "Afif Rafi Ardiyanto" << "             " << RED << "(245150307111026)" << YELLOW << "       |\n";
        std::cout << YELLOW << "|                                                               |\n";
        std::cout << YELLOW << "=================================================================" << RESET << "\n";

    }

} // Interface