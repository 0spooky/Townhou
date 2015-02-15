#include "basetile.hpp"

void basetile::setvertices(short left, short top, short right, short bot)
{
    leftheight  = left;
    topheight   = top;
    rightheight = right;
    botheight   = bot;
    if      ((left == top) && (top == right) && (right == bot))
        typeoftile = TILEFLAT;
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

int basetile::gethighestpoint() const{
    return std::max(std::max(topheight,
                            rightheight),
                    std::max(botheight,
                            leftheight));
}

tiletype basetile::gettiletype() const{
    return typeoftile;
}
