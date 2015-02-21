#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <vector>
#include "basetile.hpp"

class world {
    //Allow worldgen to alter m_basetile_data when generating a new world
    friend class worldgen;

    //A vector of vectors to simulate a world matrix of basetiles
    std::vector < std::vector <basetile> > m_basetile_data;

    //Hidden constructor used by worldgen class
    world();
public:

    //Normal constructor (copy) called with world(worldgen::generateworld(x, y)
    world(const world& _genworld);

    //Functions to return dimensions of the world. TODO: Make these new parameters.  Why calculate every time?
    int getXsize() const {return m_basetile_data[0].size();}
    int getYsize() const {return m_basetile_data.size();}

    //Return the tile at position (x, y)
    basetile tile(int x, int y) const {return m_basetile_data[x][y];}
};

#endif // WORLD_HPP_INCLUDED
