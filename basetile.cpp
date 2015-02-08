#include "basetile.hpp"

void basetile::setvertices(short left, short top, short right, short bot)
{
    leftheight  = left;
    topheight   = top;
    rightheight = right;
    botheight   = bot;
    flat        = ((left == top) && (top == right) && (right == bot));
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
