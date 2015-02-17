#ifndef BASETILE_HPP_INCLUDED
#define BASETILE_HPP_INCLUDED

//An identifier tag for a basetile.  This may not be a good system
enum tiletype {
    TILEFLAT,
    TILE0111,
    TILE1011,
    TILE1101,
    TILE1110,
    TILE0110,
    TILE0011,
    TILE1001,
    TILE1100,
    TILE2111,
    TILE1211,
    TILE1121,
    TILE1112,
    TILE0121,
    TILE1012,
    TILE2101,
    TILE1210,
    TILE0101,
    TILE1010,
    TILENULL
    };

class basetile {

    //The basetile's identifier tag
    tiletype typeoftile;

public:
    //The heights of the vertices of the tile
    //left denotes north-west corner, top  denotes north-east corner
    //bot  denotes south-west corner, left denotes south-east corner
    short   leftheight,
            topheight,
            rightheight,
            botheight;

    //constructors
    basetile(short left, short top, short right, short bot);
    basetile(short height);
    basetile();

    //Function to alter vertices
    void setvertices(short left, short top, short right, short bot);

    //Function to determine highest point
    int gethighestpoint() const;

    //Function to determine "flat" height
    int reference_height() const;

    //Function to get identifier tag
    tiletype gettiletype() const;

};

#endif // BASETILE_HPP_INCLUDED
