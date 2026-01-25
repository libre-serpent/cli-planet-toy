#include "generate.h"
#include <vector>
#include <cmath>

void temp_generate(std::vector<char>& array, int x){
    int rn = rand() % 8 + 1;
    switch(rn){
        case 1:
            array[x] = 'O';
            break;
        case 2:
            array[x] = 'o';
            break;
        case 3:
            array[x] = 'o';
            break;
        default:
            array[x] = '#';
            break;
    }
}
