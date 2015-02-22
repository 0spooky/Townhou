#include <cmath>

#include <iostream>

#include "GraphicsModule.hpp"
#include "World.hpp"
#include "CameraView.hpp"
#include "Basetile.hpp"

GraphicsModule::GraphicsModule() : m_main_camera(0,-Y_WINDOW_DIMENSION/2){

    //Initialize simple values
    m_zoom_level = 3;

    m_scale_level = 1.0;

    m_x_tiles_fit_screen = X_WINDOW_DIMENSION/static_cast<int>(64 * m_scale_level);
    m_y_tiles_fit_screen = Y_WINDOW_DIMENSION/static_cast<int>(32 * m_scale_level);

    //Initialize texture
    m_maptile_tex.loadFromFile("data/tiles_grass_0.png");

    //Initialize basetile sprites
    flat_iso_tile.setTexture(m_maptile_tex);
    flat_iso_tile.setTextureRect(sf::IntRect(0, 0, 64, 48));

    //Single high tiles

    _2_1_1_1_iso_tile.setTexture(m_maptile_tex);
    _2_1_1_1_iso_tile.setTextureRect(sf::IntRect(0*64, 1*48, 64, 48));

    _1_1_1_2_iso_tile.setTexture(m_maptile_tex);
    _1_1_1_2_iso_tile.setTextureRect(sf::IntRect(1*64, 1*48, 64, 48));

    _1_1_2_1_iso_tile.setTexture(m_maptile_tex);
    _1_1_2_1_iso_tile.setTextureRect(sf::IntRect(2*64, 1*48, 64, 48));

    _1_2_1_1_iso_tile.setTexture(m_maptile_tex);
    _1_2_1_1_iso_tile.setTextureRect(sf::IntRect(3*64, 1*48, 64, 48));

    //Full slant tiles

    _1_1_0_0_iso_tile.setTexture(m_maptile_tex);
    _1_1_0_0_iso_tile.setTextureRect(sf::IntRect(0*64, 2*48, 64, 48));

    _1_0_0_1_iso_tile.setTexture(m_maptile_tex);
    _1_0_0_1_iso_tile.setTextureRect(sf::IntRect(1*64, 2*48, 64, 48));

    _0_0_1_1_iso_tile.setTexture(m_maptile_tex);
    _0_0_1_1_iso_tile.setTextureRect(sf::IntRect(2*64, 2*48, 64, 48));

    _0_1_1_0_iso_tile.setTexture(m_maptile_tex);
    _0_1_1_0_iso_tile.setTextureRect(sf::IntRect(3*64, 2*48, 64, 48));

    //Single low tiles

    _1_1_0_1_iso_tile.setTexture(m_maptile_tex);
    _1_1_0_1_iso_tile.setTextureRect(sf::IntRect(0*64, 3*48, 64, 48));

    _1_0_1_1_iso_tile.setTexture(m_maptile_tex);
    _1_0_1_1_iso_tile.setTextureRect(sf::IntRect(1*64, 3*48, 64, 48));

    _0_1_1_1_iso_tile.setTexture(m_maptile_tex);
    _0_1_1_1_iso_tile.setTextureRect(sf::IntRect(2*64, 3*48, 64, 48));

    _1_1_1_0_iso_tile.setTexture(m_maptile_tex);
    _1_1_1_0_iso_tile.setTextureRect(sf::IntRect(3*64, 3*48, 64, 48));

    //Full tilt tiles

    _1_0_1_2_iso_tile.setTexture(m_maptile_tex);
    _1_0_1_2_iso_tile.setTextureRect(sf::IntRect(0*64, 4*48, 64, 48));

    _2_1_0_1_iso_tile.setTexture(m_maptile_tex);
    _2_1_0_1_iso_tile.setTextureRect(sf::IntRect(1*64, 4*48, 64, 48));

    _1_2_1_0_iso_tile.setTexture(m_maptile_tex);
    _1_2_1_0_iso_tile.setTextureRect(sf::IntRect(2*64, 4*48, 64, 48));

    _0_1_2_1_iso_tile.setTexture(m_maptile_tex);
    _0_1_2_1_iso_tile.setTextureRect(sf::IntRect(3*64, 4*48, 64, 48));

    //Split tiles

    _0_1_0_1_iso_tile.setTexture(m_maptile_tex);
    _0_1_0_1_iso_tile.setTextureRect(sf::IntRect(0*64, 5*48, 64, 48));

    _1_0_1_0_iso_tile.setTexture(m_maptile_tex);
    _1_0_1_0_iso_tile.setTextureRect(sf::IntRect(1*64, 5*48, 64, 48));

}

