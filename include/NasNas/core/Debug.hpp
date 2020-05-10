/**
* Created by Modar Nasser on 01/05/2020.
**/

#pragma once

#include "SFML/Graphics.hpp"
#include "NasNas/reslib/ResourceManager.hpp"
#include <iostream>

namespace ns {


    template <typename  T>
    class DebugText: public sf::Text {
    public:
        DebugText(T* var_address, std::string var_name,const sf::Vector2f& position);
        DebugText(const T* var_address, std::string var_name,const sf::Vector2f& position);
        void update();
    private:
        std::string variable_name;
        T* variable_address;
    };

    template<typename T>
    DebugText<T>::DebugText(T* var_address, std::string var_name, const sf::Vector2f &position) {
        this->variable_address = var_address;
        this->variable_name = var_name;
        this->setFont(Res::get().getFont("arial"));
        this->setPosition(position);
        this->setCharacterSize(20);
        this->update();
    }

    template<typename T>
    DebugText<T>::DebugText(const T* var_address, std::string var_name, const sf::Vector2f &position) {
        this->variable_address = (T*)var_address;
        this->variable_name = var_name;
        this->setFont(Res::get().getFont("arial"));
        this->setPosition(position);
        this->setCharacterSize(20);
        this->update();
    }
}
