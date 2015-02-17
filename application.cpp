#include <SFML/Graphics.hpp>

#include "stdlib.h"
#include "application.hpp"
#include "worldgen.hpp"
#include "world.hpp"
#include "cameraview.hpp"

application::application() : gameworld(generator.generateworld(512, 512)),
                             maincamera(0,-YWINDOWDIMENSION/2),
                             mwindow(sf::VideoMode(XWINDOWDIMENSION, YWINDOWDIMENSION), "Townhou", sf::Style::Close)
{
    mwindow.setFramerateLimit(120);
}

void application::run() {

    //srand (time(NULL));

    bool    leftpressed  = false,                                       //These are used for seamless scrolling
            rightpressed = false,                                       //
            uppressed    = false,                                       //
            downpressed  = false;                                       //

    //unsigned int zoom_level = 4;                                       //Primarily for rendering purposes;

    while (mwindow.isOpen())
    {
        sf::Event event;
        while (mwindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mwindow.close();
            else if (event.type == sf::Event::KeyPressed)
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
            else if (event.type == sf::Event::KeyReleased)
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
            else if (event.type == sf::Event::MouseMoved)
                ;
            else if (event.type == sf::Event::MouseWheelMoved)
            {
                mgraphicsmodule.changeZoomLevel(event.mouseWheel.delta);
            }
        }

        maincamera.changeview(uppressed, downpressed, leftpressed, rightpressed);

        mwindow.clear();
        mgraphicsmodule.renderworld(mwindow, maincamera, gameworld);
        mwindow.display();
    }

}
