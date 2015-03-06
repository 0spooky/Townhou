#include <SFML/Graphics/RenderTarget.hpp>

#include "CameraView.hpp"
#include "Tilemap.hpp"
#include "World.hpp"

#include <iostream>

Tilemap::Tilemap(int _x_world_dimension, int _y_world_dimension)
{
    m_map_dimensions.x = 512;
    m_map_dimensions.y = 512;

    m_maptile_verts.setPrimitiveType(sf::Quads);
    m_maptile_verts.resize(m_map_dimensions.x * m_map_dimensions.y * 4);
}

void Tilemap::load(const std::string &_tileset, const World &_game_world, const CameraView &_camera)
{
    //Load the specified texture to the texture class
    m_maptile_tex.loadFromFile(_tileset);

    //Placeholder values

    //Used for linear transformation math
    int x1, y1;
    //Used to store TileType enum (from Basetile.hpp)
    int tile_type;
    //Used to store the texture coordinates for a given tile
    sf::Vector2i text_pos;
    //Used to store the pixel coordinates for a given tile
    sf::Vector2i vertex_pos;
    //Used to point to 4 values in an array (0, 1, 2, 3) of quads
    sf::Vertex* quad;

    // The x and y solutions to the inverse transformation matrix [x] [ 1/64 -1/32]
    //                                                            [y] [ 1/64  1/32]
    // With each term multiplied by the reciprocal of m_scale_level (by theorem of inverse matrices)
    int xTileTopLeft = static_cast<int>(_camera.getX()/64 - _camera.getY()/32);
    int yTileTopLeft = static_cast<int>(_camera.getX()/64 + _camera.getY()/32);

    // Precalculate the start and stop points
    // BEST FIX:
    // TODO CHANGE THIS TO MAKE IT SO THAT ONLY SEEN TILES ARE DRAWN INSTEAD OF OVERLAYED SQUARE?
    //      THIS WILL BE A DRASTIC CHANGE AND WILL REQUIRE USING THE FOR LOOPS.  IS IT WORTH IT? -> MAY IMPROVE PERFORMANCE
    // SECONDARY FIX:
    // TODO Fix height offset values ->WILL HURT PERFORMANCE ACTUALLY
    int xTileStart = std::max(static_cast<int>(xTileTopLeft - 22 - 12), 0);
    int xTileEnd   = std::min(m_map_dimensions.x, xTileTopLeft + 30);

    int yTileStart = std::max(yTileTopLeft, 0);
    int yTileEnd   = std::min(m_map_dimensions.y, static_cast<int>(yTileTopLeft + 22 + 30 + 12));

    for (int i = xTileStart; i < xTileEnd; i++){

        for (int j = yTileStart; j < yTileEnd; j++){
            //Determine texture type to use
            tile_type = _game_world.tile(i,j).getTileType();

            if (tile_type == 0)
                text_pos = {0,0};
            else
                text_pos = {((tile_type - 1) % 4) * 64,
                            ((tile_type - 1) / 4 + 1) * 48};

            //set up a pointer to 4 vertices given the coordinates given
            quad = &m_maptile_verts[((i - xTileStart) + (j - yTileStart) * m_map_dimensions.x) * 4];

            //Perform linear transformation to pixel domain
            x1 = 32 * ( i + j);
            y1 = 16 * (-i + j);

            vertex_pos = {x1 - _camera.getX(), y1 - _camera.getY() - 8 * _game_world.tile(i,j).referenceHeight()};

            quad[0].position  = sf::Vector2f(vertex_pos);
            quad[1].position  = sf::Vector2f(vertex_pos.x + 64, vertex_pos.y);
            quad[2].position  = sf::Vector2f(vertex_pos.x + 64, vertex_pos.y + 48);
            quad[3].position  = sf::Vector2f(vertex_pos.x     , vertex_pos.y + 48);

            quad[0].texCoords = sf::Vector2f(text_pos);
            quad[1].texCoords = sf::Vector2f(text_pos.x + 64, text_pos.y);
            quad[2].texCoords = sf::Vector2f(text_pos.x + 64, text_pos.y + 48);
            quad[3].texCoords = sf::Vector2f(text_pos.x,      text_pos.y + 48);

        }
    }
}

void Tilemap::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
    _states.texture = &m_maptile_tex;
    _target.draw(m_maptile_verts, _states);
}
