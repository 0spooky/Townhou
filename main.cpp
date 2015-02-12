#include <SFML/Graphics.hpp>
#include <cmath>
#include <limits>
//#include <vector>                                         //Apparently included in <SFML/Graphics.hpp>
#include <time.h> //TESTING
#include "Noisegen.hpp"
#include "basetile.hpp"
#include "cameraview.hpp"
#include "world.hpp"
#include "worldgen.hpp"

void setTilePosition(sf::ConvexShape * tileshape, const int x1, const int y1, const cameraview &maincamera, const short leftheight);

void drawtilemap(sf::RenderWindow &window, const cameraview &maincamera, const world &gameworld);     //Draws a map of basetiles given the data, the window, and viewpoint

int main()
{
    //testing
    srand (time(NULL));

    const int XWINDOWDIMENSION = 1920;
    const int YWINDOWDIMENSION = 960;

    worldgen generator;
    world gameworld = generator.generateworld(512, 512);

    sf::RenderWindow window(sf::VideoMode(XWINDOWDIMENSION, YWINDOWDIMENSION), "Townhou", sf::Style::Close);
    window.setFramerateLimit(120);

    //sf::Vector2f viewpoint(960.f, -480.f);                            //The normal starting viewpoint
    cameraview maincamera(0,-YWINDOWDIMENSION/2);

    bool    leftpressed  = false,                                       //These are used for seamless scrolling
            rightpressed = false,                                       //
            uppressed    = false,                                       //
            downpressed  = false;                                       //

    //unsigned char zoom_level 4;                                       //Primarily for rendering purposes; currently unused

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                    leftpressed = true;
                if (event.key.code == sf::Keyboard::Right)
                    rightpressed = true;
                if (event.key.code == sf::Keyboard::Up)
                    uppressed = true;
                if (event.key.code == sf::Keyboard::Down)
                    downpressed = true;
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Left)
                    leftpressed = false;
                if (event.key.code == sf::Keyboard::Right)
                    rightpressed = false;
                if (event.key.code == sf::Keyboard::Up)
                    uppressed = false;
                if (event.key.code == sf::Keyboard::Down)
                    downpressed = false;
            }
        }

        maincamera.changeview(uppressed, downpressed, leftpressed, rightpressed);

        window.clear();
        drawtilemap(window, maincamera, gameworld);
        window.display();
    }

    return 0;
}

//A function to draw the entirety of a vector of vectors of basetiles on a window given a viewpoint
//


