#include <algorithm> //max
#include <cmath> //round

#include "Basetile.hpp"

void Basetile::setVertices(int _left, int _top, int _right, int _bot)
{
    m_left_height  = _left;
    m_top_height   = _top;
    m_right_height = _right;
    m_bot_height   = _bot;

    //This code is ugly, can this be fixed?
    if      ((_left == _top) && (_top == _right) && (_right == _bot))
        m_type_of_tile = TILEFLAT;

    else if ((_left >  _top) && (_top == _right) && (_right == _bot))
        m_type_of_tile = TILE2111;
    else if ((_left == _top) && (_top == _right) && (_right <  _bot))
        m_type_of_tile = TILE1112;
    else if ((_left == _top) && (_top <  _right) && (_right >  _bot))
        m_type_of_tile = TILE1121;
    else if ((_left <  _top) && (_top >  _right) && (_right == _bot))
        m_type_of_tile = TILE1211;

    else if ((_left <  _top) && (_top == _right) && (_right == _bot))
        m_type_of_tile = TILE0111;
    else if ((_left >  _top) && (_top <  _right) && (_right == _bot))
        m_type_of_tile = TILE1011;
    else if ((_left == _top) && (_top >  _right) && (_right <  _bot))
        m_type_of_tile = TILE1101;
    else if ((_left == _top) && (_top == _right) && (_right >  _bot))
        m_type_of_tile = TILE1110;

    else if ((_left <  _top) && (_top == _right) && (_right >  _bot))
        m_type_of_tile = TILE0110;
    else if ((_left == _top) && (_top <  _right) && (_right == _bot))
        m_type_of_tile = TILE0011;
    else if ((_left >  _top) && (_top == _right) && (_right <  _bot))
        m_type_of_tile = TILE1001;
    else if ((_left == _top) && (_top >  _right) && (_right == _bot))
        m_type_of_tile = TILE1100;

    else if ((_left >  _top) && (_top <  _right) && (_right <  _bot))
        m_type_of_tile = TILE1012;
    else if ((_left >  _top) && (_top >  _right) && (_right <  _bot))
        m_type_of_tile = TILE2101;
    else if ((_left <  _top) && (_top >  _right) && (_right >  _bot))
        m_type_of_tile = TILE1210;
    else if ((_left <  _top) && (_top <  _right) && (_right >  _bot))
        m_type_of_tile = TILE0121;

    else if ((_left <  _top) && (_top >  _right) && (_right <  _bot))
        m_type_of_tile = TILE0101;
    else if ((_left >  _top) && (_top <  _right) && (_right >  _bot))
        m_type_of_tile = TILE1010;

    else
        m_type_of_tile = TILENULL;
}

Basetile::Basetile (int _left, int _top, int _right, int _bot)
{
    setVertices(_left, _top, _right, _bot);
}

Basetile::Basetile (int _height)
{
    setVertices(_height, _height, _height, _height);
}

Basetile::Basetile ()
{
    setVertices(0, 0, 0, 0);
}

/*
    A function used to determine which tile is highest in a Basetile

    @return The highest vertex of a Basetile
*/

int Basetile::getHighestPoint() const
{
    return std::max(std::max(m_top_height,
                            m_right_height),
                    std::max(m_bot_height,
                            m_left_height));
}

int Basetile::referenceHeight() const
{
    return static_cast<int>(round((m_left_height + m_right_height + m_top_height + m_bot_height)/4));
}
