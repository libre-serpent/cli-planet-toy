#include "planet.h"
#include "print.h"
#include "generate.h"
#include "array_sum.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

void Planet::init_length_array(){
    arr_len.resize(diameter);
    for (int y = 0; y < diameter; ++y){
        float y_f = static_cast<float>(y) + 0.5;
        float h_f = static_cast<float>(diameter);

        float relative_height = 2 * (y_f/h_f) - 1; // this is a height in -1 ... 1
        float circumference_f = equator_length * sqrt(1-(relative_height*relative_height));
        int circumference = static_cast<int>(circumference_f + 0.5);

        arr_len[y] = circumference;
    }
}
void Planet::init_sum_array(){
    arr_sum.resize(diameter);
    for (int y = 0; y < diameter; ++y){
        arr_sum[y] = array_sum(arr_len, y);
    }
}
void Planet::init_data_array(){
    arr_data.resize(total_length);
    srand(time(0));
    /*for (int x = 0; x < total_length; ++x){
        temp_generate(arr_char, x);
    }*/
    for (int y = 0; y < diameter; ++y){
        int length = arr_len[y];
        int shift = arr_sum[y];
        double y_norm = static_cast<double>(y) / static_cast<double>(diameter);
        for (int x = 0; x < length ; ++x){
            int l = shift + x;
            double x_norm = (static_cast<double>(x) / static_cast<double>(length))*2 - 1;
            Sample s = temp_sample_xy(x_norm,y_norm);
            TerrainType t = temp_reformat_xy(s, l);
            arr_data[l] = t;
        }
    }
}
void Planet::init(int d){
    diameter = d;
    equator_length = 4*d;
    init_length_array();
    init_sum_array();
    total_length = array_sum(arr_len, diameter);
    init_data_array();
}
void Planet::render_frame(int rotation){
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
            print_char(arr_data[l].character, arr_data[l].fg_color, arr_data[l].bg_color);
        }
        std::cout << '\n';
    }
}
