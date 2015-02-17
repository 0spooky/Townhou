#ifndef GRAPHICSMODULE_HPP_INCLUDED
#define GRAPHICSMODULE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "cameraview.hpp"
#include "basetile.hpp"

class graphicsmodule {

    //The "normal" zoom level -> Used for calculations
    static const int BASIC_ZOOM_LEVEL = 3;

    //A Texture holding basic map tiles
    sf::Texture maptiletex;

    //The Sprite of the flat isometric tile
    sf::Sprite flat_iso_tile;

    //The Sprites of the single-high isometric tiles
    sf::Sprite _2_1_1_1_iso_tile;   //_LEFT_TOP_RIGHT_BOTTOM
    sf::Sprite _1_1_1_2_iso_tile;
    sf::Sprite _1_1_2_1_iso_tile;
    sf::Sprite _1_2_1_1_iso_tile;

    //The Sprites of the normal-slope isometric tiles
    sf::Sprite _1_1_0_0_iso_tile;
    sf::Sprite _1_0_0_1_iso_tile;
    sf::Sprite _0_0_1_1_iso_tile;
    sf::Sprite _0_1_1_0_iso_tile;

    //The Sprites of the single-low isometric tiles
    sf::Sprite _1_1_0_1_iso_tile;
    sf::Sprite _1_0_1_1_iso_tile;
    sf::Sprite _0_1_1_1_iso_tile;
    sf::Sprite _1_1_1_0_iso_tile;

    //The Sprites of the steep-slant isometric tiles
    sf::Sprite _1_0_1_2_iso_tile;
    sf::Sprite _2_1_0_1_iso_tile;
    sf::Sprite _1_2_1_0_iso_tile;
    sf::Sprite _0_1_2_1_iso_tile;

    //The Sprites of the split-valley isometric tiles
    sf::Sprite _0_1_0_1_iso_tile;
    sf::Sprite _1_0_1_0_iso_tile;

    //A value ranging from 1 to 2*BASIC_ZOOM_LEVEL depicting how zoomed the graphics are
    int zoom_level;

    //Value calculated from zoom_level whenever zoom_level is changed
    float scale_level;

    //A helper function which scales all basetile graphics
    void _scaleTiles();

public:
    //Constructor
    graphicsmodule();
    //Function to render the gameworld
    void renderworld(sf::RenderWindow &mwindow, const cameraview &maincamera, const world &gameworld);
    //Function to alter zoom level
    void changeZoomLevel(int delta);
};

#endif // GRAPHICSMODULE_HPP_INCLUDED
