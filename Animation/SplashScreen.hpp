//
// Created by Acer on 08/06/2025.
//

#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP
#include "../Interface/CLI/CommandLineInterface.h"
#include "SplashScreenText.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

inline void showLoadingBar(int total = 100, int delayMs = 15) {
    const int barWidth = 50;  // Panjang loading bar

    for (int i = 0; i <= total; ++i) {
        std::cout << "\rLoading [";

        int pos = barWidth * i / total;

        // cetak bar
        for (int j = 0; j < barWidth; ++j) {
            if (j < pos) std::cout << "=";
            else if (j == pos) std::cout << ">";
            else std::cout << " ";
        }

        // cetak percentase
        std::cout << "] " << i << "%";
        std::cout.flush();

        // Tunggu dulu sebelum lanjut
        std::this_thread::sleep_for(std::chrono::milliseconds((rand() % 5)));
    }

    std::cout << "\nDone!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}


inline void StartSplashScreen() {
    std::vector<std::string> frames = AnimationFrame;
    for (const auto& frame : frames) {
        std::cout << "\033[2J\033[1;1H";
        std::cout << frame;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // delay antara frames
    }
    showLoadingBar();
    CLI::OnCommandLineInterface();
}

#endif //SPLASHSCREEN_HPP
