#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>

class cameraview {

    //The screen resolution.  TODO: Make this configurable and acquirable from application/graphics module
    static const int X_WINDOW_DIMENSION = 1920;
    static const int Y_WINDOW_DIMENSION = 960;

    //The speed which the camera scrolls.  TODO: Should this be configurable?
    static const int SCROLL_SPEED = 12;

    //The current level of zoom of the camera
    int m_zoom_level;

    //The camera's top left corner with respect to the standard map
    sf::Vector2i m_viewpoint;

public:

    //Constructors
    cameraview();
    cameraview(int x, int y);

    //Functions to return the camera's position
    int getX() const {return m_viewpoint.x;}
    int getY() const {return m_viewpoint.y;}

    //A function to change the camera's position TODO:
    void changeView(bool up, bool down, bool left, bool right);

    //A function to set the camera's position
    void setView(int x, int y){m_viewpoint.x = x; m_viewpoint.y = y;}

    //A function to shift the camera's position
    void setDeltaView(int x, int y);

    //A function to set the zoom level of the camera
    void setZoomLevel(int zoom_level);
};

#endif // CAMERA_HPP_INCLUDED
