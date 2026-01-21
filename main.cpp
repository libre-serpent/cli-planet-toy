#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>

//Data type definitions
struct Vec2{
    float x;
    float y;
};

//Constants
const float T = 10.0; // Time in seconds to complete a full rotation3.14159
const float A = 0.0;  // Axial tilt (difference between rotation axis and planet axis)
const int PLANET_D = 20; // Diameter of the planet == height of the planet in character units
const int equator_width = static_cast<int>((PLANET_D * 4) + 0.5); // Width of the equator in chars (yes pi = 4)

const std::string color_r = "\033[0m";
std::string color = "\033[38;5;255m";
const std::string ansi_white = "\033[38;5;255m";
const std::string ansi_grey = "\033[38;5;250m";
const std::string ansi_dgrey = "\033[38;5;240m";

//Functions
void wait_for(float t){
    float Tf = t * 1000;
    int Ti = static_cast<int>(Tf + 0.5);
    std::this_thread::sleep_for(std::chrono::milliseconds(Ti));
}

void init_length_array(int array[PLANET_D], int planet_height, int equator_width){
    for (int y = 0; y < PLANET_D; ++y){
        float y_f = static_cast<float>(y) + 0.5;
        float h_f = static_cast<float>(planet_height);

        float relative_height = 2 * (y_f/h_f) - 1; // this is a height in -1 ... 1
        float circumference_f = equator_width * cos(asin(relative_height));
        int circumference = static_cast<int>(circumference_f+0.5);

        array[y] = circumference;
    }
}

void temp_generate(char array[], int x){
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

void create_planet(char buffer[], int planet_length){
    srand(time(0));
    for (int x = 0; x < planet_length; ++x){
        temp_generate(buffer, x);
    }
}

//Main cycle
int main(){
    int array_leng[PLANET_D];
    init_length_array(array_leng, PLANET_D, equator_width);

    //std::cout << "\x1B[2J\x1B[H";
    //render_function_of_some_kind(array_char,array_leng,loop);
    //wait_for(0.1);

    return 0;
}
