#ifndef GRAPHICSMODULE_HPP_INCLUDED
#define GRAPHICSMODULE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "cameraview.hpp"
#include "basetile.hpp"

class graphicsmodule {

    sf::Texture maptiletex;

    sf::Sprite flat_iso_tile;

    sf::Sprite _2_1_1_1_iso_tile;
    sf::Sprite _1_1_1_2_iso_tile;
    sf::Sprite _1_1_2_1_iso_tile;
    sf::Sprite _1_2_1_1_iso_tile;

    sf::Sprite _1_1_0_1_iso_tile;
    sf::Sprite _1_0_1_1_iso_tile;
    sf::Sprite _0_1_1_1_iso_tile;
    sf::Sprite _1_1_1_0_iso_tile;               //_LEFT_TOP_RIGHT_BOTTOM

    sf::Sprite _1_1_0_0_iso_tile;
    sf::Sprite _1_0_0_1_iso_tile;
    sf::Sprite _0_0_1_1_iso_tile;
    sf::Sprite _0_1_1_0_iso_tile;

    sf::Sprite _1_0_1_2_iso_tile;
    sf::Sprite _2_1_0_1_iso_tile;
    sf::Sprite _1_2_1_0_iso_tile;
    sf::Sprite _0_1_2_1_iso_tile;

    sf::Sprite _0_1_0_1_iso_tile;
    sf::Sprite _1_0_1_0_iso_tile;

public:
    graphicsmodule();
    void renderworld(sf::RenderWindow &mwindow, const cameraview &maincamera, const world &gameworld);
};

#endif // GRAPHICSMODULE_HPP_INCLUDED
