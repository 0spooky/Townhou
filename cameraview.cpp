#include "cameraview.hpp"
#include <algorithm> //std::max

cameraview::cameraview()
{
    viewpoint.x = 0;
    viewpoint.y = 0;
}

cameraview::cameraview(int x, int y)
{
    viewpoint.x = x;
    viewpoint.y = y;
}

void cameraview::changeview(bool up, bool down, bool left, bool right)
{
    viewpoint.x = std::max(viewpoint.x + SCROLL_SPEED * right - SCROLL_SPEED * left, 0);    //
    viewpoint.y = std::max(viewpoint.y + SCROLL_SPEED * down  - SCROLL_SPEED * up, -8208);  //return std::min eventually
}
