#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <vector>
#include "basetile.hpp"

class world {
    friend class worldgen;
    std::vector < std::vector <basetile> > basetile_data;

    world();
public:

    world(const world& genworld);

    int getXsize() const {return basetile_data[0].size();}
    int getYsize() const {return basetile_data.size();}
    basetile tile(int x, int y) const {return basetile_data[x][y];}
};

#endif // WORLD_HPP_INCLUDED
