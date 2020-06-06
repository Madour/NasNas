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

        std::string m_label;
        sf::Color m_fillcolor = color;
        T* m_variable_address = nullptr;
        BaseEntity* m_object_address = nullptr;
        std::function<T(BaseEntity &)> m_method_address = nullptr;
    };

    template<typename T>
    sf::Color DebugText<T>::color = sf::Color::White;

    template<typename T>
    DebugText<T>::DebugText(std::string label, const sf::Vector2f& position) {
        m_label = label;
        setFont(Res::get().getFont("arial"));
        setFillColor(m_fillcolor);
        setPosition(position);
        setCharacterSize(20);
    }

    template<typename T>
    DebugText<T>::DebugText(T *var_address, std::string label, const sf::Vector2f &position)
    : DebugText(label, position) {
        m_variable_address = var_address;
    }

    template<typename T>
    DebugText<T>::DebugText(const T *var_address, std::string label, const sf::Vector2f &position)
    : DebugText(label, position) {
        m_variable_address = (T*) var_address;
    }

    template<typename T>
    DebugText<T>::DebugText(
            BaseEntity* object_address,
            std::function<T(BaseEntity &)> method_address,
            std::string label,
            const sf::Vector2f& position
    )
    : DebugText(label, position) {
        m_method_address = method_address;
        m_object_address = object_address;
    }
}
