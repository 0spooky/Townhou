#include "graphicsmodule.hpp"
#include "world.hpp"
#include "cameraview.hpp"
#include "basetile.hpp"

graphicsmodule::graphicsmodule() {

    maptiletex.loadFromFile("data/tiles_grass_0.png");

    flat_iso_tile.setTexture(maptiletex);                                   //Origins are really wrong
    flat_iso_tile.setTextureRect(sf::IntRect(0, 0, 64, 48));
    flat_iso_tile.setOrigin(0, 32);

    _1_1_0_1_iso_tile.setTexture(maptiletex);
    _1_1_0_1_iso_tile.setTextureRect(sf::IntRect(0*64, 3*48, 64, 48));
    _1_1_0_1_iso_tile.setOrigin(0, 24);

    _1_0_1_1_iso_tile.setTexture(maptiletex);
    _1_0_1_1_iso_tile.setTextureRect(sf::IntRect(1*64, 3*48, 64, 48));
    _1_0_1_1_iso_tile.setOrigin(0, 24);

    _0_1_1_1_iso_tile.setTexture(maptiletex);
    _0_1_1_1_iso_tile.setTextureRect(sf::IntRect(2*64, 3*48, 64, 48));
    _0_1_1_1_iso_tile.setOrigin(0, 32);

    _1_1_1_0_iso_tile.setTexture(maptiletex);
    _1_1_1_0_iso_tile.setTextureRect(sf::IntRect(3*64, 3*48, 64, 48));
    _1_1_1_0_iso_tile.setOrigin(0, 24);


    _1_1_0_0_iso_tile.setTexture(maptiletex);
    _1_1_0_0_iso_tile.setTextureRect(sf::IntRect(0*64, 2*48, 64, 48));
    _1_1_0_0_iso_tile.setOrigin(0, 24);

    _1_0_0_1_iso_tile.setTexture(maptiletex);
    _1_0_0_1_iso_tile.setTextureRect(sf::IntRect(1*64, 2*48, 64, 48));
    _1_0_0_1_iso_tile.setOrigin(0, 24);

    _0_0_1_1_iso_tile.setTexture(maptiletex);
    _0_0_1_1_iso_tile.setTextureRect(sf::IntRect(2*64, 2*48, 64, 48));
    _0_0_1_1_iso_tile.setOrigin(0, 32);

    _0_1_1_0_iso_tile.setTexture(maptiletex);
    _0_1_1_0_iso_tile.setTextureRect(sf::IntRect(3*64, 2*48, 64, 48));
    _0_1_1_0_iso_tile.setOrigin(0, 32);

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

            sf::Vector2f tileposition(x1 - maincamera.getX(), y1 - maincamera.getY() - gameworld.tile(i,j).leftheight);

            switch(gameworld.tile(i,j).gettiletype()) {

                case (TILEFLAT):
                    flat_iso_tile.setPosition(tileposition);
                    mwindow.draw(flat_iso_tile);
                    break;

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

                //default:
                //   break;
            }
        }
    }

}
