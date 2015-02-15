#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Noisegen.hpp"
#include "worldgen.hpp"
#include "basetile.hpp"

PerlinNoise worldgen::noisegenerator;

worldgen::worldgen() {
    srand(time(NULL));
    noisegenerator.Set(.125, .0625, 16, 8, rand()); //freq was .0625
}

world worldgen::generateworld(int xsize, int ysize) {
    world newworld;
    std::vector<basetile> temp_y_vector;

    for(unsigned short i = 0; i < xsize; i++)                           //Tick up the main vector as long as defined
    {
        for(unsigned short j = 0; j < ysize; j++)                       //Tick up
        {
            temp_y_vector.push_back(basetile(8 * floor(noisegenerator.GetHeight(i,j) + 16),         //basetile(left, top, right, bottom)
                                             8 * floor(noisegenerator.GetHeight(i+1,j) + 16),
                                             8 * floor(noisegenerator.GetHeight(i+1,j+1) + 16),
                                             8 * floor(noisegenerator.GetHeight(i,j+1) + 16)));
        }
        newworld.basetile_data.push_back(temp_y_vector);
        temp_y_vector.clear();
    }

    return newworld;
}
