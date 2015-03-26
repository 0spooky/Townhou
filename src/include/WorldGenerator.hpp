#ifndef WORLDGEN_HPP_INCLUDED
#define WORLDGEN_HPP_INCLUDED

#include "NoiseGenerator.hpp"
#include "World.hpp"

class WorldGenerator {

    //The noise generator used to randomize the map
    static PerlinNoise m_noise_generator;

public:
    //Constructor
    WorldGenerator();

    //A function to generate a new world
    World generateWorld(int xsize, int ysize);

};

#endif // WORLDGEN_HPP_INCLUDED
