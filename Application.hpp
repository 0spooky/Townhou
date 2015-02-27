#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "CameraView.hpp"
#include "GraphicsModule.hpp"
#include "World.hpp"
#include "WorldGenerator.hpp"

class Application {

    //The screen resolution.  TODO: Make this configurable
    static const int X_WINDOW_DIMENSION = 1920;
    static const int Y_WINDOW_DIMENSION = 960;

    //The game world and its generator
    WorldGenerator m_generator;
    World m_game_world;

    //The main display window
    //Put this above world generator to have the screen the first thing generated;  Might be useful later for load screens
    sf::RenderWindow m_window;

    //The graphics renderer
    GraphicsModule m_graphics_module;

    //Determine input states to update Input framework
    void _handleInput();

public:

    //Constructor
    Application();

    //Start everything
    void run();
    //End everything. TODO: Possible clean-up needed
    void close() {};

};

#endif // APPLICATION_HPP_INCLUDED
