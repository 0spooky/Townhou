#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "WorldGenerator.hpp"
#include "World.hpp"
#include "GraphicsModule.hpp"
#include "CameraView.hpp"

class Application {

    //The screen resolution.  TODO: Make this configurable and passable to graphics module
    static const int X_WINDOW_DIMENSION = 1920;
    static const int Y_WINDOW_DIMENSION = 960;

    //The game world and its generator
    WorldGenerator m_generator;
    World m_game_world;

    //The main display window
    sf::RenderWindow m_window;                   //Put this above world generator to have the screen the first thing generated;  Might be useful later for load screens

    //The graphics renderer
    GraphicsModule m_graphics_module;

public:

    //Constructor
    Application();

    //Start everything
    void run();
    //End everything. TODO: Possible clean-up needed
    void close() {};

};

#endif // APPLICATION_HPP_INCLUDED
