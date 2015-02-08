#ifndef BASETILE_HPP_INCLUDED
#define BASETILE_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include <limits>

class basetile {
    int highestpoint = std::max(std::max(topheight,         //this value may be used to choose build height
                                       rightheight),
                                std::max(botheight,
                                       leftheight));

public:
    short   leftheight,                                     //The heights of the vertices of the tile
            topheight,                                      //left denotes north-west corner, top  denotes north-east corner
            rightheight,                                    //bot  denotes south-west corner, left denotes south-east corner
            botheight;                                              ////For now we will let them all be height 0 and assume they connect

    //constructors
    basetile(short left, short top, short right, short bot);
    basetile(short height);
    basetile();
    void setvertices(short left, short top, short right, short bot);
    bool flat;

};

#endif // BASETILE_HPP_INCLUDED
