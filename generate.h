#pragma once
#include <vector>

struct Sample{
    float height;
    float temperature;
    float moisture;
};

void temp_generate(std::vector<char>& array, int x);
Sample temp_sample_xy(double x_n, double y_n);
void temp_reformat_xy(std::vector<char>& array, Sample s, int l);
