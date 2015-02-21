#include "cameraview.hpp"
#include <algorithm> //std::max
#include <cmath>     //pow

cameraview::cameraview() : m_viewpoint(0,0)
{
    m_zoom_level = 3;
}

cameraview::cameraview(int x, int y) : m_viewpoint(x, y)
{
    m_zoom_level = 3;
}

//TODO: Set std::min values as well
void cameraview::changeView(bool up, bool down, bool left, bool right)
{
    m_viewpoint.x = std::max(m_viewpoint.x + SCROLL_SPEED * right - SCROLL_SPEED * left, 0);    //
    m_viewpoint.y = std::max(m_viewpoint.y + SCROLL_SPEED * down  - SCROLL_SPEED * up, static_cast<int>(pow(2, m_zoom_level - 3)*(512 * -16 - 16*8)));  //return std::min eventually
}

void cameraview::setDeltaView(int x, int y)
{
    m_viewpoint.x += x;
    m_viewpoint.y += y;
}

void cameraview::setZoomLevel(int _zoom_level)
{
        if (_zoom_level > m_zoom_level)
        {
            m_viewpoint   *= 2;
            m_viewpoint.x += X_WINDOW_DIMENSION / 2;
            m_viewpoint.y += Y_WINDOW_DIMENSION / 2;
        }
        else if (_zoom_level < m_zoom_level)
        {
            m_viewpoint   /= 2;
            m_viewpoint.x -= X_WINDOW_DIMENSION / 4;
            m_viewpoint.y -= Y_WINDOW_DIMENSION / 4;
        }
        m_zoom_level = _zoom_level;

        // Keep in bounds
        m_viewpoint.x = std::max(m_viewpoint.x, 0);
        m_viewpoint.y = std::max(m_viewpoint.y , static_cast<int>(pow(2, m_zoom_level - 3)*(512 * -16 - 16*8)));  //return std::min eventually

}
