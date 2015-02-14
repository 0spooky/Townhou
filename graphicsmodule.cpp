#include "graphicsmodule.hpp"
#include "world.hpp"
#include "cameraview.hpp"
#include "basetile.hpp"

graphicsmodule::graphicsmodule() {

    initializetile(&flat_iso_tile,     TILEFLAT);
    initializetile(&_0_1_1_1_iso_tile, TILE0111);
    initializetile(&_1_0_1_1_iso_tile, TILE1011);
    initializetile(&_1_1_0_1_iso_tile, TILE1101);
    initializetile(&_1_1_1_0_iso_tile, TILE1110);
    initializetile(&_0_1_1_0_iso_tile, TILE0110);
    initializetile(&_0_0_1_1_iso_tile, TILE0011);
    initializetile(&_1_0_0_1_iso_tile, TILE1001);
    initializetile(&_1_1_0_0_iso_tile, TILE1100);
}

void graphicsmodule::initializetile(sf::ConvexShape * gentile, tiletype typeoftile) {
    gentile->setPointCount(4);
    gentile->setPoint(0, sf::Vector2f(0.f, 0.f));

    switch(typeoftile) {
        case (TILEFLAT):
            gentile->setPoint(1, sf::Vector2f(32.f, 16.f));                 // If you use sprites, remove it eventually
            gentile->setPoint(2, sf::Vector2f(64.f, 0.f));                  // For some reason, I have these all drawing counterclockwise
            gentile->setPoint(3, sf::Vector2f(32.f, -16.f));                // even though all measurements are clockwise. This should be fixed
            break;
        case (TILE0111):
            gentile->setPoint(1, sf::Vector2f(32.f, 0.f));
            gentile->setPoint(2, sf::Vector2f(64.f, -16.f));
            gentile->setPoint(3, sf::Vector2f(32.f, -32.f));
            break;
        case (TILE1011):
            gentile->setPoint(1, sf::Vector2f(32.f, 16.f));
            gentile->setPoint(2, sf::Vector2f(64.f, 0.f));
            gentile->setPoint(3, sf::Vector2f(32.f, 0.f));
            break;
        case (TILE1101):
            gentile->setPoint(1, sf::Vector2f(32.f, 16.f));
            gentile->setPoint(2, sf::Vector2f(64.f, 16.f));
            gentile->setPoint(3, sf::Vector2f(32.f, -16.f));
            break;
        case (TILE1110):
            gentile->setPoint(1, sf::Vector2f(32.f, 32.f));
            gentile->setPoint(2, sf::Vector2f(64.f, 0.f));
            gentile->setPoint(3, sf::Vector2f(32.f, -16.f));
            break;
        case (TILE0110):
            gentile->setPoint(1, sf::Vector2f(32.f, 16.f));
            gentile->setPoint(2, sf::Vector2f(64.f, -16.f));
            gentile->setPoint(3, sf::Vector2f(32.f, -32.f));
            break;
        case (TILE0011):
            gentile->setPoint(1, sf::Vector2f(32.f, 0.f));
            gentile->setPoint(2, sf::Vector2f(64.f, -16.f));
            gentile->setPoint(3, sf::Vector2f(32.f, -16.f));
            break;
        case (TILE1001):
            gentile->setPoint(1, sf::Vector2f(32.f, 16.f));
            gentile->setPoint(2, sf::Vector2f(64.f, 16.f));
            gentile->setPoint(3, sf::Vector2f(32.f, 0.f));
            break;
        case (TILE1100):
            gentile->setPoint(1, sf::Vector2f(32.f, 32.f));
            gentile->setPoint(2, sf::Vector2f(64.f, 16.f));
            gentile->setPoint(3, sf::Vector2f(32.f, -16.f));
            break;
    }
    gentile->setOutlineThickness(1);
    gentile->setOutlineColor(sf::Color(255,255,255,128));

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
                    flat_iso_tile.setFillColor(sf::Color(std::min(gameworld.tile(i,j).topheight/2.f, 255.f), std::min(gameworld.tile(i,j).rightheight/2.f, 255.f), std::min(gameworld.tile(i,j).botheight/2.f, 255.f), 255));
                    _setTilePosition(&flat_iso_tile, tileposition);
                    mwindow.draw(flat_iso_tile);
                    break;

                case (TILE0111):
                    _0_1_1_1_iso_tile.setFillColor(sf::Color(std::min(gameworld.tile(i,j).topheight/2.f, 255.f), std::min(gameworld.tile(i,j).rightheight/2.f, 255.f), std::min(gameworld.tile(i,j).botheight/2.f, 255.f), 255));
                    _setTilePosition(&_0_1_1_1_iso_tile, tileposition);
                    mwindow.draw(_0_1_1_1_iso_tile);
                    break;

                case (TILE1011):
                    _1_0_1_1_iso_tile.setFillColor(sf::Color(std::min(gameworld.tile(i,j).topheight/2.f, 255.f), std::min(gameworld.tile(i,j).rightheight/2.f, 255.f), std::min(gameworld.tile(i,j).botheight/2.f, 255.f), 255));
                    _setTilePosition(&_1_0_1_1_iso_tile, tileposition);
                    mwindow.draw(_1_0_1_1_iso_tile);
                    break;

                case (TILE1101):
                    _1_1_0_1_iso_tile.setFillColor(sf::Color(std::min(gameworld.tile(i,j).topheight/2.f, 255.f), std::min(gameworld.tile(i,j).rightheight/2.f, 255.f), std::min(gameworld.tile(i,j).botheight/2.f, 255.f), 255));
                    _setTilePosition(&_1_1_0_1_iso_tile, tileposition);
                    mwindow.draw(_1_1_0_1_iso_tile);
                    break;

                case (TILE1110):
                    _1_1_1_0_iso_tile.setFillColor(sf::Color(std::min(gameworld.tile(i,j).topheight/2.f, 255.f), std::min(gameworld.tile(i,j).rightheight/2.f, 255.f), std::min(gameworld.tile(i,j).botheight/2.f, 255.f), 255));
                    _setTilePosition(&_1_1_1_0_iso_tile, tileposition);
                    mwindow.draw(_1_1_1_0_iso_tile);
                    break;

                case (TILE0110):
                    _0_1_1_0_iso_tile.setFillColor(sf::Color(gameworld.tile(i,j).topheight/2.f, 0, 0, 255));
                    _setTilePosition(&_0_1_1_0_iso_tile, tileposition);
                    mwindow.draw(_0_1_1_0_iso_tile);
                    break;

                case (TILE0011):
                    _0_0_1_1_iso_tile.setFillColor(sf::Color(gameworld.tile(i,j).topheight/2.f, 0, 0, 255));
                    _setTilePosition(&_0_0_1_1_iso_tile, tileposition);
                    mwindow.draw(_0_0_1_1_iso_tile);
                    break;

                case (TILE1001):
                    _1_0_0_1_iso_tile.setFillColor(sf::Color(gameworld.tile(i,j).topheight/2.f, 0, 0, 255));
                    _setTilePosition(&_1_0_0_1_iso_tile, tileposition);
                    mwindow.draw(_1_0_0_1_iso_tile);
                    break;

                case (TILE1100):
                    _1_1_0_0_iso_tile.setFillColor(sf::Color(gameworld.tile(i,j).topheight/2.f, 0, 0, 255));
                    _setTilePosition(&_1_1_0_0_iso_tile, tileposition);
                    mwindow.draw(_1_1_0_0_iso_tile);
                    break;

                //default:
                //   break;
            }
        }
    }

}

void graphicsmodule::_setTilePosition(sf::ConvexShape * tileshape, const sf::Vector2f screenposition) {
    tileshape->setPosition(screenposition);
}
