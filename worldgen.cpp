#include <time.h>
#include <vector>
#include <cstdlib> //rand
#include <cmath> //floor

#include "Noisegen.hpp"
#include "worldgen.hpp"
#include "basetile.hpp"

PerlinNoise worldgen::m_noise_generator;

worldgen::worldgen() {
    srand(time(NULL));
    m_noise_generator.set(.125, .0625, 16, 8, rand()); //freq was .0625
}

world worldgen::generateWorld(int xsize, int ysize) {
    world new_world;
    std::vector<basetile> temp_y_vector;

    for(unsigned short i = 0; i < xsize; i++)                           //Tick up the main vector as long as defined
    {
        for(unsigned short j = 0; j < ysize; j++)                       //Tick up
        {
            temp_y_vector.push_back(basetile(floor(m_noise_generator.getHeight(i,j)     + m_noise_generator.getAmplitude()),         //basetile(left, top, right, bottom)
                                             floor(m_noise_generator.getHeight(i+1,j)   + m_noise_generator.getAmplitude()),
                                             floor(m_noise_generator.getHeight(i+1,j+1) + m_noise_generator.getAmplitude()),
                                             floor(m_noise_generator.getHeight(i,j+1)   + m_noise_generator.getAmplitude())));
        }
        new_world.m_basetile_data.push_back(temp_y_vector);
        temp_y_vector.clear();
    }

    return new_world;
}
