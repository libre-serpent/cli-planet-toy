#include "print.h"
#include <iostream>
#include <string>

const std::string color_r = "\033[0m";
std::string color = "\033[38;5;255m";
const std::string ansi_white = "\033[38;5;255m";
const std::string ansi_grey = "\033[38;5;250m";
const std::string ansi_dgrey = "\033[38;5;240m";

void print_colored(std::string color, char c){
    std::cout << color << c << color_r;
}

void print_char(char c){
    switch(c){
        case 'O':
            print_colored(ansi_dgrey, c);
            break;
        case 'o':
            print_colored(ansi_grey, c);
            break;
        case '#':
            print_colored(ansi_white, c);
            break;
        default:
            print_colored(ansi_white, c);
            break;
    }
}
