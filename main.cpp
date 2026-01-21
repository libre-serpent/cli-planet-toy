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
const float T = 10.0; // Time in seconds to complete a full rotation
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

int array_sum(int array[], int array_length){
    int sum = 0;
    for (int x = 0; x < array_length; ++x){
        sum += array[x];
    }
    return sum;
}

void init_length_array(int array[PLANET_D], int planet_height, int equator_width){
    for (int y = 0; y < PLANET_D; ++y){
        float y_f = static_cast<float>(y) + 0.5;
        float h_f = static_cast<float>(planet_height);

        float relative_height = 2 * (y_f/h_f) - 1; // this is a height in -1 ... 1
        float circumference_f = equator_width * cos(asin(relative_height));
        int circumference = static_cast<int>(circumference_f + 0.5);

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

void init_char_array(char array[], int planet_length){
    srand(time(0));
    for (int x = 0; x < planet_length; ++x){
        temp_generate(array, x);
    }
}

void render_frame(int array_leng[], char array_char[], int height, int equator_width, int shift){
    for (int y = 0; y < height; ++y){
        int segment_length = array_leng[y]/2;
        for (int x = 0; x < (equator_width/2 - segment_length)/2 ; ++x){
            std::cout << ' ';
        }
        for (int x = 0; x < segment_length; ++x){
            int unconditional_shift = array_sum(array_leng,y);
            float segment_length_f = static_cast<float>(segment_length);
            float equator_width_f = static_cast<float>(equator_width);
            float shift_f = static_cast<float>(shift);
            float temporal_shift_f = shift_f * (2*segment_length_f / equator_width_f);
            int temporal_shift = static_cast<int>(temporal_shift_f + 0.5);
            int l = unconditional_shift + (temporal_shift + x) % array_leng[y]/2;
            print_char(array_char[l]);
        }// for shift = max segment_length = max, for true shift
        std::cout << '\n';
    }
}

//Main cycle
int main(){
    float t = T / static_cast<float>(equator_width);

    int array_leng[PLANET_D];
    init_length_array(array_leng, PLANET_D, equator_width);

    int planet_length = array_sum(array_leng, PLANET_D);

    char array_char[planet_length];
    init_char_array(array_char, planet_length);

    int frame = 0;
    while (true){
        frame++;
        if (frame == (equator_width)){
            frame = 0;
        }
        std::cout << "\x1B[2J\x1B[H";
        std::cout << frame << '\n';
        render_frame(array_leng, array_char, PLANET_D, equator_width, frame);
        wait_for(t);
    }

    return 0;
}
