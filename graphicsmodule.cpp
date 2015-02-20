#include "graphicsmodule.hpp"
#include "world.hpp"
#include "cameraview.hpp"
#include "basetile.hpp"

#include <cmath>

#include <iostream>

graphicsmodule::graphicsmodule() {

    //Initialize simple values
    zoom_level = 3;

    scale_level = 1.0;

    xTilesFitScreen = X_WINDOW_DIMENSION/static_cast<int>(64 * scale_level);
    yTilesFitScreen = Y_WINDOW_DIMENSION/static_cast<int>(32 * scale_level);

    //Initialize texture
    maptiletex.loadFromFile("data/tiles_grass_0.png");

    //Initialize basetile sprites
    flat_iso_tile.setTexture(maptiletex);
    flat_iso_tile.setTextureRect(sf::IntRect(0, 0, 64, 48));

    //Single high tiles

    _2_1_1_1_iso_tile.setTexture(maptiletex);
    _2_1_1_1_iso_tile.setTextureRect(sf::IntRect(0*64, 1*48, 64, 48));

    _1_1_1_2_iso_tile.setTexture(maptiletex);
    _1_1_1_2_iso_tile.setTextureRect(sf::IntRect(1*64, 1*48, 64, 48));

    _1_1_2_1_iso_tile.setTexture(maptiletex);
    _1_1_2_1_iso_tile.setTextureRect(sf::IntRect(2*64, 1*48, 64, 48));

    _1_2_1_1_iso_tile.setTexture(maptiletex);
    _1_2_1_1_iso_tile.setTextureRect(sf::IntRect(3*64, 1*48, 64, 48));

    //Full slant tiles

    _1_1_0_0_iso_tile.setTexture(maptiletex);
    _1_1_0_0_iso_tile.setTextureRect(sf::IntRect(0*64, 2*48, 64, 48));

    _1_0_0_1_iso_tile.setTexture(maptiletex);
    _1_0_0_1_iso_tile.setTextureRect(sf::IntRect(1*64, 2*48, 64, 48));

    _0_0_1_1_iso_tile.setTexture(maptiletex);
    _0_0_1_1_iso_tile.setTextureRect(sf::IntRect(2*64, 2*48, 64, 48));

    _0_1_1_0_iso_tile.setTexture(maptiletex);
    _0_1_1_0_iso_tile.setTextureRect(sf::IntRect(3*64, 2*48, 64, 48));

    //Single low tiles

    _1_1_0_1_iso_tile.setTexture(maptiletex);
    _1_1_0_1_iso_tile.setTextureRect(sf::IntRect(0*64, 3*48, 64, 48));

    _1_0_1_1_iso_tile.setTexture(maptiletex);
    _1_0_1_1_iso_tile.setTextureRect(sf::IntRect(1*64, 3*48, 64, 48));

    _0_1_1_1_iso_tile.setTexture(maptiletex);
    _0_1_1_1_iso_tile.setTextureRect(sf::IntRect(2*64, 3*48, 64, 48));

    _1_1_1_0_iso_tile.setTexture(maptiletex);
    _1_1_1_0_iso_tile.setTextureRect(sf::IntRect(3*64, 3*48, 64, 48));

    //Full tilt tiles

    _1_0_1_2_iso_tile.setTexture(maptiletex);
    _1_0_1_2_iso_tile.setTextureRect(sf::IntRect(0*64, 4*48, 64, 48));

    _2_1_0_1_iso_tile.setTexture(maptiletex);
    _2_1_0_1_iso_tile.setTextureRect(sf::IntRect(1*64, 4*48, 64, 48));

    _1_2_1_0_iso_tile.setTexture(maptiletex);
    _1_2_1_0_iso_tile.setTextureRect(sf::IntRect(2*64, 4*48, 64, 48));

    _0_1_2_1_iso_tile.setTexture(maptiletex);
    _0_1_2_1_iso_tile.setTextureRect(sf::IntRect(3*64, 4*48, 64, 48));

    //Split tiles

    _0_1_0_1_iso_tile.setTexture(maptiletex);
    _0_1_0_1_iso_tile.setTextureRect(sf::IntRect(0*64, 5*48, 64, 48));

    _1_0_1_0_iso_tile.setTexture(maptiletex);
    _1_0_1_0_iso_tile.setTextureRect(sf::IntRect(1*64, 5*48, 64, 48));

}

