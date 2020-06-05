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

        DebugText(T *var_address, std::string var_name, const sf::Vector2f &position);

        DebugText(const T *var_address, std::string var_name, const sf::Vector2f &position);

        DebugText(
                std::function<T(BaseEntity &)> method_address,
                BaseEntity *object_address,
                std::string var_name,
                const sf::Vector2f &position
        );

        DebugText(
                std::function<T(const BaseEntity &)> method_address,
                BaseEntity *object_address,
                std::string var_name,
                const sf::Vector2f &position
        );

        void update();

    private:
        DebugText(std::string var_name, const sf::Vector2f &position);

        std::string variable_name;
        T *variable_address = nullptr;
        BaseEntity *object_address = nullptr;
        std::function<T(BaseEntity &)> method_address = nullptr;
    };

    template<typename T>
    DebugText<T>::DebugText(std::string var_name, const sf::Vector2f &position) {
        this->variable_name = var_name;
        this->setFont(Res::get().getFont("arial"));
        this->setPosition(position);
        this->setCharacterSize(20);
    }

    template<typename T>
    DebugText<T>::DebugText(T *var_address, std::string var_name, const sf::Vector2f &position)
    : DebugText(var_name, position) {
        this->variable_address = var_address;
    }

    template<typename T>
    DebugText<T>::DebugText(const T *var_address, std::string var_name, const sf::Vector2f &position)
    : DebugText(var_name, position) {
        this->variable_address = (T*) var_address;
    }

    template<typename T>
    DebugText<T>::DebugText(
            std::function<T(BaseEntity &)> method_address,
            BaseEntity *object_address,
            std::string var_name,
            const sf::Vector2f &position
    )
    : DebugText(var_name, position) {
        this->method_address = method_address;
        this->object_address = object_address;
    }

    template<typename T>
    DebugText<T>::DebugText(
            std::function<T(const BaseEntity &)> method_address,
            BaseEntity *object_address,
            std::string var_name,
            const sf::Vector2f &position
    )
    : DebugText(var_name, position) {
        this->method_address = (std::function<T(BaseEntity &)>) method_address;
        this->object_address = object_address;
    }

}
