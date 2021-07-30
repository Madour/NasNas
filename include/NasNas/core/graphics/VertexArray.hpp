/**
* Created by Modar Nasser on 19/12/2020.
**/

#pragma once

#include <SFML/Graphics.hpp>

namespace ns {

    class VertexArray : public sf::VertexArray {
    public:
        void setTexture(const sf::Texture& texture) {
            m_texture = &texture;
        }
        auto getPosition() const -> sf::Vector2f;

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            states.texture = m_texture;
            target.draw(static_cast<sf::VertexArray>(*this), states);
        }

        const sf::Texture* m_texture = nullptr;
    };

}
