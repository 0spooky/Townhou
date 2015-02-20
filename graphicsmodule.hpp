#ifndef GRAPHICSMODULE_HPP_INCLUDED
#define GRAPHICSMODULE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "cameraview.hpp"
#include "basetile.hpp"

class graphicsmodule {

    /*
     * Constant values
     */

    //The "normal" zoom level -> Used for calculations
    static const int BASIC_ZOOM_LEVEL = 3;

    //The height displacement between two vertices when one is higher (normal zoom)
    static const int HEIGHT_INCREMENTS = 8;

    //The screen resolution.  TODO: Make this configurable and acquirable from application
    static const int X_WINDOW_DIMENSION = 1920;
    static const int Y_WINDOW_DIMENSION = 1080;

    /*
     * Primitive variables
     */

    //The screen resolution
    //int xWindowDimension
    //int yWindowDimension

    //The number of tiles that can be fit on screen
    //  rounded down
    int xTilesFitScreen;
    int yTilesFitScreen;

    //A value ranging from 1 to 2*BASIC_ZOOM_LEVEL depicting how zoomed the graphics are
    int zoom_level;

    //Value calculated from zoom_level whenever zoom_level is changed
    float scale_level;

    /*
     * Class variables
     *
     * Basetile Sprites
     * SYNTAX: _LEFT_TOP_RIGHT_BOTTOM_iso_tile
     */

    //A Texture holding basic map tiles
    sf::Texture maptiletex;

    //The Sprite of the flat isometric tile
    sf::Sprite flat_iso_tile;

    //The Sprites of the single-high isometric tiles
    sf::Sprite  _2_1_1_1_iso_tile, _1_1_1_2_iso_tile, _1_1_2_1_iso_tile, _1_2_1_1_iso_tile;

    //The Sprites of the normal-slope isometric tiles
    sf::Sprite  _1_1_0_0_iso_tile, _1_0_0_1_iso_tile, _0_0_1_1_iso_tile, _0_1_1_0_iso_tile;

    //The Sprites of the single-low isometric tiles
    sf::Sprite  _1_1_0_1_iso_tile, _1_0_1_1_iso_tile, _0_1_1_1_iso_tile, _1_1_1_0_iso_tile;

    //The Sprites of the steep-slant isometric tiles
    sf::Sprite  _1_0_1_2_iso_tile, _2_1_0_1_iso_tile, _1_2_1_0_iso_tile, _0_1_2_1_iso_tile;

    //The Sprites of the split-valley isometric tiles
    sf::Sprite  _0_1_0_1_iso_tile, _1_0_1_0_iso_tile;

    /*
     * Private functions
     */

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
