#pragma once
#include <iostream>
#include <string>

const std::string RESET = "\033[0m";
const std::string ESC = "\033[";

inline void print_char(char c, int fg_color,int bg_color){
    std::cout << ESC << "38;5;" << fg_color << ";48;5;" << bg_color << 'm' << c << RESET;
}