CameraView& GraphicsModule::getMainCamera()
{
    return m_main_camera;
}

void GraphicsModule::renderWorld(sf::RenderWindow &mwindow, const World &gameworld) {

    // Used for calculating transformation matrices of x any y values
    int x1, y1;

    // The "x" size of the game map
    // The "y" size of the game map;
    // Will probably take this out eventually for optimization or something
    int   xsize = gameworld.getXsize(),
          ysize = gameworld.getYsize();

    // The x and y solutions to the inverse transformation matrix [x] [ 1/64 -1/32]
    //                                                            [y] [ 1/64  1/32]
    // With each term multiplied by the reciprocal of m_scale_level (by theorem of inverse matrices)
    int xTileTopLeft = static_cast<int>((m_main_camera.getX()/64 - m_main_camera.getY()/32)/m_scale_level);
    int yTileTopLeft = static_cast<int>((m_main_camera.getX()/64 + m_main_camera.getY()/32)/m_scale_level);

    // Precalculate the start and stop points
    // TODO CHANGE THIS TO MAKE IT SO THAT ONLY SEEN TILES ARE DRAWN INSTEAD OF OVERLAYED SQUARE?
    int xTileStart = std::max(xTileTopLeft - m_y_tiles_fit_screen, 0);
    int xTileEnd   = std::min(xsize, xTileTopLeft + m_x_tiles_fit_screen);

    int yTileStart = std::max(yTileTopLeft, 0);
    int yTileEnd   = std::min(ysize, yTileTopLeft + m_y_tiles_fit_screen + m_x_tiles_fit_screen);

    // see (COMMENT: C000001) for information about this loop
    for (int i = xTileStart; i < xTileEnd; i++)
    {
    // see (COMMENT ID: 000002) for information about this loop
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

            sf::Vector2f tileposition(x1 - m_main_camera.getX(), y1 - m_main_camera.getY() - HEIGHT_INCREMENTS * m_scale_level * gameworld.tile(i,j).referenceHeight());

            switch(gameworld.tile(i,j).getTileType()) {

                case (TILEFLAT):
                    flat_iso_tile.setPosition(tileposition);
                    mwindow.draw(flat_iso_tile);
                    break;

                //Single high tiles
                case (TILE2111):
                    _2_1_1_1_iso_tile.setPosition(tileposition);
                    mwindow.draw(_2_1_1_1_iso_tile);
                    break;

                case (TILE1112):
                    _1_1_1_2_iso_tile.setPosition(tileposition);
                    mwindow.draw(_1_1_1_2_iso_tile);
                    break;

                case (TILE1121):
                    _1_1_2_1_iso_tile.setPosition(tileposition);
                    mwindow.draw(_1_1_2_1_iso_tile);
                    break;

                case (TILE1211):
                    _1_2_1_1_iso_tile.setPosition(tileposition);
                    mwindow.draw(_1_2_1_1_iso_tile);
                    break;

                //Full slant tiles
                case (TILE0110):
                    _0_1_1_0_iso_tile.setPosition(tileposition);
                    mwindow.draw(_0_1_1_0_iso_tile);
                    break;

                case (TILE0011):
                    _0_0_1_1_iso_tile.setPosition(tileposition);
                    mwindow.draw(_0_0_1_1_iso_tile);
                    break;

                case (TILE1001):
                    _1_0_0_1_iso_tile.setPosition(tileposition);
                    mwindow.draw(_1_0_0_1_iso_tile);
                    break;

                case (TILE1100):
                    _1_1_0_0_iso_tile.setPosition(tileposition);
                    mwindow.draw(_1_1_0_0_iso_tile);
                    break;

                //Single low tiles
                case (TILE0111):
                    _0_1_1_1_iso_tile.setPosition(tileposition);
                    mwindow.draw(_0_1_1_1_iso_tile);
                    break;

                case (TILE1011):
                    _1_0_1_1_iso_tile.setPosition(tileposition);
                    mwindow.draw(_1_0_1_1_iso_tile);
                    break;

                case (TILE1101):
                    _1_1_0_1_iso_tile.setPosition(tileposition);
                    mwindow.draw(_1_1_0_1_iso_tile);
                    break;

                case (TILE1110):
                    _1_1_1_0_iso_tile.setPosition(tileposition);
                    mwindow.draw(_1_1_1_0_iso_tile);
                    break;

                //Full tilt tiles

                case (TILE1012):
                    _1_0_1_2_iso_tile.setPosition(tileposition);
                    mwindow.draw(_1_0_1_2_iso_tile);
                    break;

                case (TILE2101):
                    _2_1_0_1_iso_tile.setPosition(tileposition);
                    mwindow.draw(_2_1_0_1_iso_tile);
                    break;

                case (TILE1210):
                    _1_2_1_0_iso_tile.setPosition(tileposition);
                    mwindow.draw(_1_2_1_0_iso_tile);
                    break;

                case (TILE0121):
                    _0_1_2_1_iso_tile.setPosition(tileposition);
                    mwindow.draw(_0_1_2_1_iso_tile);
                    break;

                //Split tiles
                case (TILE1010):
                    _1_0_1_0_iso_tile.setPosition(tileposition);
                    mwindow.draw(_1_0_1_0_iso_tile);
                    break;

                case (TILE0101):
                    _0_1_0_1_iso_tile.setPosition(tileposition);
                    mwindow.draw(_0_1_0_1_iso_tile);
                    break;

                //default:
                //   break;
            }
        }
    }
}

