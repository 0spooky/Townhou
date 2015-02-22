#include <cmath> //floor
#include <cstdlib> //rand
#include <time.h>
#include <vector>

#include "Basetile.hpp"
#include "NoiseGenerator.hpp"
#include "WorldGenerator.hpp"

PerlinNoise WorldGenerator::m_noise_generator;

WorldGenerator::WorldGenerator() {
    srand(time(NULL));
    m_noise_generator.set(.125, .0625, 16, 8, rand()); //freq was .0625
}

World WorldGenerator::generateWorld(int xsize, int ysize) {
    World new_world;
    std::vector<Basetile> temp_y_vector;

    for(unsigned short i = 0; i < xsize; i++)                           //Tick up the main vector as long as defined
    {
        for(unsigned short j = 0; j < ysize; j++)                       //Tick up
        {
            temp_y_vector.push_back(Basetile(floor(m_noise_generator.getHeight(i,j)     + m_noise_generator.getAmplitude()),         //basetile(left, top, right, bottom)
                                             floor(m_noise_generator.getHeight(i+1,j)   + m_noise_generator.getAmplitude()),
                                             floor(m_noise_generator.getHeight(i+1,j+1) + m_noise_generator.getAmplitude()),
                                             floor(m_noise_generator.getHeight(i,j+1)   + m_noise_generator.getAmplitude())));
        }
        new_world.m_basetile_data.push_back(temp_y_vector);
        temp_y_vector.clear();
    }

    return new_world;
}
