#include "generate.h"
#include "noise.h"
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>

//temp defintion of terrain types

const TerrainType tt_ice{
    '*',
    195,
    153
};

const TerrainType tt_tundra{
    '#',
    195,
    153
};

const TerrainType tt_water{
    '~',
    255,
    39
};

const TerrainType tt_sand{
    '#',
    229,
    223
};

const TerrainType tt_grass{
    '#',
    112,
    100
};

const TerrainType tt_low_mountain{
    '.',
    248,
    245
};

const TerrainType tt_medium_mountain{
    '\"',
    252,
    245
};

const TerrainType tt_high_mountain{
    '^',
    231,
    245
};

//eof

double pi = 3.14159;

Sample temp_sample_xy(double x_n, double y_n,
                      int seed_h_lat, int seed_h_lon,
                      int seed_m_lat, int seed_m_lon,
                      int seed_t_lat, int seed_t_lon){//x -1...1 y 0...1

    std::cout << "Height seed is: " << seed_h_lat << seed_h_lon << '\n';
    std::cout << "Moisture seed is: " << seed_m_lat << seed_m_lon << '\n';
    std::cout << "Temperature seed is: " << seed_t_lat << seed_t_lon << '\n';

    double lat = y_n * 2.0 * pi;
    double lon = x_n * 2.0 * pi;

    //temporary? sample parameters
    double height = (noise(lat, seed_h_lat) * 0.3 + noise(lon, seed_h_lon) * 0.7);
    double moisture = (noise(lat, seed_h_lat) * 0.25 + noise(lon, seed_h_lon) * 0.25 + 0.5);
    double temperature = (-2.0 * (std::fabs(y_n * 2.0 - 1.0)-0.5)) * 0.5 + (noise(lat, seed_t_lat) * 0.2 + noise(lon, seed_t_lon) * 0.3);
    //featuring magical numbers :) ^ that whole ordeal creates a temperature field -1...0.5...-1 where y_n = 0...1

    Sample s;
    s.height = height;
    s.moisture = moisture;
    s.temperature = temperature;

    return s;
}

TerrainType temp_reformat_xy(Sample s, int l){//basically just solver for the sample
    double height = s.height;
    double moisture = s.moisture;
    double temperature = s.temperature;

    std::cout << l << ':' << height << '/' << moisture << '/' << temperature << '\n';
    //wooo debug codeeeeee

    if (height < 0){ //below sea level
        if (temperature < -0.2){
            return tt_ice;
        }
        return tt_water;
    }
    else if (height < 0.1 && temperature > 0.1){ //beach
        return tt_sand;
    }
    else if (height > 0.4){
        return tt_high_mountain;
    }
    else if (height > 0.3){
        return tt_medium_mountain;
    }
    else if (height > 0.25){
        return tt_low_mountain;
    }
    else if (temperature < -0.1){ // frozen tundra
        return tt_tundra;
    }
    else {
        return tt_grass;
    }
}
