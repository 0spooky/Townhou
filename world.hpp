#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <vector>
#include "basetile.hpp"

class world {
    friend class worldgen;
    std::vector < std::vector <basetile> > basetile_data;
public:

};

#endif // WORLD_HPP_INCLUDED
