#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>
#include <vector>

//Constants
const float T = 10.0; // Time in seconds to complete a full rotation
const int PLANET_DIAMETER = 20; // Diameter of the planet == height of the planet in character units

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

int array_sum(std::vector<int>& array, int array_length){
    int sum = 0;
    for (int x = 0; x < array_length; ++x){
        sum += array[x];
    }
    return sum;
}

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

//Data type definitions
struct Planet{
    int diameter;
    int equator_length;
    int total_length;
    std::vector<int> arr_len;
    std::vector<int> arr_sum;
    std::vector<char> arr_char;

    void init_length_array(){
        arr_len.resize(diameter);
        for (int y = 0; y < diameter; ++y){
            float y_f = static_cast<float>(y) + 0.5;
            float h_f = static_cast<float>(diameter);

            float relative_height = 2 * (y_f/h_f) - 1; // this is a height in -1 ... 1
            float circumference_f = equator_length * cos(asin(relative_height));
            int circumference = static_cast<int>(circumference_f + 0.5);

            arr_len[y] = circumference;
        }
    }
    void init_sum_array(){
        arr_sum.resize(diameter);
        for (int y = 0; y < diameter; ++y){
            arr_sum[y] = array_sum(arr_len, y);
        }
    }
    void init_char_array(){
        arr_char.resize(total_length);
        srand(time(0));
        for (int x = 0; x < total_length; ++x){
            temp_generate(arr_char, x);
        }
    }
    void init(int d){
        diameter = d;
        equator_length = 4*d;
        init_length_array();
        init_sum_array();
        total_length = array_sum(arr_len, diameter);
        init_char_array();
    }
    void render_frame(int rotation){
        for (int y = 0; y < diameter; ++y){
            int segment_length = arr_len[y]/2;
            int unconditional_shift = arr_sum[y];
            for (int x = 0; x < (equator_length/2 - segment_length)/2 ; ++x){
                std::cout << ' ';
            }
            for (int x = 0; x < segment_length; ++x){
                float segment_length_f = static_cast<float>(segment_length);
                float equator_length_f = static_cast<float>(equator_length);
                float shift_f = static_cast<float>(rotation);
                float temporal_shift_f = shift_f * (2*segment_length_f / equator_length_f);
                int temporal_shift = static_cast<int>(temporal_shift_f + 0.5);
                int l = unconditional_shift + (temporal_shift + x) % arr_len[y]/2;
                print_char(arr_char[l]);
            }
            std::cout << '\n';
        }
    }
};

//Main cycle
int main(){
    Planet planet;
    planet.init(PLANET_DIAMETER);

    float t = T / static_cast<float>(planet.equator_length);
    int frame = 0;

    while (true){
        frame++;
        if (frame == (planet.equator_length)){
            frame = 0;
        }
        std::cout << "\x1B[2J\x1B[H";
        std::cout << frame << '\n';
        planet.render_frame(frame);
        wait_for(t);
    }

    return 0;
}
