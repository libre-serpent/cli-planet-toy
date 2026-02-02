#pragma once
#include <vector>

struct Sample{
    float height;
    float temperature;
    float moisture;
};

struct TerrainType{
    char character;
    int fg_color;
    int bg_color;
};

void temp_generate(std::vector<char>& array, int x);
Sample temp_sample_xy(double x_n, double y_n);
TerrainType temp_reformat_xy(Sample s, int l);