void GraphicsModule::changeZoomLevel(int delta)
{
    if (m_zoom_level < 6 && delta > 0)
        m_zoom_level++;
    else if (m_zoom_level > 1 && delta < 0)
        m_zoom_level--;

    //Scale things based off powers of 2
    m_scale_level = powf(2, m_zoom_level - BASIC_ZOOM_LEVEL);

    //Set the new number of tiles that fit onscreen (for math)
    m_x_tiles_fit_screen = X_WINDOW_DIMENSION/static_cast<int>(64*m_scale_level);
    m_y_tiles_fit_screen = Y_WINDOW_DIMENSION/static_cast<int>(32*m_scale_level);

    m_main_camera.setZoomLevel(m_zoom_level);

    //Alter sprites
    _scaleTiles();

}

void GraphicsModule::_scaleTiles()
{
    flat_iso_tile.setScale(m_scale_level, m_scale_level);
    //Single high tiles
    _2_1_1_1_iso_tile.setScale(m_scale_level, m_scale_level);
    _1_1_1_2_iso_tile.setScale(m_scale_level, m_scale_level);
    _1_1_2_1_iso_tile.setScale(m_scale_level, m_scale_level);
    _1_2_1_1_iso_tile.setScale(m_scale_level, m_scale_level);
    //Full slant tiles
    _0_1_1_0_iso_tile.setScale(m_scale_level, m_scale_level);
    _0_0_1_1_iso_tile.setScale(m_scale_level, m_scale_level);
    _1_0_0_1_iso_tile.setScale(m_scale_level, m_scale_level);
    _1_1_0_0_iso_tile.setScale(m_scale_level, m_scale_level);
    //Single low tiles
    _0_1_1_1_iso_tile.setScale(m_scale_level, m_scale_level);
    _1_0_1_1_iso_tile.setScale(m_scale_level, m_scale_level);
    _1_1_0_1_iso_tile.setScale(m_scale_level, m_scale_level);
    _1_1_1_0_iso_tile.setScale(m_scale_level, m_scale_level);
    //Full tilt tiles
    _1_0_1_2_iso_tile.setScale(m_scale_level, m_scale_level);
    _2_1_0_1_iso_tile.setScale(m_scale_level, m_scale_level);
    _1_2_1_0_iso_tile.setScale(m_scale_level, m_scale_level);
    _0_1_2_1_iso_tile.setScale(m_scale_level, m_scale_level);
    //Split tiles
    _1_0_1_0_iso_tile.setScale(m_scale_level, m_scale_level);
    _0_1_0_1_iso_tile.setScale(m_scale_level, m_scale_level);
}
