//
// Created by Acer on 07/06/2025.
//

#ifndef TEXTINSPECTOR_H
#define TEXTINSPECTOR_H
#include <iostream>

namespace Text {

    const std::string BodoHeader = R"(
  ____            _
 | __ )  ___   __| | ___
 |  _ \ / _ \ / _` |/ _ \
 | |_) | (_) | (_| | (_) |
 |____/ \___/ \__,_|\___/
  _____ _____ _____ _____ _____ _____ _____ _____
 |_____|_____|_____|_____|_____|_____|_____|_____|
  ____              _    _               ____        _    _
 | __ )  ___   ___ | | _(_)_ __   __ _  |  _ \  ___ | | _| |_ ___ _ __
 |  _ \ / _ \ / _ \| |/ / | '_ \ / _` | | | | |/ _ \| |/ / __/ _ \ '__|
 | |_) | (_) | (_) |   <| | | | | (_| | | |_| | (_) |   <| ||  __/ |
 |____/ \___/ \___/|_|\_\_|_| |_|\__, | |____/ \___/|_|\_\\__\___|_|
                                 |___/
)";

    inline void PrintCharWithLength(char c, int length) { while (length--) { std::cout << c; } std::cout << '\n'; }

    const std::string NamaKelompok = R"(
=================================================================
| TUGAS AKHIR ALGORITMA DAN DATA STRUKTUR                       |
| Nama Kelompok :                                               |
|    1. Muhammad Idham Ma'arif          (245150300111024)       |
|    2. Muhammad Varrel diandra         (245150307111029)       |
|    3. Muhammad Rafi Alfarel K         (245150307111018)       |
|    4. Rafi Ibnushaleh                 (245150301111012)       |
|    5. Afif Rafi Ardiyanto             (245150307111026)       |
|                                                               |
=================================================================
)";


} // Text

#endif //TEXTINSPECTOR_H
