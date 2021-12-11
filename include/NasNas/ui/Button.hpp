// Created by Modar Nasser on 10/10/2021.

#pragma once

#include <functional>

#include <SFML/Graphics/Text.hpp>

#include <NasNas/ui/Widget.hpp>

namespace ns::ui {

    class ButtonBase : public Widget {
    public:
        ButtonBase() = default;
    };

    template <typename T>
    class Button : public ButtonBase {
        T* m_bg = nullptr;
        sf::Text m_text;
    public:
        Button() = default;

        void setText(sf::Text text);

        void setBackground(T& background);

        auto getGlobalBounds() const -> sf::FloatRect override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    template <typename T>
    void Button<T>::setText(sf::Text text) {
        m_text = text;
        auto bounds = m_text.getGlobalBounds();
        //m_text.setOrigin(bounds.width/2, bounds.height/2);
    }

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
        target.draw(m_text, states);
    }
}
