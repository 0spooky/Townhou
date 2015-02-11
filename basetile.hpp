#ifndef BASETILE_HPP_INCLUDED
#define BASETILE_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include <limits>

enum tiletype {
    TILEFLAT,
    TILE0111,
    TILE1011,
    TILE1101,
    TILE1110,
    TILE0110,
    TILE0011,
    TILE1001,
    TILE1100
    };

class basetile {

    tiletype typeoftile;

public:
    short   leftheight,                                     //The heights of the vertices of the tile
            topheight,                                      //left denotes north-west corner, top  denotes north-east corner
            rightheight,                                    //bot  denotes south-west corner, left denotes south-east corner
            botheight;

    //constructors
    basetile(short left, short top, short right, short bot);
    basetile(short height);
    basetile();
    void setvertices(short left, short top, short right, short bot);
    int gethighestpoint() const;
    tiletype gettiletype() const;
    bool flat;

};

#endif // BASETILE_HPP_INCLUDED
