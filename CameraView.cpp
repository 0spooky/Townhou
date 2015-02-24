#include <algorithm> //std::max
#include <cmath>     //pow

#include "CameraView.hpp"

CameraView::CameraView(int _xWindowDimension, int _yWindowDimension) : m_viewpoint(0,0)
{
    xWindowDimension = _xWindowDimension;
    yWindowDimension = _yWindowDimension;

    m_zoom_level = 3;
}

CameraView::CameraView(int _xWindowDimension, int _yWindowDimension, int x, int y) : m_viewpoint(x, y)
{
    xWindowDimension = _xWindowDimension;
    yWindowDimension = _yWindowDimension;

    m_zoom_level = 3;
}

//TODO: Set std::min values as well
void CameraView::changeView(bool up, bool down, bool left, bool right)
{
    m_viewpoint.x = std::max(m_viewpoint.x + SCROLL_SPEED * right - SCROLL_SPEED * left, 0);    //
    m_viewpoint.y = std::max(m_viewpoint.y + SCROLL_SPEED * down  - SCROLL_SPEED * up, static_cast<int>(pow(2, m_zoom_level - 3)*(512 * -16 - 16*8)));  //return std::min eventually
}

void CameraView::setDeltaView(int x, int y)
{
    m_viewpoint.x += x;
    m_viewpoint.y += y;
}

void CameraView::setZoomLevel(int _zoom_level)
{
        if (_zoom_level > m_zoom_level)
        {
            m_viewpoint   *= 2;
            m_viewpoint.x += xWindowDimension / 2;
            m_viewpoint.y += yWindowDimension / 2;
        }
        else if (_zoom_level < m_zoom_level)
        {
            m_viewpoint   /= 2;
            m_viewpoint.x -= xWindowDimension / 4;
            m_viewpoint.y -= yWindowDimension / 4;
        }
        m_zoom_level = _zoom_level;

        // Keep in bounds
        m_viewpoint.x = std::max(m_viewpoint.x, 0);
        m_viewpoint.y = std::max(m_viewpoint.y , static_cast<int>(pow(2, m_zoom_level - 3)*(512 * -16 - 16*8)));  //return std::min eventually

}

void CameraView::setWindowDimensions(int _xWindowDimension, int _yWindowDimension)
{
    xWindowDimension = _xWindowDimension;
    yWindowDimension = _yWindowDimension;
}
