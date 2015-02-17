#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>

class cameraview {

    //The speed which the camera scrolls.  TODO: Should this be configurable?
    static const int SCROLL_SPEED = 12;

    //The camera's top left corner with respect to the standard map
    sf::Vector2i viewpoint;

public:

    //Constructors
    cameraview();
    cameraview(int x, int y);

    //Functions to return the camera's position
    int getX() const {return viewpoint.x;}
    int getY() const {return viewpoint.y;}

    //A function to change the camera's position
    void changeview(bool up, bool down, bool left, bool right);
};

#endif // CAMERA_HPP_INCLUDED
