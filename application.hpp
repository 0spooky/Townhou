#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "worldgen.hpp"
#include "world.hpp"
#include "graphicsmodule.hpp"
#include "cameraview.hpp"

class application {

    static const int XWINDOWDIMENSION = 1920;
    static const int YWINDOWDIMENSION = 1080;

    worldgen generator;
    world gameworld;

    cameraview maincamera;

    sf::RenderWindow mwindow;                   //Put this above world generator to have the screen the first thing generated;  Might be useful later for load screens

    graphicsmodule mgraphicsmodule;

public:

    application();

    void run();
    void close() {};

};

#endif // APPLICATION_HPP_INCLUDED
