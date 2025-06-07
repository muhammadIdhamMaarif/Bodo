//
// Created by Acer on 07/06/2025.
//

#ifndef COLORLIST_H
#define COLORLIST_H
#include <string>
#include <vector>

namespace Color {

    // ANSI color codes
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string CYAN = "\033[36m";
    const std::string GREEN = "\033[32m";
    const std::string CYAN_VIBRANT = "\033[38;5;51m";
    const std::string GREEN_VIBRANT = "\033[38;5;34m";
    const std::string BOX_COLOR = "\033[34m";
    const std::string YELLOW = "\033[38;5;226m";
    const std::string TEAL = "\033[38;5;37m";
    const std::string GOLD = "\033[38;5;178m";
    const std::string PURPLE = "\033[38;5;177m";
    const std::string RED = "\033[38;5;197m";

    const std::vector<int> SeamlessRainbowColor_15_Colors = {
        196, // Red       (RGB ~ 255, 0, 0)
        202, // Orange    (RGB ~ 255, 95, 0)
        214, // Gold      (RGB ~ 255, 175, 0)
        226, // Yellow    (RGB ~ 255, 255, 0)
        190, // LGreen    (RGB ~ 175, 255, 95)
        46,  // Green     (RGB ~ 0, 255, 0)
        49,  // Turquoise (RGB ~ 0, 175, 175)
        51,  // Cyan      (RGB ~ 0, 255, 255)
        33,  // Sky Blue  (RGB ~ 0, 95, 255)
        21,  // Blue      (RGB ~ 0, 0, 255)
        57,  // Indigo    (RGB ~ 95, 0, 255)
        93,  // Purple    (RGB ~ 175, 0, 255)
        127, // Magenta   (RGB ~ 255, 0, 255)
        165, // Pink      (RGB ~ 255, 95, 175)
        201  // Violet    (RGB ~ 255, 0, 175)
    };

    inline std::string setColor(int code) {
        return "\033[38;5;" + std::to_string(code) + "m";
    }

} // Color

#endif //COLORLIST_H
