#include "planet/planet.h"
#include "generate/generate.h"
#include "support/print.hpp"
#include "support/array_sum.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

void Planet::init_length_array(bool debug){
    arr_len.resize(diameter);
    for (int y = 0; y < diameter; ++y){
        float y_f = static_cast<float>(y) + 0.5;
        float h_f = static_cast<float>(diameter);

        float relative_height = 2 * (y_f/h_f) - 1; // this is a height in -1 ... 1
        float circumference_f = equator_length * sqrt(1-(relative_height*relative_height));
        //    ^ of y-th slice of the planet, calculated as max circumference * trigonometric warping
        int circumference = static_cast<int>(circumference_f + 0.5);

        arr_len[y] = circumference;

        if (debug){
            std::cout << "Initialised array of planet layer lengths successfully." << '\n';
        }
    }
}
void Planet::init_sum_array(bool debug){
    arr_sum.resize(diameter);
    for (int y = 0; y < diameter; ++y){
        arr_sum[y] = array_sum(arr_len, y);
        //  ^ of all array members up to but not including y-th
        if (debug){
            std::cout << "Initialised array of layer prefixes successfully." << '\n';
        }
    }
}
void Planet::init_data_array(bool debug){
    arr_data.resize(total_length);
    srand(time(0)); // seeding the random generator

    int seed_h_lat = rand() % 888888 + 111111; //getting all the seeds
    int seed_h_lon = rand() % 888888 + 111111;
    int seed_m_lat = rand() % 888888 + 111111;
    int seed_m_lon = rand() % 888888 + 111111;
    int seed_t_lat = rand() % 888888 + 111111;
    int seed_t_lon = rand() % 888888 + 111111;

    if (debug){
        std::cout << "Generator seeded successfully." << '\n';
    }

    for (int y = 0; y < diameter; ++y){ // for every slice of the planet
        int length = arr_len[y]; //length of the current slice
        int shift = arr_sum[y];  //sum of all lengths before the current slice
        double y_norm = static_cast<double>(y) / static_cast<double>(diameter);
        for (int x = 0; x < length ; ++x){
            int l = shift + x; // character being currently generated
            double x_norm = (static_cast<double>(x) / static_cast<double>(length))*2 - 1;
            //          ^ normalized to -1...1 to wrap in trigonometric space
            Sample s = temp_sample_xy(x_norm,y_norm,
                                      seed_h_lat,seed_h_lon,
                                      seed_m_lat,seed_m_lon,
                                      seed_t_lat,seed_t_lon);
            TerrainType t = temp_reformat_xy(s, l);
            arr_data[l] = t;
        }
        if (debug){
            std::cout << "Generated layer " << y << " of " << diameter << " successfully." << '\n';
        }
    }
    if (debug){
        std::cout << "Planet generation is successful." << '\n';
    }
}
void Planet::init(int d, bool debug){
    diameter = d;
    equator_length = 4*d; //yes, pi is equal to 4 here. it's ok.
    if (debug){
        std::cout << "Initialising..." << '\n';
    }
    init_length_array(debug);
    init_sum_array(debug);
    total_length = array_sum(arr_len, diameter);
    init_data_array(debug);
    if (debug){
        std::cout << "Planet initialised successfully." << '\n';
    }
}
void Planet::render_sphere(int rotation, bool debug){
    if (debug){
        std::cout << "Frame " << rotation << '\n';
    }
    for (int y = 0; y < diameter; ++y){
        int segment_length = arr_len[y]/2; // length of the slice to be rendered
        int unconditional_shift = arr_sum[y];
        //  ^ for the 1d data array; this is how far you have to move to get to the 'x' of layer y
        for (int x = 0; x < (equator_length/2 - segment_length)/2 ; ++x){
            std::cout << ' ';
        }// ^ writes empty space to the left of the rendered slice
        for (int x = 0; x < segment_length; ++x){
            float segment_length_f = static_cast<float>(segment_length);
            float equator_length_f = static_cast<float>(equator_length);
            float rotation_f = static_cast<float>(rotation);
            float warped_rotation_f = rotation_f * (2*segment_length_f / equator_length_f);
            // ^ here, rotation is 0...equator_length. this magical equation converts it to 0...2*segment length.
            //                                         2*seglen is the full length of the slice to be rendered.
            //                                         why not just do arr_len[y]? bc we're working with floats
            //                                         and adding another value or a bulky expression would be uglier ig
            // this makes every slice rotate on its own
            int warped_rotation = static_cast<int>(warped_rotation_f + 0.5);
            int l = unconditional_shift + ((warped_rotation + x) % arr_len[y])/2;
            //     ^ this whole expression returns how far we are in the data array,
            //       % wraps the iterator w_r+x in case of overflows, the whole thing
            //       is divided by 2 because arr_len[y] is the full circumference of
            //       the planet at y, but we only need to render the half facing us (hence 1/2)
            print_char(arr_data[l].character, arr_data[l].fg_color, arr_data[l].bg_color);
        }
        std::cout << '\n';
    }
}
