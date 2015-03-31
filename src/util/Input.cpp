#include <unordered_map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

#include "Input.hpp"

namespace {

    //A map of keys that are/aren't pressed
    std::unordered_map<std::string, bool> m_key_pressed_map ( { {"RMB"     , false},
                                                                {"LMB"     , false},
                                                                {"Up"      , false},
                                                                {"Down"    , false},
                                                                {"Left"    , false},
                                                                {"Right"   , false},
                                                                {"Add"     , false},
                                                                {"Subtract", false},
                                                                {"Q"       , false},
                                                                {"W"       , false},
                                                                {"E"       , false},
                                                                {"R"       , false},
                                                                {"T"       , false},
                                                                {"Y"       , false} } );

    //The drag box formed by clicking and dragging
    sf::IntRect m_drag_box(0, 0, 0, 0);

    sf::Vector2i m_cursor_position(0, 0);

    //The direction the scroll wheel is spun
    int m_scroll_wheel_delta(0);
}

//Parse the inputs given by an event.  RenderWindow is required to set mouse position.
bool Input::parseInput(const sf::Event _event, const sf::RenderWindow& _reference_window)
{
    switch(_event.type){
    case (sf::Event::Closed):
        return false;
        break;
    case (sf::Event::KeyPressed):
        switch (_event.key.code) {
        case (sf::Keyboard::Left):
            m_key_pressed_map["Left"] = true;
            break;
        case (sf::Keyboard::Right):
            m_key_pressed_map["Right"] = true;
            break;
        case (sf::Keyboard::Up):
            m_key_pressed_map["Up"] = true;
            break;
        case (sf::Keyboard::Down):
            m_key_pressed_map["Down"] = true;
            break;
        case (sf::Keyboard::Add):
            m_key_pressed_map["Add"] = true;
            m_scroll_wheel_delta = 1;
            break;
        case (sf::Keyboard::Subtract):
            m_key_pressed_map["Subtract"] = true;
            m_scroll_wheel_delta = -1;
            break;
        default:
            /*
             * Include more keys later
             */
             break;
        }
        break;
    case (sf::Event::KeyReleased):
        switch (_event.key.code) {
        case (sf::Keyboard::Left):
            m_key_pressed_map["Left"] = false;
            break;
        case (sf::Keyboard::Right):
            m_key_pressed_map["Right"] = false;
            break;
        case (sf::Keyboard::Up):
            m_key_pressed_map["Up"] = false;
            break;
        case (sf::Keyboard::Down):
            m_key_pressed_map["Down"] = false;
            break;
        case (sf::Keyboard::Add):
            m_key_pressed_map["Add"] = false;
            break;
        case (sf::Keyboard::Subtract):
            m_key_pressed_map["Subtract"] = false;
            break;
        default:
            /*
             * Include more keys later
             */
             break;
        }
        break;
    case (sf::Event::MouseMoved):
        m_cursor_position = sf::Mouse::getPosition(_reference_window);
        if (!m_key_pressed_map["RMB"]){
            m_drag_box.left   = m_cursor_position.x;
            m_drag_box.top    = m_cursor_position.y;
        }
        else {
            m_drag_box.height = m_cursor_position.x;
            m_drag_box.width  = m_cursor_position.y;
        }
        break;
    case (sf::Event::MouseButtonPressed):
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            m_key_pressed_map["RMB"] = true;
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            m_key_pressed_map["LMB"] = true;
        break;
    case (sf::Event::MouseButtonReleased):
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
            m_key_pressed_map["RMB"] = false;
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            m_key_pressed_map["LMB"] = false;
        break;
    case (sf::Event::MouseWheelMoved):
        if (_event.mouseWheel.delta > 0)
            m_scroll_wheel_delta = 1;
        else
            m_scroll_wheel_delta = -1;
        break;
    default:
        /*
         * Include more events later
         */
         break;
    }
    return true;
}

bool Input::arrowKeyPressed()
{
    return (m_key_pressed_map["Up"] || m_key_pressed_map["Down"] || m_key_pressed_map["Left"] || m_key_pressed_map["Right"]);
}

//Return whether the specified key is pressed
bool Input::getKeyPressed(const std::string _key){return m_key_pressed_map[_key];}

//Return the direction the mouse wheel was just spun (if at all)
int Input::getMouseWheelDelta(){return m_scroll_wheel_delta;}

//Return the position of the mouse with reference to a RenderWindow
sf::Vector2i Input::getMousePosition(const sf::RenderWindow& _reference_window) {return sf::Mouse::getPosition(_reference_window);}

//Manipulate the status of keys being pressed or not
void Input::setKeyPressed(const std::string _key) {m_key_pressed_map[_key] = true;}
void Input::setKeyReleased(const std::string _key){m_key_pressed_map[_key] = false;}
void Input::setKeyToggled(const std::string _key) {m_key_pressed_map[_key] = !m_key_pressed_map[_key];}

//Zero out the scroll wheel
void Input::zeroMouseWheelDelta(){m_scroll_wheel_delta = 0;}
