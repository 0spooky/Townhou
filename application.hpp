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

    sf::RenderWindow mwindow;

    worldgen generator;
    world gameworld;

    cameraview maincamera;

    graphicsmodule mgraphicsmodule;

public:

    application();

    void run();
    void close() {};

};

#endif // APPLICATION_HPP_INCLUDED
