#include "external/cxxopts.hpp"
#include <iostream>
#pragma once

auto parse_arguments(int argc,char** argv){
    cxxopts::Options options("Planet", "Generates a planet right in your cli!");

    options.add_options()
    ("d,debug", "Enable debug outputs", cxxopts::value<bool>()->default_value("false"))
    ("D,diameter", "Planet diameter in characters", cxxopts::value<int>()->default_value("40"))
    ("T,timerotation", "Time for a full rotation in seconds", cxxopts::value<int>()->default_value("20"))
    ("terrain", "Terrain type XML", cxxopts::value<std::string>())
    ("samples", "Sampling rules XML", cxxopts::value<std::string>())
    ("h,help", "Print usage")
    ;

    return options.parse(argc, argv);
}
void return_help(){
    cxxopts::Options options("Planet", "Generates a planet right in your cli!");

    options.add_options()
    ("d,debug", "Enable debug outputs", cxxopts::value<bool>()->default_value("false"))
    ("D,diameter", "Planet diameter in characters", cxxopts::value<int>()->default_value("40"))
    ("T,timerotation", "Time for a full rotation in seconds", cxxopts::value<int>()->default_value("20"))
    ("terrain", "Terrain type XML", cxxopts::value<std::string>())
    ("samples", "Sampling rules XML", cxxopts::value<std::string>())
    ("h,help", "Print usage")
    ;

    std::cout << options.help() << '\n';
}
