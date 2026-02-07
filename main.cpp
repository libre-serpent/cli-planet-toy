#include "planet.h"

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

//Constants
const float T = 18.0; // Time in seconds to complete a full rotation
const int PLANET_DIAMETER = 40; // Diameter of the planet == height of the planet in character units

//Main cycle
int main(){
    Planet planet;
    planet.init(PLANET_DIAMETER);

    float t = T / static_cast<float>(planet.equator_length);
    int frame = 0;

    while (true){
        frame = (frame + 1) % planet.equator_length;
        std::cout << "\x1B[2J\x1B[H"; //ANSI clear escape sequence
        //std::cout << frame << '\n';
        planet.render_frame(frame);
        wait_for(t);
    }

    return 0;
}
