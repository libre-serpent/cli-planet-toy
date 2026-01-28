#include "noise.h"
#include <iostream>

const int seed = 123654;

double range = 255.0 - 232.0;

int main(){
    srand(time(0));
    int seed = rand() % 888888 + 111111;
    std::cout << seed << '\n';
    for (int i = 0; i < 40; ++i){
        double x = static_cast<double>(i) / 40 + 0.5;
        double n = noise(x, seed);
        double c1 = (n + 1)/2;
        double c2 = c1 * range + 232.0;
        int color = static_cast<int>(c2 + 0.5);
        std::cout << "\033[38;5;" << color << 'm' << 'x' << "\033[0m";
    }
    std::cout << '\n';
    return 0;
}
