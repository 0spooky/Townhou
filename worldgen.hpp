#ifndef WORLDGEN_HPP_INCLUDED
#define WORLDGEN_HPP_INCLUDED

#include "Noisegen.hpp"
#include "world.hpp"

class worldgen {

    //The noise generator used to randomize the map
    static PerlinNoise noisegenerator;

public:
    //Constructor
    worldgen();

    //A function to generate a new world
    world generateworld(int xsize, int ysize);

};

#endif // WORLDGEN_HPP_INCLUDED
