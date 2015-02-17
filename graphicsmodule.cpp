#include "graphicsmodule.hpp"
#include "world.hpp"
#include "cameraview.hpp"
#include "basetile.hpp"

#include <cmath>

#include <iostream>

graphicsmodule::graphicsmodule() {

    zoom_level = 3;

    maptiletex.loadFromFile("data/tiles_grass_0.png");

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

    int x1, y1;                                             //      used for algebraic purposes

    int   xsize = gameworld.getXsize(),                     //      The arbitrary "x" size of the game map
          ysize = gameworld.getYsize();                     //      The arbitrary "y" size of the game map;  In theory this supports non-homologous lengths, but that'll never get implemented?
                                                            //      Not worth making width variable, so why make height variable?
                                                            //      Will probably take this out eventually for optimization or something

    // see (COMMENT ID: 000001) for information about this loop
    for(unsigned int i = std::max((maincamera.getX()/64 - maincamera.getY()/32) - 48, 0); i < std::min(xsize, ((maincamera.getX()/64 - maincamera.getY()/32) + 1920/64) + 0); i++)
    {

    // see (COMMENT ID: 000002) for information about this loop
        for(unsigned int j = std::max((maincamera.getX()/64 + maincamera.getY()/32) + 0, 0); j < std::min(ysize, ((maincamera.getX()/64 + maincamera.getY()/32) + 960/32 + 48)); j++)
        {
            x1 = 32 * (i + j);      //the x and y solutions to the transformation matrix [x] [ 32      32 ]
            y1 = 16 * (-i + j);     //                                                   [y] [-16      16 ]

            sf::Vector2f tileposition(x1 - maincamera.getX(), y1 - maincamera.getY() - gameworld.tile(i,j).reference_height());

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
    _scaleTiles();

    std::cout << zoom_level << ":" << powf(2, zoom_level-BASIC_ZOOM_LEVEL) << std::endl;

}

void graphicsmodule::_scaleTiles()
{
    flat_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    //Single high tiles
    _2_1_1_1_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _1_1_1_2_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _1_1_2_1_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _1_2_1_1_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    //Full slant tiles
    _0_1_1_0_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _0_0_1_1_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _1_0_0_1_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _1_1_0_0_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    //Single low tiles
    _0_1_1_1_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _1_0_1_1_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _1_1_0_1_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _1_1_1_0_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    //Full tilt tiles
    _1_0_1_2_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _2_1_0_1_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _1_2_1_0_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _0_1_2_1_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    //Split tiles
    _1_0_1_0_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
    _0_1_0_1_iso_tile.setScale(powf(2, zoom_level-BASIC_ZOOM_LEVEL), powf(2, zoom_level-BASIC_ZOOM_LEVEL));
}
