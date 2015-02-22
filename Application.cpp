#include "stdlib.h"

#include <SFML/Graphics.hpp>

#include "Application.hpp"
#include "CameraView.hpp"
#include "WorldGenerator.hpp"
#include "World.hpp"

Application::Application() : m_game_world(m_generator.generateWorld(512, 512)),
                             m_window(sf::VideoMode(X_WINDOW_DIMENSION, Y_WINDOW_DIMENSION), "Townhou", sf::Style::Close),
                             m_graphics_module(X_WINDOW_DIMENSION, Y_WINDOW_DIMENSION)
{
    m_window.setFramerateLimit(120);
}

void Application::run() {

    //These are intended for seamless scrolling
    //TODO: Delegate to input class/function?
    bool    left_pressed  = false,
            right_pressed = false,
            up_pressed    = false,
            down_pressed  = false;

    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            switch (event.type) {
                case (sf::Event::Closed):
                    m_window.close();
                    break;

                case (sf::Event::KeyPressed):
                    switch (event.key.code) {

                        case (sf::Keyboard::Left):
                            left_pressed = true;
                            break;
                        case (sf::Keyboard::Right):
                            right_pressed = true;
                            break;
                        case (sf::Keyboard::Up):
                            up_pressed = true;
                            break;
                        case (sf::Keyboard::Down):
                            down_pressed = true;
                            break;
                        case (sf::Keyboard::Add):
                            m_graphics_module.changeZoomLevel(1);
                            break;
                        case (sf::Keyboard::Subtract):
                            m_graphics_module.changeZoomLevel(-1);
                            break;
                        default:
                            break;
                    }
                    break;

                case (sf::Event::KeyReleased):
                    switch (event.key.code) {
                        case (sf::Keyboard::Left):
                            left_pressed = false;
                            break;
                        case (sf::Keyboard::Right):
                            right_pressed = false;
                            break;
                        case (sf::Keyboard::Up):
                            up_pressed = false;
                            break;
                        case (sf::Keyboard::Down):
                            down_pressed = false;
                            break;
                        default:
                            break;
                    }
                    break;

                case (sf::Event::MouseMoved):
                    break;

                case (sf::Event::MouseWheelMoved):
                    m_graphics_module.changeZoomLevel(event.mouseWheel.delta);
                    break;

                default:
                    break;
            }
        }

        if (up_pressed || down_pressed || left_pressed || right_pressed)
            m_graphics_module.getMainCamera().changeView(up_pressed, down_pressed, left_pressed, right_pressed);

        m_window.clear();
        m_graphics_module.renderWorld(m_window, m_game_world);
        m_window.display();
    }

}
