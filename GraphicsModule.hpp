#ifndef GRAPHICSMODULE_HPP_INCLUDED
#define GRAPHICSMODULE_HPP_INCLUDED
#include <SFML/Graphics.hpp>

#include "Basetile.hpp"
#include "CameraView.hpp"
#include "World.hpp"

class GraphicsModule {

    /*
     * Constant values
     */

    //The "normal" zoom level -> Used for calculations
    static const int BASIC_ZOOM_LEVEL = 3;

    //The height displacement between two vertices when one is higher (normal zoom)
    static const int HEIGHT_INCREMENTS = 8;

    //The maximum height possible for a basetile vertex
    static const int MAX_VERTEX_HEIGHT = 32;
    /*
     * Primitive variables
     */

    //The screen resolution
    int xWindowDimension;
    int yWindowDimension;

    //The number of tiles that can be fit on screen
    //  rounded down
    int m_x_tiles_fit_screen;
    int m_y_tiles_fit_screen;

    //A value ranging from 1 to 2*BASIC_ZOOM_LEVEL depicting how zoomed the graphics are
    int m_zoom_level;

    //Value calculated from m_zoom_level whenever m_zoom_level is changed
    float m_scale_level;

    /*
     * Class variables
     *
     * Basetile Sprites
     * SYNTAX: _LEFT_TOP_RIGHT_BOTTOM_iso_tile
     */

    //A Texture holding basic map tiles
    sf::Texture m_maptile_tex;

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

    CameraView m_main_camera;

    /*
     * Private functions
     */

    //Function to render the gameworld TODO: Push into update
    void _renderWorld(sf::RenderWindow &mwindow, const World &gameworld);
    //Function to alter zoom level TODO: Make private when update is finished
    void _changeZoomLevel(int delta);
    //A helper function which scales all basetile graphics
    void _scaleTiles();

public:
    //Constructor
    GraphicsModule(int _xWindowDimension, int _yWindowDimension);
    //Return the cameraview to manipulate from outside class
    CameraView& getMainCamera();
    //Updates all statuses of the graphics TODO: Make private when update is finished
    void update(sf::RenderWindow &mwindow, const World &gameworld);


};

#endif // GRAPHICSMODULE_HPP_INCLUDED
