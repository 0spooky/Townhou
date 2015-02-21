#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "worldgen.hpp"
#include "world.hpp"
#include "graphicsmodule.hpp"
#include "cameraview.hpp"

class application {

    //The screen resolution.  TODO: Make this configurable and passable to graphics module
    static const int X_WINDOW_DIMENSION = 1920;
    static const int Y_WINDOW_DIMENSION = 960;

    //The game world and its generator
    worldgen m_generator;
    world m_game_world;

    //The main display window
    sf::RenderWindow m_window;                   //Put this above world generator to have the screen the first thing generated;  Might be useful later for load screens

    //The graphics renderer
    graphicsmodule m_graphics_module;

public:

    //Constructor
    application();

    //Start everything
    void run();
    //End everything. TODO: Possible clean-up needed
    void close() {};

};

#endif // APPLICATION_HPP_INCLUDED
