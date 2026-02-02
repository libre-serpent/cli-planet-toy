#include "generate.h"
#include "noise.h"
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>

//temp defintion of terrain types

TerrainType tt_ice{
    '*',
    195,
    117
};

TerrainType tt_water{
    '~',
    255,
    39
};

TerrainType tt_sand{
    '#',
    229,
    223
};

TerrainType tt_grass{
    '#',
    112,
    100
};

TerrainType tt_low_mountain{
    '.',
    248,
    245
};

TerrainType tt_medium_mountain{
    '\"',
    252,
    245
};

TerrainType tt_high_mountain{
    '^',
    231,
    245
};

//eof

double pi = 3.14159;

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

Sample temp_sample_xy(double x_n, double y_n){//x -1...1 y 0...1
    srand(time(0));
    int seed_heig_lat = rand() % 888888 + 111111;
    int seed_heig_lon = rand() % 888888 + 111111;
    int seed_mois_lat = rand() % 888888 + 111111;
    int seed_mois_lon = rand() % 888888 + 111111;
    int seed_temp_lat = rand() % 888888 + 111111;
    int seed_temp_lon = rand() % 888888 + 111111;

    std::cout << "Height seed is: " << seed_heig_lat << seed_heig_lon << '\n';
    std::cout << "Moisture seed is: " << seed_mois_lat << seed_mois_lon << '\n';
    std::cout << "Temperature seed is: " << seed_temp_lat << seed_temp_lon << '\n';

    double lat = y_n * 2.0 * pi;
    double lon = x_n * 2.0 * pi;

    double height = (noise(lat, seed_heig_lat) * 0.3 + noise(lon, seed_heig_lon) * 0.7);
    double moisture = (noise(lat, seed_heig_lat) * 0.25 + noise(lon, seed_heig_lon) * 0.25 + 0.5);
    double temperature = (-2.0 * (std::fabs(y_n * 2.0 - 1.0)-0.5)) * 0.5 + (noise(lat, seed_temp_lat) * 0.2 + noise(lon, seed_temp_lon) * 0.3);

    Sample s;
    s.height = height;
    s.moisture = moisture;
    s.temperature = temperature;

    return s;
}

TerrainType temp_reformat_xy(Sample s, int l){
    double height = s.height;
    double moisture = s.moisture;
    double temperature = s.temperature;

    std::cout << l << ':' << height << '/' << moisture << '/' << temperature << '\n';

    if (height < 0){ //below sea level
        if (temperature < -0.1){
            return tt_ice;
        }
        return tt_water;
    }
    else if (height < 0.1 && temperature > 0.1){ //beach
        return tt_sand;
    }
    else if (temperature < -0.3){ // frozen tundra
        return tt_ice;
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
    else {
        return tt_grass;
    }
}
