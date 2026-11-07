#include <Utilities/input.hpp>
#include <iostream>

void Input::BeginFrame(){
    keyboardButtonPressed.fill(false);
    keyboardButtonReleased.fill(false);

    mouseButtonPressed.fill(false);
    mouseButtonReleased.fill(false);
}

void Input::HandleEvent(const sf::Event& event){
    if(const auto* eventInfo = event.getIf<sf::Event::KeyPressed>()){
        if(eventInfo->code == sf::Keyboard::Key::Unknown) return;
        else if(!keyboardButtonDown[static_cast<size_t>(eventInfo->code)]){
            keyboardButtonPressed[static_cast<size_t>(eventInfo->code)] = true;
        }
        keyboardButtonDown[static_cast<size_t>(eventInfo->code)] = true;

        //std::cout << "Press" << std::endl;
    }

    if(const auto* eventInfo = event.getIf<sf::Event::KeyReleased>()){
        if(eventInfo->code == sf::Keyboard::Key::Unknown) return;
        else if(!keyboardButtonReleased[static_cast<size_t>(eventInfo->code)]){
            keyboardButtonReleased[static_cast<size_t>(eventInfo->code)] = true;
        }
        keyboardButtonDown[static_cast<size_t>(eventInfo->code)] = false;

        //std::cout << "Release";
    }

    if(const auto* eventInfo = event.getIf<sf::Event::MouseButtonPressed>()){
        if(!mouseButtonDown[static_cast<size_t>(eventInfo->button)]){
            mouseButtonPressed[static_cast<size_t>(eventInfo->button)] = true;
        }
        mouseButtonDown[static_cast<size_t>(eventInfo->button)] = true;

        //std::cout << "Mouse press";
    }

    if(const auto* eventInfo = event.getIf<sf::Event::MouseButtonReleased>()){
        if(!mouseButtonReleased[static_cast<size_t>(eventInfo->button)]){
            mouseButtonReleased[static_cast<size_t>(eventInfo->button)] = true;
        }
        mouseButtonDown[static_cast<size_t>(eventInfo->button)] = false;

        //std::cout << "Mouse release";
    }

    
    
}