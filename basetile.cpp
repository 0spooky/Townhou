#include <cmath>
#include <algorithm>

#include "basetile.hpp"


void basetile::setvertices(short left, short top, short right, short bot)
{
    leftheight  = left;
    topheight   = top;
    rightheight = right;
    botheight   = bot;
    if      ((left == top) && (top == right) && (right == bot))
        typeoftile = TILEFLAT;

    else if ((left >  top) && (top == right) && (right == bot))
        typeoftile = TILE2111;
    else if ((left == top) && (top == right) && (right <  bot))
        typeoftile = TILE1112;
    else if ((left == top) && (top <  right) && (right >  bot))
        typeoftile = TILE1121;
    else if ((left <  top) && (top >  right) && (right == bot))
        typeoftile = TILE1211;

    else if ((left <  top) && (top == right) && (right == bot))
        typeoftile = TILE0111;
    else if ((left >  top) && (top <  right) && (right == bot))
        typeoftile = TILE1011;
    else if ((left == top) && (top >  right) && (right <  bot))
        typeoftile = TILE1101;
    else if ((left == top) && (top == right) && (right >  bot))
        typeoftile = TILE1110;

    else if ((left <  top) && (top == right) && (right >  bot))
        typeoftile = TILE0110;
    else if ((left == top) && (top <  right) && (right == bot))
        typeoftile = TILE0011;
    else if ((left >  top) && (top == right) && (right <  bot))
        typeoftile = TILE1001;
    else if ((left == top) && (top >  right) && (right == bot))
        typeoftile = TILE1100;

    else if ((left >  top) && (top <  right) && (right <  bot))
        typeoftile = TILE1012;
    else if ((left >  top) && (top >  right) && (right <  bot))
        typeoftile = TILE2101;
    else if ((left <  top) && (top >  right) && (right >  bot))
        typeoftile = TILE1210;
    else if ((left <  top) && (top <  right) && (right >  bot))
        typeoftile = TILE0121;

    else if ((left <  top) && (top >  right) && (right <  bot))
        typeoftile = TILE0101;
    else if ((left >  top) && (top <  right) && (right >  bot))
        typeoftile = TILE1010;

    else
        typeoftile = TILENULL;
}

basetile::basetile (short left, short top, short right, short bot)
{
    setvertices(left, top, right, bot);
}

basetile::basetile (short height)
{
    setvertices(height, height, height, height);
}

basetile::basetile ()
{
    setvertices(0, 0, 0, 0);
}

/**
    A function used to determine which tile is highest in a basetile

    @return The highest vertex of a basetile
*/

int basetile::gethighestpoint() const
{
    return std::max(std::max(topheight,
                            rightheight),
                    std::max(botheight,
                            leftheight));
}

int basetile::reference_height() const
{
    int refheight;
    refheight = static_cast<int>(round((leftheight + rightheight + topheight + botheight)/4));
    return refheight;
}

tiletype basetile::gettiletype() const
{
    return typeoftile;
}
