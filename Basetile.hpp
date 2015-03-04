#ifndef BASETILE_HPP_INCLUDED
#define BASETILE_HPP_INCLUDED

//An identifier tag for a Basetile.  This may not be a good system
enum TileType {
    TILEFLAT=0,
    TILE2111=1,
    TILE1112=2,
    TILE1121=3,
    TILE1211=4,
    TILE1100=5,
    TILE1001=6,
    TILE0011=7,
    TILE0110=8,
    TILE1101=9,
    TILE1011=10,
    TILE0111=11,
    TILE1110=12,
    TILE1012=13,
    TILE2101=14,
    TILE1210=15,
    TILE0121=16,
    TILE0101=17,
    TILE1010=18,
    TILENULL=19
    };

class Basetile {

    //The Basetile's identifier tag
    TileType m_type_of_tile;

    //The heights of the vertices of the tile
    //left denotes north-west corner, top  denotes north-east corner
    //bot  denotes south-west corner, left denotes south-east corner
    int m_left_height,
        m_top_height,
        m_right_height,
        m_bot_height;

public:

    //constructors
    Basetile(int _left, int _top, int _right, int _bot);
    Basetile(int _height);
    Basetile();

    //Function to alter vertices
    void setVertices(int _left, int _top, int _right, int _bot);

    //Function to determine highest point
    int getHighestPoint() const;

    //Function to determine "flat" height
    int referenceHeight() const;

    //Function to get identifier tag
    TileType getTileType() const {return m_type_of_tile;};

};

#endif // BASETILE_HPP_INCLUDED
