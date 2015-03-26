#include <cmath>

#include "Basetile.hpp"
#include "CameraView.hpp"
#include "GraphicsModule.hpp"
#include "Input.hpp"
#include "Tilemap.hpp"
#include "World.hpp"

GraphicsModule::GraphicsModule(int _xWindowDimension, int _yWindowDimension) :  m_main_camera(_xWindowDimension, _yWindowDimension, 0, -_yWindowDimension/2),
                                                                                m_tilemap(_xWindowDimension, _yWindowDimension)
{
    //Initialize simple values
    m_zoom_level = BASIC_ZOOM_LEVEL;

    m_scale_level = 1.0;

    xWindowDimension = _xWindowDimension;
    yWindowDimension = _yWindowDimension;

    m_x_tiles_fit_screen = xWindowDimension/static_cast<int>(64 * m_scale_level);
    m_y_tiles_fit_screen = yWindowDimension/static_cast<int>(32 * m_scale_level);
}

CameraView& GraphicsModule::getMainCamera()
{
    return m_main_camera;
}

void GraphicsModule::_changeZoomLevel(int delta)
{
    //Perform allowable zoom level changes
    if (m_zoom_level < MAX_ZOOM_LEVEL && delta > 0)
        m_zoom_level++;
    else if (m_zoom_level > MIN_ZOOM_LEVEL && delta < 0)
        m_zoom_level--;

    //Scale things based off powers of 2
    m_scale_level = powf(2, m_zoom_level - BASIC_ZOOM_LEVEL);

    //Set the new number of tiles that fit onscreen (for math)
    m_x_tiles_fit_screen = xWindowDimension/static_cast<int>(64*m_scale_level);
    m_y_tiles_fit_screen = yWindowDimension/static_cast<int>(32*m_scale_level);

    m_main_camera.setZoomLevel(m_zoom_level);

    m_tilemap.zoom(m_zoom_level);
}

void GraphicsModule::update(sf::RenderWindow &mwindow, const World &gameworld)
{
    if (Input::getMouseWheelDelta() != 0) {
       _changeZoomLevel(Input::getMouseWheelDelta());
       Input::zeroMouseWheelDelta();
    }

    if (Input::arrowKeyPressed())
        m_main_camera.changeView(Input::getKeyPressed("Up"), Input::getKeyPressed("Down"), Input::getKeyPressed("Left"), Input::getKeyPressed("Right"));

    m_tilemap.load(gameworld, m_main_camera);
    mwindow.draw(m_tilemap);
}
