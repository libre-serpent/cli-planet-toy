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
const float A = 0.0;  // Axial tilt (difference between rotation axis and planet axis)
const int PLANET_D = 40; // Diameter of the planet
const int PLANET_W = 4*PLANET_D; // Width of the planet map in characters
const int PLANET_H = PLANET_D; // Height of the planet map in characters
const int PLANET_L = PLANET_H*PLANET_W; // Planet total length

const std::string color_r = "\033[0m";
std::string color = "\033[38;5;255m";
const std::string ansi_white = "\033[38;5;255m";
const std::string ansi_grey = "\033[38;5;250m";
const std::string ansi_dgrey = "\033[38;5;240m";

//Functions
void temp_generate(char buffer[PLANET_L], int x){
    int rn = rand() % 8 + 1;
    switch(rn){
        case 1:
            buffer[x] = 'O';
            break;
        case 2:
            buffer[x] = 'o';
            break;
        case 3:
            buffer[x] = 'o';
            break;
        default:
            buffer[x] = '#';
            break;
    }
}

void lat_generate(char buffer[PLANET_L], int x){
    if (x % PLANET_W == 0 ||
        x % PLANET_W == PLANET_W/8 ||
        x % PLANET_W == 2*PLANET_W/8 ||
        x % PLANET_W == 3*PLANET_W/8 ||
        x % PLANET_W == 4*PLANET_W/8 ||
        x % PLANET_W == 5*PLANET_W/8 ||
        x % PLANET_W == 6*PLANET_W/8 ||
        x % PLANET_W == 7*PLANET_W/8 ||
        x % PLANET_W == 8*PLANET_W/8){
        buffer[x] = '|';
    }
    else if (x % PLANET_W == 0 + 1 ||
        x % PLANET_W == PLANET_W/8 + 1 ||
        x % PLANET_W == 2*PLANET_W/8 + 1 ||
        x % PLANET_W == 3*PLANET_W/8 + 1 ||
        x % PLANET_W == 4*PLANET_W/8 + 1 ||
        x % PLANET_W == 5*PLANET_W/8 + 1 ||
        x % PLANET_W == 6*PLANET_W/8 + 1 ||
        x % PLANET_W == 7*PLANET_W/8 + 1){
        buffer[x] = '|';
        }
    else{
        buffer[x] = '#';
    }
}

void create_planet(char buffer[PLANET_L]){
    srand(time(0));
    for (int x = 0; x < PLANET_L; ++x){
        temp_generate(buffer, x);
    }
}

void render_rect(char buffer[PLANET_L]){
    for (int x = 1; x < PLANET_L+1; ++x){
        std::cout << buffer[x-1];
        if (x % PLANET_W == 0){
            std::cout << '\n';
        }
    }
} // lord forgive me for this jank.... :o

void render_circ(char buffer[PLANET_L], int start){
    char circ_buffer[PLANET_L/2];

    for (int x = 0; x < PLANET_L/2; ++x){
        circ_buffer[x] = '.';
    }

    for (int y = 0; y < PLANET_H; ++y){
        float y_f = static_cast<float>(y)+0.5;
        float h_f = static_cast<float>(PLANET_H);
        float w_f = static_cast<float>(PLANET_W);

        float height_relative = 2*(y_f/h_f) - 1; // this is a height in -1...1

        float segment_length_f = w_f/2 * cos(asin(height_relative));
        int segment_length = static_cast<int>(segment_length_f); //this is the length of the grabbed segment

        int rect_shift = (PLANET_W - segment_length)/2; // this is how much we have to offset rect and circ map respectively
        int circ_shift = (PLANET_W/2 - segment_length)/2;// to account for circularity

        for (int x = 0; x < segment_length; ++x){
            //float x_f = static_cast<float>(x)+0.5;
            //float width_relative = 2*(x_f/segment_length_f) - 1; // ranges -1...1
            //float x_relative = ((sin(width_relative * (M_PI/2))) + 1) * 0.5;   // ranges 0...1
            //int x_warped = static_cast<int>(x_relative * (PLANET_W/2) + 0.5);

            int rect_x = (start + x + rect_shift) % (PLANET_W);

            int rect_l = rect_x + y*PLANET_W;
            int circ_l = (circ_shift+x) % (PLANET_W/2) + y*(PLANET_W/2);

            circ_buffer[circ_l] = buffer[rect_l];
        }
    }

    for (int x = 1; x < PLANET_L/2 + 1; ++x){
        switch(circ_buffer[x-1]){
            case '#':
                color = ansi_white;
                break;
            case 'o':
                color = ansi_grey;
                break;
            case 'O':
                color = ansi_dgrey;
                break;
            default:
                color = ansi_white;
                break;
        }
        std::cout << color << circ_buffer[x-1] << color_r;
        if (x % (PLANET_W / 2) == 0){
            std::cout << '\n';
        }
    }
} // lord forgive me for this jank :o

void wait_for(float t){
    float Tf = t * 1000;
    int Ti = static_cast<int>(Tf + 0.5);
    std::this_thread::sleep_for(std::chrono::milliseconds(Ti));
}

//Main cycle
int main(){
    char buffer[PLANET_L];

    create_planet(buffer);

    int loop = 0;
    while (true){
        loop++;
        if (loop == (PLANET_W)){
            loop = 0;
        }
        std::cout << "\x1B[2J\x1B[H";
        //render_rect(buffer);
        render_circ(buffer, loop);
        wait_for(0.1);
    }

    return 0;
}
