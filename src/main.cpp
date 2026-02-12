#include "planet/planet.h"
#include "support/argparser.hpp"

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

//Functions
void wait_for(float t){
    float Tf = t * 1000;
    int Ti = static_cast<int>(Tf + 0.5);
    std::this_thread::sleep_for(std::chrono::milliseconds(Ti));
}

//Main cycle
int main(int argc, char** argv){
    auto arguments = parse_arguments(argc, argv);
    bool debug = arguments["debug"].as<bool>();
    int diameter = arguments["diameter"].as<int>();
    int timerotation = arguments["timerotation"].as<int>();

    if (arguments.count("help"))
    {
        return_help();
        return 0;
    }

    Planet planet;
    planet.init(diameter, debug);
    if (debug){
        wait_for(3);
    }

    float t = timerotation / static_cast<float>(planet.equator_length);
    int frame = 0;

    while (true){
        frame = (frame + 1) % planet.equator_length;
        std::cout << "\x1B[2J\x1B[H"; //ANSI clear escape sequence
        planet.render_sphere(frame, debug);
        wait_for(t);
    }

    return 0;
}