void drawtilemap(sf::RenderWindow &window, const cameraview &maincamera, const world &gameworld)
{
    sf::ConvexShape flat_iso_tile(4);                                   // This code is to draw an openGL SFML isometric flat square.
    flat_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));                  // If you use sprites, remove it eventually
    flat_iso_tile.setPoint(1, sf::Vector2f(32.f, 16.f));                // For some reason, I have these all drawing counterclockwise
    flat_iso_tile.setPoint(2, sf::Vector2f(64.f, 0.f));                 // even though all measurements are clockwise. This should be fixed
    flat_iso_tile.setPoint(3, sf::Vector2f(32.f, -16.f));               //
    flat_iso_tile.setOutlineThickness(1);
    flat_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _0_1_1_1_iso_tile(4);                               // _X_X_X_X = _Left_Bottom_Right_Top
    _0_1_1_1_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _0_1_1_1_iso_tile.setPoint(1, sf::Vector2f(32.f, 0.f));
    _0_1_1_1_iso_tile.setPoint(2, sf::Vector2f(64.f, -16.f));
    _0_1_1_1_iso_tile.setPoint(3, sf::Vector2f(32.f, -32.f));
    _0_1_1_1_iso_tile.setOutlineThickness(1);
    _0_1_1_1_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _1_0_1_1_iso_tile(4);
    _1_0_1_1_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _1_0_1_1_iso_tile.setPoint(1, sf::Vector2f(32.f, 16.f));
    _1_0_1_1_iso_tile.setPoint(2, sf::Vector2f(64.f, 0.f));
    _1_0_1_1_iso_tile.setPoint(3, sf::Vector2f(32.f, 0.f));
    _1_0_1_1_iso_tile.setOutlineThickness(1);
    _1_0_1_1_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _1_1_0_1_iso_tile(4);
    _1_1_0_1_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _1_1_0_1_iso_tile.setPoint(1, sf::Vector2f(32.f, 16.f));
    _1_1_0_1_iso_tile.setPoint(2, sf::Vector2f(64.f, 15.f));
    _1_1_0_1_iso_tile.setPoint(3, sf::Vector2f(32.f, -16.f));
    _1_1_0_1_iso_tile.setOutlineThickness(1);
    _1_1_0_1_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _1_1_1_0_iso_tile(4);
    _1_1_1_0_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _1_1_1_0_iso_tile.setPoint(1, sf::Vector2f(32.f, 32.f));
    _1_1_1_0_iso_tile.setPoint(2, sf::Vector2f(64.f, 0.f));
    _1_1_1_0_iso_tile.setPoint(3, sf::Vector2f(32.f, -16.f));
    _1_1_1_0_iso_tile.setOutlineThickness(1);
    _1_1_1_0_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _0_1_1_0_iso_tile(4);
    _0_1_1_0_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _0_1_1_0_iso_tile.setPoint(1, sf::Vector2f(32.f, 16.f));
    _0_1_1_0_iso_tile.setPoint(2, sf::Vector2f(64.f, -16.f));
    _0_1_1_0_iso_tile.setPoint(3, sf::Vector2f(32.f, -32.f));
    _0_1_1_0_iso_tile.setOutlineThickness(1);
    _0_1_1_0_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _0_0_1_1_iso_tile(4);
    _0_0_1_1_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _0_0_1_1_iso_tile.setPoint(1, sf::Vector2f(32.f, 0.f));
    _0_0_1_1_iso_tile.setPoint(2, sf::Vector2f(64.f, -16.f));
    _0_0_1_1_iso_tile.setPoint(3, sf::Vector2f(32.f, -16.f));
    _0_0_1_1_iso_tile.setOutlineThickness(1);
    _0_0_1_1_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _1_0_0_1_iso_tile(4);
    _1_0_0_1_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _1_0_0_1_iso_tile.setPoint(1, sf::Vector2f(32.f, 16.f));
    _1_0_0_1_iso_tile.setPoint(2, sf::Vector2f(64.f, 16.f));
    _1_0_0_1_iso_tile.setPoint(3, sf::Vector2f(32.f, 0.f));
    _1_0_0_1_iso_tile.setOutlineThickness(1);
    _1_0_0_1_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _1_1_0_0_iso_tile(4);
    _1_1_0_0_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _1_1_0_0_iso_tile.setPoint(1, sf::Vector2f(32.f, 32.f));
    _1_1_0_0_iso_tile.setPoint(2, sf::Vector2f(64.f, 16.f));
    _1_1_0_0_iso_tile.setPoint(3, sf::Vector2f(32.f, -16.f));
    _1_1_0_0_iso_tile.setOutlineThickness(1);
    _1_1_0_0_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

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

            if (gameworld.tile(i,j).gettiletype() == TILEFLAT)
            {
                flat_iso_tile.setFillColor(sf::Color(std::min(gameworld.tile(i,j).topheight/2.f, 255.f), std::min(gameworld.tile(i,j).rightheight/2.f, 255.f), std::min(gameworld.tile(i,j).botheight/2.f, 255.f), 255));
                flat_iso_tile.setPosition(sf::Vector2f(x1 - maincamera.getX(), y1 - maincamera.getY() - gameworld.tile(i,j).leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(flat_iso_tile);
            }
            else if (gameworld.tile(i,j).gettiletype() == TILE0111)
            {
                _0_1_1_1_iso_tile.setFillColor(sf::Color(std::min(gameworld.tile(i,j).topheight/2.f, 255.f), std::min(gameworld.tile(i,j).rightheight/2.f, 255.f), std::min(gameworld.tile(i,j).botheight/2.f, 255.f), 255));
                _0_1_1_1_iso_tile.setPosition(sf::Vector2f(x1 - maincamera.getX(), y1 - maincamera.getY() - gameworld.tile(i,j).leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_0_1_1_1_iso_tile);
            }
            else if (gameworld.tile(i,j).gettiletype() == TILE1011)
            {
                _1_0_1_1_iso_tile.setFillColor(sf::Color(std::min(gameworld.tile(i,j).topheight/2.f, 255.f), std::min(gameworld.tile(i,j).rightheight/2.f, 255.f), std::min(gameworld.tile(i,j).botheight/2.f, 255.f), 255));
                _1_0_1_1_iso_tile.setPosition(sf::Vector2f(x1 - maincamera.getX(), y1 - maincamera.getY() - gameworld.tile(i,j).leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_1_0_1_1_iso_tile);
            }
            else if (gameworld.tile(i,j).gettiletype() == TILE1101)
            {
                _1_1_0_1_iso_tile.setFillColor(sf::Color(std::min(gameworld.tile(i,j).topheight/2.f, 255.f), std::min(gameworld.tile(i,j).rightheight/2.f, 255.f), std::min(gameworld.tile(i,j).botheight/2.f, 255.f), 255));
                _1_1_0_1_iso_tile.setPosition(sf::Vector2f(x1 - maincamera.getX(), y1 - maincamera.getY() - gameworld.tile(i,j).leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_1_1_0_1_iso_tile);
            }
            else if (gameworld.tile(i,j).gettiletype() == TILE1110)
            {
                _1_1_1_0_iso_tile.setFillColor(sf::Color(std::min(gameworld.tile(i,j).topheight/2.f, 255.f), std::min(gameworld.tile(i,j).rightheight/2.f, 255.f), std::min(gameworld.tile(i,j).botheight/2.f, 255.f), 255));
                _1_1_1_0_iso_tile.setPosition(sf::Vector2f(x1 - maincamera.getX(), y1 - maincamera.getY() - gameworld.tile(i,j).leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_1_1_1_0_iso_tile);
            }
            else if (gameworld.tile(i,j).gettiletype() == TILE0110)
            {
                _0_1_1_0_iso_tile.setFillColor(sf::Color(gameworld.tile(i,j).topheight/2.f, 0, 0, 255));
                _0_1_1_0_iso_tile.setPosition(sf::Vector2f(x1 - maincamera.getX(), y1 - maincamera.getY() - gameworld.tile(i,j).leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_0_1_1_0_iso_tile);
            }
            else if (gameworld.tile(i,j).gettiletype() == TILE0011)
            {
                _0_0_1_1_iso_tile.setFillColor(sf::Color(gameworld.tile(i,j).topheight/2.f, 0, 0, 255));
                _0_0_1_1_iso_tile.setPosition(sf::Vector2f(x1 - maincamera.getX(), y1 - maincamera.getY() - gameworld.tile(i,j).leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_0_0_1_1_iso_tile);
            }
            else if (gameworld.tile(i,j).gettiletype() == TILE1001)
            {
                _1_0_0_1_iso_tile.setFillColor(sf::Color(gameworld.tile(i,j).topheight/2.f, 0, 0, 255));
                _1_0_0_1_iso_tile.setPosition(sf::Vector2f(x1 - maincamera.getX(), y1 - maincamera.getY() - gameworld.tile(i,j).leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_1_0_0_1_iso_tile);
            }
            else if (gameworld.tile(i,j).gettiletype() == TILE1100)
            {
                _1_1_0_0_iso_tile.setFillColor(sf::Color(gameworld.tile(i,j).topheight/2.f, 0, 0, 255));
                //_1_1_0_0_iso_tile.setPosition(sf::Vector2f(x1 - maincamera.getX(), y1 - maincamera.getY() - gameworld.tile(i,j).leftheight));        //Set the new position of the template tile offset by the viewpoint
                setTilePosition(&_1_1_0_0_iso_tile, x1, y1, maincamera, gameworld.tile(i,j).leftheight);
                window.draw(_1_1_0_0_iso_tile);
            }
        }
    }
}

void setTilePosition(sf::ConvexShape * tileshape, const int x1, const int y1, const cameraview &maincamera, const short leftheight)
{
    tileshape->setPosition(sf::Vector2f(x1 - maincamera.getX(), y1 - maincamera.getY() - leftheight));
}