void graphicsmodule::renderworld(sf::RenderWindow &mwindow, const cameraview &maincamera, const world &gameworld) {

    // Used for calculating transformation matrices of x any y values
    int x1, y1;

    // The "x" size of the game map
    // The "y" size of the game map;
    // Will probably take this out eventually for optimization or something
    int   xsize = gameworld.getXsize(),
          ysize = gameworld.getYsize();

    // The x and y solutions to the inverse transformation matrix [x] [ 1/64 -1/32]
    //                                                            [y] [ 1/64  1/32]
    // With each term multiplied by the reciprocal of scale_level (by theorem of inverse matrices)
    int xTileStart = static_cast<int>((maincamera.getX()/64 - maincamera.getY()/32)/scale_level);
    int yTileStart = static_cast<int>((maincamera.getX()/64 + maincamera.getY()/32)/scale_level);

    // see (COMMENT: C000001) for information about this loop
    for (int i = std::max(xTileStart - yTilesFitScreen, 0); i < std::min(xsize, xTileStart + xTilesFitScreen); i++)
    {
    // see (COMMENT ID: 000002) for information about this loop
        for (int j = std::max(yTileStart, 0); j < std::min(ysize, yTileStart + yTilesFitScreen + xTilesFitScreen); j++)
        {
            // The x and y solutions to the transformation matrix [x] [ 32      32 ]
            //                                                    [y] [-16      16 ]
            // With each term multiplied by scale_level
            // Cast to int is not required in x1
            //
            // In y1 calculation, scale_level must be cast to int before it hits
            //      (-i + j) or else implicit casting returns garbage values
            x1 =                 (scale_level * 32) * ( i + j);
            y1 = static_cast<int>(scale_level * 16) * (-i + j);

            sf::Vector2f tileposition(x1 - maincamera.getX(), y1 - maincamera.getY() - HEIGHT_INCREMENTS * scale_level * gameworld.tile(i,j).reference_height());

            switch(gameworld.tile(i,j).gettiletype()) {

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

void graphicsmodule::changeZoomLevel(int delta)
{
    zoom_level += delta;
    if (zoom_level < 1)
        zoom_level = 1;
    if (zoom_level > 6)
        zoom_level = 6;
    //Scale things based off powers of 2
    scale_level = powf(2, zoom_level - BASIC_ZOOM_LEVEL);

    //Set the new number of tiles that fit onscreen (for math)
    xTilesFitScreen = X_WINDOW_DIMENSION/static_cast<int>(64*scale_level);
    yTilesFitScreen = Y_WINDOW_DIMENSION/static_cast<int>(32*scale_level);

    //Alter sprites
    _scaleTiles();

    std::cout << zoom_level << ":" << powf(2, zoom_level - BASIC_ZOOM_LEVEL) << std::endl;

}

void graphicsmodule::_scaleTiles()
{
    flat_iso_tile.setScale(scale_level, scale_level);
    //Single high tiles
    _2_1_1_1_iso_tile.setScale(scale_level, scale_level);
    _1_1_1_2_iso_tile.setScale(scale_level, scale_level);
    _1_1_2_1_iso_tile.setScale(scale_level, scale_level);
    _1_2_1_1_iso_tile.setScale(scale_level, scale_level);
    //Full slant tiles
    _0_1_1_0_iso_tile.setScale(scale_level, scale_level);
    _0_0_1_1_iso_tile.setScale(scale_level, scale_level);
    _1_0_0_1_iso_tile.setScale(scale_level, scale_level);
    _1_1_0_0_iso_tile.setScale(scale_level, scale_level);
    //Single low tiles
    _0_1_1_1_iso_tile.setScale(scale_level, scale_level);
    _1_0_1_1_iso_tile.setScale(scale_level, scale_level);
    _1_1_0_1_iso_tile.setScale(scale_level, scale_level);
    _1_1_1_0_iso_tile.setScale(scale_level, scale_level);
    //Full tilt tiles
    _1_0_1_2_iso_tile.setScale(scale_level, scale_level);
    _2_1_0_1_iso_tile.setScale(scale_level, scale_level);
    _1_2_1_0_iso_tile.setScale(scale_level, scale_level);
    _0_1_2_1_iso_tile.setScale(scale_level, scale_level);
    //Split tiles
    _1_0_1_0_iso_tile.setScale(scale_level, scale_level);
    _0_1_0_1_iso_tile.setScale(scale_level, scale_level);
}
