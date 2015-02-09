#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>

class cameraview {

    sf::Vector2i viewpoint;

public:

    cameraview();
    cameraview(int x, int y);

    int getX() const {return viewpoint.x;}
    int getY() const {return viewpoint.y;}
    void changeview(bool up, bool down, bool left, bool right);
};

#endif // CAMERA_HPP_INCLUDED
