/**
* Created by Modar Nasser on 01/05/2020.
**/

#pragma once

#include "SFML/Graphics.hpp"
#include "NasNas/reslib/ResourceManager.hpp"
#include "NasNas/core/Entities.hpp"
#include <iostream>

namespace ns {

    template<typename T>
    class DebugText : public sf::Text {
    public:
        static sf::Color color;
        DebugText(T *var_address, std::string label, const sf::Vector2f &position);

        DebugText(const T *var_address, std::string label, const sf::Vector2f &position);

        DebugText(
                BaseEntity* object_address,
                std::function<T(BaseEntity &)> method_address,
                std::string label,
                const sf::Vector2f &position
        );

        void update();

    private:
        DebugText(std::string label, const sf::Vector2f& position);

        std::string label;
        sf::Color fillcolor = color;
        T *variable_address = nullptr;
        BaseEntity *object_address = nullptr;
        std::function<T(BaseEntity &)> method_address = nullptr;
    };

    template<typename T>
    sf::Color DebugText<T>::color = sf::Color::White;

    template<typename T>
    DebugText<T>::DebugText(std::string label, const sf::Vector2f& position) {
        this->label = label;
        this->setFont(Res::get().getFont("arial"));
        this->setFillColor(fillcolor);
        this->setPosition(position);
        this->setCharacterSize(20);
    }

    template<typename T>
    DebugText<T>::DebugText(T *var_address, std::string label, const sf::Vector2f &position)
    : DebugText(label, position) {
        this->variable_address = var_address;
    }

    template<typename T>
    DebugText<T>::DebugText(const T *var_address, std::string label, const sf::Vector2f &position)
    : DebugText(label, position) {
        this->variable_address = (T*) var_address;
    }

    template<typename T>
    DebugText<T>::DebugText(
            BaseEntity* object_address,
            std::function<T(BaseEntity &)> method_address,
            std::string label,
            const sf::Vector2f& position
    )
    : DebugText(label, position) {
        this->method_address = method_address;
        this->object_address = object_address;
    }
}
