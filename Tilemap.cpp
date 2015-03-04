#include <SFML/Graphics/RenderTarget.hpp>

#include "CameraView.hpp"
#include "Tilemap.hpp"
#include "World.hpp"

Tilemap::Tilemap(int _x_window_dimension, int _y_window_dimension)
{
    m_map_dimensions.x = _x_window_dimension;
    m_map_dimensions.y = _y_window_dimension;
}

void Tilemap::load(const std::string &_tileset, const World &_game_world, const CameraView &_camera)
{
    m_maptile_tex.loadFromFile(_tileset);

    m_maptile_verts.setPrimitiveType(sf::Quads);
    m_maptile_verts.resize(m_map_dimensions.x * m_map_dimensions.y * 4);

    int x1, y1;

    for (int i = 0; i < m_map_dimensions.x; i++){

            for (int j = 0; j < m_map_dimensions.y; j++){

                //Determine texture type to use
                int tile_type = _game_world.tile(i,j).getTileType();
                sf::Vector2i text_pos;

                if (tile_type == 0)
                    text_pos = {0,0};
                else
                    text_pos = {((tile_type - 1) % 4) * 64,
                                ((tile_type - 1) / 4) * 48};

                sf::Vertex* quad = &m_maptile_verts[(i + j * m_map_dimensions.x) * 4];

                x1 = 32 * (i + j);
                y1 = 16 * (i - j);

                quad[0].position  = sf::Vector2f(x1 - _camera.getX()     , y1 - _camera.getY() - 8 * _game_world.tile(i,j).referenceHeight() - 24);
                quad[1].position  = sf::Vector2f(x1 - _camera.getX() + 64, y1 - _camera.getY() - 8 * _game_world.tile(i,j).referenceHeight() - 24);
                quad[2].position  = sf::Vector2f(x1 - _camera.getX() + 64, y1 - _camera.getY() - 8 * _game_world.tile(i,j).referenceHeight() + 24);
                quad[3].position  = sf::Vector2f(x1 - _camera.getX()     , y1 - _camera.getY() - 8 * _game_world.tile(i,j).referenceHeight() + 24);

                quad[0].texCoords = sf::Vector2f(text_pos.x * 64, text_pos.y * 48);
                quad[1].texCoords = sf::Vector2f((text_pos.x + 1) * 64, text_pos.y * 48);
                quad[2].texCoords = sf::Vector2f((text_pos.x + 1) * 64, (text_pos.y + 1) * 48);
                quad[3].texCoords = sf::Vector2f(text_pos.x * 64, (text_pos.y + 1) * 48);

            }
    }
}

void Tilemap::draw(sf::RenderTarget &_target, sf::RenderStates _states) const
{
    _states.texture = &m_maptile_tex;
    _target.draw(m_maptile_verts, _states);
}
