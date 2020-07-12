/**
* Created by Modar Nasser on 24/06/2020.
**/


#pragma once

#include <functional>
#include <unordered_map>
#include <SFML/System.hpp>
#include "NasNas/ecs/BaseComponent.hpp"

namespace ns::ecs {

    class InputsComponent : public BaseComponent{
    public:
        explicit InputsComponent(BaseEntity* entity);

        template <typename T>
        void bind(sf::Keyboard::Key key, std::function<void(T&)> function);

        void setCaptureInput(bool);

        template <typename T>
        void update();

        void update() override;

    private:
        template <typename T>
        static std::unordered_map<InputsComponent*, std::unordered_map<sf::Keyboard::Key, std::function<void(T&)>>> m_controls;

        bool m_capture_input;
    };

    template <typename T>
    std::unordered_map<InputsComponent*, std::unordered_map<sf::Keyboard::Key, std::function<void(T&)>>> InputsComponent::m_controls = {};
    template<typename T>
    void InputsComponent::bind(sf::Keyboard::Key key, std::function<void(T &)> function) {
        static_assert(std::is_base_of_v<BaseEntity, T>);
        m_controls<T>[this][key] = std::move(function);
    }

    template <typename T>
    void InputsComponent::update() {
        if (m_capture_input) {
            for (const auto& item : m_controls<T>[this]) {
                if (sf::Keyboard::isKeyPressed(item.first))
                    item.second(*dynamic_cast<T*>(m_entity));
            }
        }
    }

}
