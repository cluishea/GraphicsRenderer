#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <array>

class Input{

private:

    std::array<bool,sf::Keyboard::KeyCount> keyboardButtonDown{}, keyboardButtonPressed{}, keyboardButtonReleased{};
    std::array<bool,sf::Mouse::ButtonCount> mouseButtonDown{}, mouseButtonPressed{}, mouseButtonReleased{}; 

public:

    void BeginFrame();
    void HandleEvent(const sf::Event& event);

    sf::Vector2i GetMousePosition(sf::RenderWindow& window){
        return sf::Mouse::getPosition(window);
    }

    bool IsKeyPressed(sf::Keyboard::Key k){
        return keyboardButtonPressed[static_cast<size_t>(k)];
    }

    bool IsMouseButtonPressed(sf::Mouse::Button b){
        return mouseButtonPressed[static_cast<size_t>(b)];
    }

};