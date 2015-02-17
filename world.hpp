#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <vector>
#include "basetile.hpp"

class world {
    //Allow worldgen to alter basetile_data when generating a new world
    friend class worldgen;

    //A vector of vectors to simulate a world matrix of basetiles
    std::vector < std::vector <basetile> > basetile_data;

    //Hidden constructor used by worldgen class
    world();
public:

    //Normal constructor (copy) called with world(worldgen::generateworld(x, y)
    world(const world& genworld);

    //Functions to return dimensions of the world. TODO: Make these new parameters.  Why calculate every time?
    int getXsize() const {return basetile_data[0].size();}
    int getYsize() const {return basetile_data.size();}

    //Return the tile at position (x, y)
    basetile tile(int x, int y) const {return basetile_data[x][y];}
};

#endif // WORLD_HPP_INCLUDED
