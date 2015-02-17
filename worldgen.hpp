#ifndef WORLDGEN_HPP_INCLUDED
#define WORLDGEN_HPP_INCLUDED

#include "Noisegen.hpp"
#include "world.hpp"

class worldgen {

    //The height displacement between two vertices when one is higher
    static const int HEIGHT_INCREMENTS = 8;

    //The noise generator used to randomize the map
    static PerlinNoise noisegenerator;

public:
    //Constructor
    worldgen();

    //A function to generate a new world
    world generateworld(int xsize, int ysize);

};

#endif // WORLDGEN_HPP_INCLUDED
