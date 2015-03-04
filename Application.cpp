#include "stdlib.h"

#include <SFML/Graphics.hpp>

#include "Application.hpp"
#include "CameraView.hpp"
#include "Input.hpp"
#include "WorldGenerator.hpp"
#include "World.hpp"

Application::Application() : m_game_world(m_generator.generateWorld(X_WORLD_DIMENSION, Y_WORLD_DIMENSION)),
                             m_window(sf::VideoMode(X_WINDOW_DIMENSION, Y_WINDOW_DIMENSION), "Townhou", sf::Style::Close),
                             m_graphics_module(X_WINDOW_DIMENSION, Y_WINDOW_DIMENSION)
{
    m_window.setFramerateLimit(MAX_FPS);
}

void Application::_handleInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (Input::parseInput(event, m_window) == false)
            m_window.close();
    }
}

void Application::run()
{
    while (m_window.isOpen())
    {
        _handleInput();

        m_window.clear();
        m_graphics_module.update(m_window, m_game_world);
        m_window.display();

    }
}
