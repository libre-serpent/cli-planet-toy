#include "noise.h"
#include <cmath>
#include <iostream>

const double pi = 3.14159;

double noise(double x_rad, int seed, int octaves){//assuming x = 0...1
    double seed_i = std::fmod(static_cast<double>(seed) / 1000000,1);
    double seed_j = std::fmod(static_cast<double>(seed) / 10000,1);
    double seed_k = std::fmod(static_cast<double>(seed) / 100,1);
    double seed_ws = std::fmod(static_cast<double>(seed) / 100000, 1);
    double seed_wc = std::fmod(static_cast<double>(seed) / 1000, 1);

    double amplitude = 1.0;
    double normalize = 0.0;
    double value = 0.0;
    double frequency = 1.0;

    double phasesin = seed_i * 4.0 * pi;
    double phasecos = seed_j * 4.0 * pi;

    double ampsin = seed_k;
    double ampcos = 1 - ampsin;

    for (int i = 0; i < octaves; ++i){
        double wavesin = (sin(seed_ws * 4.0 * pi) * 0.25) + 0.75;
        double wavecos = (sin(seed_wc * 4.0 * pi) * 0.25) + 0.75;

        value += sin(x_rad * frequency + phasesin) * wavesin * ampsin * amplitude + cos(x_rad * frequency + phasecos) * wavecos * ampcos * amplitude;

        normalize += amplitude;
        amplitude *= 0.5;
        frequency *= 2.0;

        seed_ws = std::fmod((seed_ws + pi * pi),1);
        seed_wc = std::fmod((seed_wc + pi * pi),1);

        phasesin = std::fmod((phasesin + seed_j*pi),2.0*pi);
        phasecos = std::fmod((phasecos + seed_k*pi),2.0*pi);
    }

    return value / normalize;
}
