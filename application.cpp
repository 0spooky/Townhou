#include <SFML/Graphics.hpp>

#include "stdlib.h"
#include "application.hpp"
#include "worldgen.hpp"
#include "world.hpp"
#include "cameraview.hpp"

application::application() : gameworld(generator.generateworld(512, 512)),
                             maincamera(0,-Y_WINDOW_DIMENSION/2),
                             mwindow(sf::VideoMode(X_WINDOW_DIMENSION, Y_WINDOW_DIMENSION), "Townhou", sf::Style::Close)
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
                switch (event.key.code) {

                    case (sf::Keyboard::Left):
                        leftpressed = true;
                        break;
                    case (sf::Keyboard::Right):
                        rightpressed = true;
                        break;
                    case (sf::Keyboard::Up):
                        uppressed = true;
                        break;
                    case (sf::Keyboard::Down):
                        downpressed = true;
                        break;
                    //default:
                    //    break;
                }

            }
            else if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code) {
                    case (sf::Keyboard::Left):
                        leftpressed = false;
                        break;
                    case (sf::Keyboard::Right):
                        rightpressed = false;
                        break;
                    case (sf::Keyboard::Up):
                        uppressed = false;
                        break;
                    case (sf::Keyboard::Down):
                        downpressed = false;
                        break;
                    case (sf::Keyboard::Add):
                        mgraphicsmodule.changeZoomLevel(1);
                        break;
                    case (sf::Keyboard::Subtract):
                        mgraphicsmodule.changeZoomLevel(-1);
                        break;
                    default:
                        break;
                }
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
