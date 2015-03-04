#include <cmath>

#include "Basetile.hpp"
#include "CameraView.hpp"
#include "GraphicsModule.hpp"
#include "Input.hpp"
#include "Tilemap.hpp"
#include "World.hpp"

#include <iostream>

GraphicsModule::GraphicsModule(int _xWindowDimension, int _yWindowDimension) :  m_main_camera(_xWindowDimension, _yWindowDimension, 0, -_yWindowDimension/2),
                                                                                m_tilemap(_xWindowDimension, _yWindowDimension)
{
    //Initialize simple values
    m_zoom_level = 3;

    m_scale_level = 1.0;

    xWindowDimension = _xWindowDimension;
    yWindowDimension = _yWindowDimension;

    m_x_tiles_fit_screen = xWindowDimension/static_cast<int>(64 * m_scale_level);
    m_y_tiles_fit_screen = yWindowDimension/static_cast<int>(32 * m_scale_level);

    //Initialize texture
    m_maptile_tex.loadFromFile("data/tiles_grass_0.png");

    //Initialize standard base tiles
    for(int i = 0; i < 20; i++)
    {
        m_base_iso_tiles[i].setTexture(m_maptile_tex);
        if(i == 0)
            m_base_iso_tiles[i].setTextureRect(sf::IntRect(0, 0, 64, 48));
        else
            m_base_iso_tiles[i].setTextureRect(sf::IntRect(((i-1)%4)*64, ((i-1)/4 + 1)*48, 64, 48));
    }

}

CameraView& GraphicsModule::getMainCamera()
{
    return m_main_camera;
}

void GraphicsModule::_renderWorld(sf::RenderWindow &mwindow, const World &gameworld) {

    // Used for calculating transformation matrices of x any y values
    int x1, y1;

    // The "x" size of the game map
    // The "y" size of the game map;
    // Will probably take this out eventually for optimization or something
    int   x_size = gameworld.getXsize() - 1,
          y_size = gameworld.getYsize() - 1;

    // The x and y solutions to the inverse transformation matrix [x] [ 1/64 -1/32]
    //                                                            [y] [ 1/64  1/32]
    // With each term multiplied by the reciprocal of m_scale_level (by theorem of inverse matrices)
    int xTileTopLeft = static_cast<int>((m_main_camera.getX()/64 - m_main_camera.getY()/32)/m_scale_level);
    int yTileTopLeft = static_cast<int>((m_main_camera.getX()/64 + m_main_camera.getY()/32)/m_scale_level);

    // Precalculate the start and stop points
    // BEST FIX:
    // TODO CHANGE THIS TO MAKE IT SO THAT ONLY SEEN TILES ARE DRAWN INSTEAD OF OVERLAYED SQUARE?
    //      THIS WILL BE A DRASTIC CHANGE AND WILL REQUIRE USING THE FOR LOOPS.  IS IT WORTH IT? -> MAY IMPROVE PERFORMANCE
    // SECONDARY FIX:
    // TODO Fix height offset values ->WILL HURT PERFORMANCE ACTUALLY
    int xTileStart = std::max(static_cast<int>(xTileTopLeft - m_y_tiles_fit_screen - 4), 0);
    int xTileEnd   = std::min(x_size, xTileTopLeft + m_x_tiles_fit_screen);

    int yTileStart = std::max(yTileTopLeft, 0);
    int yTileEnd   = std::min(y_size, static_cast<int>(yTileTopLeft + m_y_tiles_fit_screen + m_x_tiles_fit_screen + 6));

    // see (COMMENT ID: C000001) for information about this loop
    for (int i = xTileStart; i < xTileEnd; i++)
    {
    // see (COMMENT ID: C000002) for information about this loop
        for (int j = yTileStart; j < yTileEnd; j++)
        {
            // The x and y solutions to the transformation matrix [x] [ 32      32 ]
            //                                                    [y] [-16      16 ]
            // With each term multiplied by m_scale_level
            // Cast to int is not required in x1
            //
            // In y1 calculation, m_scale_level must be cast to int before it hits
            //      (-i + j) or else implicit casting of negative float returns garbage values
            x1 =                 (m_scale_level * 32) * ( i + j);
            y1 = static_cast<int>(m_scale_level * 16) * (-i + j);

            sf::Vector2f tile_position(x1 - m_main_camera.getX(), y1 - m_main_camera.getY() - HEIGHT_INCREMENTS * m_scale_level * gameworld.tile(i,j).referenceHeight());

            _drawIsoTile(gameworld.tile(i,j).getTileType(), mwindow, tile_position);
        }
    }
}

void GraphicsModule::_drawIsoTile(const TileType _tile_ID, sf::RenderWindow &_target_window, const sf::Vector2f &_tile_position)
{
    m_base_iso_tiles[_tile_ID].setPosition(_tile_position);
    _target_window.draw(m_base_iso_tiles[_tile_ID]);
}

void GraphicsModule::_changeZoomLevel(int delta)
{
    if (m_zoom_level < 6 && delta > 0)
        m_zoom_level++;
    else if (m_zoom_level > 0 && delta < 0)
        m_zoom_level--;

    //Scale things based off powers of 2
    m_scale_level = powf(2, m_zoom_level - BASIC_ZOOM_LEVEL);

    //Set the new number of tiles that fit onscreen (for math)
    m_x_tiles_fit_screen = xWindowDimension/static_cast<int>(64*m_scale_level);
    m_y_tiles_fit_screen = yWindowDimension/static_cast<int>(32*m_scale_level);

    m_main_camera.setZoomLevel(m_zoom_level);

    //Alter sprites
    _scaleTiles();

}

void GraphicsModule::_scaleTiles()
{
    for (int i = 0; i < 20; i++)
        m_base_iso_tiles[i].setScale(m_scale_level, m_scale_level);
}

void GraphicsModule::update(sf::RenderWindow &mwindow, const World &gameworld)
{
    if (Input::getMouseWheelDelta() != 0) {
        _changeZoomLevel(Input::getMouseWheelDelta());
        Input::zeroMouseWheelDelta();
    }

    if (Input::arrowKeyPressed())
        m_main_camera.changeView(Input::getKeyPressed("Up"), Input::getKeyPressed("Down"), Input::getKeyPressed("Left"), Input::getKeyPressed("Right"));

    _renderWorld(mwindow, gameworld);
}
