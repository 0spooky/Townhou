#ifndef TILEMAP_HPP_INCLUDED
#define TILEMAP_HPP_INCLUDED

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "CameraView.hpp"
#include "World.hpp"

class Tilemap : public sf::Drawable {

    sf::Texture m_maptile_tex;
    sf::VertexArray m_maptile_verts;

    sf::Vector2i m_map_dimensions;

    void draw(sf::RenderTarget &_target, sf::RenderStates _states) const;

public:
    Tilemap(int _x_world_dimension, int _y_world_dimension);
    void load(const std::string &tileset, const World &gameworld, const CameraView &_camera);

};

#endif // TILEMAP_HPP_INCLUDED
