#include <SFML/Graphics/RenderTarget.hpp>

#include "CameraView.hpp"
#include "Tilemap.hpp"
#include "World.hpp"

#include <iostream>

Tilemap::Tilemap(int _x_world_dimension, int _y_world_dimension)
{
    m_map_dimensions.x = 1024;
    m_map_dimensions.y = 1024;

    m_maptile_verts.setPrimitiveType(sf::Quads);
    m_maptile_verts.resize(1000*1000);
}

void Tilemap::load(const std::string &_tileset, const World &_game_world, const CameraView &_camera)
{
    //Load the specified texture to the texture class
    m_maptile_tex.loadFromFile(_tileset);

    //Placeholder values

    // Used for calculating transformation matrices of x any y values
    int x1, y1;
    //Used to store TileType enum (from Basetile.hpp)
    int tile_type;
    //Used to store the texture coordinates for a given tile
    sf::Vector2i text_pos;
    //Used to store the pixel coordinates for a given tile
    sf::Vector2i vertex_pos;
    //Used to point to 4 values in an array (0, 1, 2, 3) of quads
    sf::Vertex* quad;
    //
    sf::Vector2i tilesFitOnscreen(_camera.getResolution().x / static_cast<int>(64 * _camera.getScale()), _camera.getResolution().y / static_cast<int>(32 * _camera.getScale()));

    // The "x" size of the game map
    // The "y" size of the game map;
    // Will probably take this out eventually for optimization or something
    int   x_size = _game_world.getXsize(),
          y_size = _game_world.getYsize();

    // The x and y solutions to the inverse transformation matrix [x] [ 1/64 -1/32]
    //                                                            [y] [ 1/64  1/32]
    // With each term multiplied by the reciprocal of _camera.getScale() (by theorem of inverse matrices)
    int xTileTopLeft = static_cast<int>((_camera.getX()/64 - _camera.getY()/32) / _camera.getScale());
    int yTileTopLeft = static_cast<int>((_camera.getX()/64 + _camera.getY()/32) / _camera.getScale());

    // Precalculate the start and stop points
    // BEST FIX:
    // TODO CHANGE THIS TO MAKE IT SO THAT ONLY SEEN TILES ARE DRAWN INSTEAD OF OVERLAYED SQUARE?
    //      THIS WILL BE A DRASTIC CHANGE AND WILL REQUIRE USING THE FOR LOOPS.  IS IT WORTH IT? -> MAY IMPROVE PERFORMANCE
    // SECONDARY FIX:
    // TODO Fix height offset values ->WILL HURT PERFORMANCE ACTUALLY
    int xTileStart = std::max(static_cast<int>(xTileTopLeft - tilesFitOnscreen.y - 4), 0);
    int xTileEnd   = std::min(x_size, xTileTopLeft + tilesFitOnscreen.x);

    int yTileStart = std::max(yTileTopLeft, 0);
    int yTileEnd   = std::min(y_size, static_cast<int>(yTileTopLeft + tilesFitOnscreen.y + tilesFitOnscreen.x + 6));

    //Populate VertexArray with tiles from the world
    for (int i = xTileStart; i < xTileEnd; i++){

        for (int j = yTileStart; j < yTileEnd; j++){
            //Determine texture type to use
            tile_type = _game_world.tile(i,j).getTileType();

            if (tile_type == 0)
                text_pos = {0,0};
            else
                text_pos = {((tile_type - 1) % 4)     * static_cast<int> (64 * _camera.getScale()),
                            ((tile_type - 1) / 4 + 1) * static_cast<int> (48 * _camera.getScale())};

            //set up a pointer to 4 vertices given the coordinates given
            quad = &m_maptile_verts[((i - xTileStart) + (j - yTileStart) * (xTileEnd - xTileStart)) * 4];

            // The x and y solutions to the transformation matrix [x] [ 32      32 ]
            //                                                    [y] [-16      16 ]
            x1 =                 (_camera.getScale() * 32) * ( i + j);
            y1 = static_cast<int>(_camera.getScale() * 16) * (-i + j);

            //The exact position of the referenced basetile, accounting for transformation, camera poeision, and tile height
            vertex_pos = {x1 - _camera.getX(), static_cast<int>(y1 - _camera.getY() - 8 * _game_world.tile(i,j).referenceHeight() * _camera.getScale())};

            quad[0].position  = sf::Vector2f(vertex_pos);
            quad[1].position  = sf::Vector2f(vertex_pos.x + 64 * _camera.getScale(), vertex_pos.y);
            quad[2].position  = sf::Vector2f(vertex_pos.x + 64 * _camera.getScale(), vertex_pos.y + 48 * _camera.getScale());
            quad[3].position  = sf::Vector2f(vertex_pos.x     , vertex_pos.y + 48 * _camera.getScale());

            quad[0].texCoords = sf::Vector2f(text_pos);
            quad[1].texCoords = sf::Vector2f(text_pos.x + 64 * _camera.getScale(), text_pos.y);
            quad[2].texCoords = sf::Vector2f(text_pos.x + 64 * _camera.getScale(), text_pos.y + 48 * _camera.getScale());
            quad[3].texCoords = sf::Vector2f(text_pos.x,      text_pos.y + 48 * _camera.getScale());

        }
    }
}


void Tilemap::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
    _states.texture = &m_maptile_tex;
    _target.draw(m_maptile_verts, _states);
}

//TODO: Use better numbers i.e. actually calculate an algorithm
void Tilemap::zoom(int _zoom_level)
{
    m_maptile_verts.clear();

    switch(_zoom_level) {
    case 1:
        m_maptile_verts.resize(244*246*4);
        break;
    case 2:
        m_maptile_verts.resize(124*126*4);
        break;
    case 3:
        m_maptile_verts.resize(64*66*4);
        break;
    case 4:
        m_maptile_verts.resize(34*36*4);
        break;
    case 5:
        m_maptile_verts.resize(19*21*4);
        break;
    default:
        m_maptile_verts.resize(64*66*4);
        break;

    }
}
