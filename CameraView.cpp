#include <algorithm> //std::max
#include <cmath>     //pow

#include "CameraView.hpp"

#include <iostream>

CameraView::CameraView(int _xWindowDimension, int _yWindowDimension, int x, int y) : m_window_dimensions(_xWindowDimension, _yWindowDimension),
                                                                                     m_viewpoint(x, y)
{
    m_zoom_level = 3;
    m_scale_level = 1;
}

//TODO: Set std::min values as well
void CameraView::changeView(bool up, bool down, bool left, bool right)
{
    m_viewpoint.x = std::max(m_viewpoint.x + SCROLL_SPEED * right - SCROLL_SPEED * left, 0);    //
    m_viewpoint.y = std::max(m_viewpoint.y + SCROLL_SPEED * down  - SCROLL_SPEED * up, static_cast<int>(m_scale_level*(512 * -16 - 16*8)));  //return std::min eventually
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
            m_viewpoint.x += m_window_dimensions.x / 2;
            m_viewpoint.y += m_window_dimensions.y / 2;
        }
        else if (_zoom_level < m_zoom_level)
        {
            m_viewpoint   /= 2;
            m_viewpoint.x -= m_window_dimensions.x / 4;
            m_viewpoint.y -= m_window_dimensions.y / 4;
        }
        m_zoom_level  = _zoom_level;
        m_scale_level = pow(2, m_zoom_level - 3);

        // Keep in bounds
        m_viewpoint.x = std::max(m_viewpoint.x, 0);
        m_viewpoint.y = std::max(m_viewpoint.y , static_cast<int>(m_scale_level*(512 * -16 - 16*8)));  //return std::min eventually

}

void CameraView::setWindowDimensions(int _xWindowDimension, int _yWindowDimension)
{
    m_window_dimensions = {_xWindowDimension, _yWindowDimension};
}
