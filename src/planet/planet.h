#pragma once
#include "generate/generate.h"
#include <vector>

struct Planet{
    int diameter;
    int equator_length;
    int total_length;
    std::vector<int> arr_len; //n-th member is the circumference in characters of the n-th slice of the planet
    std::vector<int> arr_sum; //n-th member is the sum of all 0...n members of arr_len
    std::vector<TerrainType> arr_data; //contains TerrainType objects consisting of a character, and two color codes 0-255

    void init_length_array(bool debug=false);
    void init_sum_array(bool debug=false);
    void init_data_array(bool debug=false);
    void init(int d, bool debug=false);
    void render_sphere(int rotation=0, bool debug=false);
};
