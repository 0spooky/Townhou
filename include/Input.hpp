#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace Input {

    bool parseInput(const sf::Event _event, const sf::RenderWindow& _referenceWindow);

    bool arrowKeyPressed();

    bool getKeyPressed(const std::string _key);

    int getMouseWheelDelta();

    sf::Vector2i getMousePosition(const sf::RenderWindow& _referenceWindow);

    void setKeyPressed(const std::string _key);
    void setKeyReleased(const std::string _key);
    void setKeyToggled(const std::string _key);

    void zeroMouseWheelDelta();
}

#endif // INPUT_HPP_INCLUDED
