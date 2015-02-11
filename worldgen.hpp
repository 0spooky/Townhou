#ifndef WORLDGEN_HPP_INCLUDED
#define WORLDGEN_HPP_INCLUDED

#include "Noisegen.hpp"
#include "world.hpp"

class worldgen {

    static PerlinNoise noisegenerator;

public:
    worldgen();
    world generateworld(int xsize, int ysize);

};

#endif // WORLDGEN_HPP_INCLUDED
