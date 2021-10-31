// Created by Modar Nasser on 10/10/2021.

#pragma once

#include <functional>

#include <NasNas/ui/Widget.hpp>

namespace ns::ui {

    class ButtonBase : public Widget {
    public:
        ButtonBase() = default;
    };

    template <typename T>
    class Button : public ButtonBase {
        T* m_bg = nullptr;
    public:
        Button() = default;

        void setBackground(T& background);

        auto getGlobalBounds() const -> sf::FloatRect override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    template <typename T>
    void Button<T>::setBackground(T& background) {
        m_bg = &background;
    }

    template <typename T>
    auto Button<T>::getGlobalBounds() const -> sf::FloatRect {
        return getTransform().transformRect(m_bg->getGlobalBounds());
    }

    template <typename T>
    void Button<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(*m_bg, states);
    }
}
