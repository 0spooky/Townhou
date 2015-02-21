#ifndef BASETILE_HPP_INCLUDED
#define BASETILE_HPP_INCLUDED

//An identifier tag for a basetile.  This may not be a good system
enum TileType {
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
    TileType type_of_tile;

    //The heights of the vertices of the tile
    //left denotes north-west corner, top  denotes north-east corner
    //bot  denotes south-west corner, left denotes south-east corner
    int m_left_height,
        m_top_height,
        m_right_height,
        m_bot_height;

public:

    //constructors
    basetile(int _left, int _top, int _right, int _bot);
    basetile(int _height);
    basetile();

    //Function to alter vertices
    void setVertices(int _left, int _top, int _right, int _bot);

    //Function to determine highest point
    int getHighestPoint() const;

    //Function to determine "flat" height
    int referenceHeight() const;

    //Function to get identifier tag
    TileType getTileType() const {return type_of_tile;};

};

#endif // BASETILE_HPP_INCLUDED
