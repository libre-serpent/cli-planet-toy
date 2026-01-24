#pragma once
#include <vector>

struct Planet{
    int diameter;
    int equator_length;
    int total_length;
    std::vector<int> arr_len;
    std::vector<int> arr_sum;
    std::vector<char> arr_char;

    void init_length_array();
    void init_sum_array();
    void init_char_array();
    void init(int d);
    void render_frame(int rotation);
};
