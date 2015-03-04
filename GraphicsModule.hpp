#ifndef GRAPHICSMODULE_HPP_INCLUDED
#define GRAPHICSMODULE_HPP_INCLUDED
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Basetile.hpp"
#include "CameraView.hpp"
#include "Tilemap.hpp"
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
     */

    //A Texture holding basic map tiles
    sf::Texture m_maptile_tex;

    //The container for the standard isometric tiles used
    //the int key will be gotten from the basetile.hpp TileType
    std::unordered_map<int, sf::Sprite> m_base_iso_tiles;

    //The main camera view for the screen; used for calculations
    CameraView m_main_camera;

    //The VectorArray of tiles to be drawn (The whole world)
    Tilemap m_tilemap;

    /*
     * Private functions
     */

    //Function to render the gameworld (used by update)
    void _renderWorld(sf::RenderWindow &mwindow, const World &gameworld);
    //Function to draw specific tiles (used by _renderWorld)
    void _drawIsoTile(TileType _tile_ID, sf::RenderWindow &_target_window, const sf::Vector2f &_tile_position);
    //Function to alter zoom level (used by update)
    void _changeZoomLevel(int delta);
    //A helper function which scales all basetile graphics (used by _changeZoomLevel)
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
