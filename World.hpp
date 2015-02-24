#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <vector>

#include "Basetile.hpp"

class World {
    //Allow WorldGenerator to alter m_basetile_data when generating a new World
    friend class WorldGenerator;

    //A vector of vectors to simulate a World matrix of basetiles
    std::vector < std::vector <Basetile> > m_basetile_data;

    //Hidden constructor used by WorldGenerator class
    World();
public:

    //Normal constructor (copy) called with World(WorldGenerator::generateWorld(x, y)
    World(const World& _generated_world);

    //Functions to return dimensions of the World. TODO: Make these new parameters.  Why calculate every time?
    int getXsize() const {return m_basetile_data[0].size();}
    int getYsize() const {return m_basetile_data.size();}

    //Return the tile at position (x, y)
    Basetile tile(int x, int y) const {return m_basetile_data[x][y];}
};

#endif // WORLD_HPP_INCLUDED
