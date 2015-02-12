#ifndef GRAPHICSMODULE_HPP_INCLUDED
#define GRAPHICSMODULE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "cameraview.hpp"
#include "basetile.hpp"

class graphicsmodule {
    sf::ConvexShape flat_iso_tile;
    sf::ConvexShape _0_1_1_1_iso_tile;
    sf::ConvexShape _1_0_1_1_iso_tile;
    sf::ConvexShape _1_1_0_1_iso_tile;
    sf::ConvexShape _1_1_1_0_iso_tile;
    sf::ConvexShape _0_1_1_0_iso_tile;
    sf::ConvexShape _0_0_1_1_iso_tile;
    sf::ConvexShape _1_0_0_1_iso_tile;
    sf::ConvexShape _1_1_0_0_iso_tile;

    void initializetile(sf::ConvexShape * gentile, tiletype typeoftile);
    void _setTilePosition(sf::ConvexShape * tileshape, const sf::Vector2f screenposition);

public:
    graphicsmodule();
    void renderworld(sf::RenderWindow &mwindow, const cameraview &maincamera, const world &gameworld);
};

#endif // GRAPHICSMODULE_HPP_INCLUDED
