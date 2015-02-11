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
    viewpoint.x = std::max(viewpoint.x + 12 * right - 12 * left, 0);    //
    viewpoint.y = std::max(viewpoint.y + 12 * down  - 12 * up, -8208);  //return std::min eventually
}
