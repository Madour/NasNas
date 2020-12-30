/**
* Created by Modar Nasser on 19/12/2020.
**/

#pragma once

#include <SFML/Graphics.hpp>
#include "NasNas/data/Drawable.hpp"

namespace ns {

    class VertexArray : public ns::Drawable, public sf::VertexArray {
    public:
        void setTexture(const sf::Texture& texture) {
            m_texture = &texture;
        }
        auto getPosition() const -> sf::Vector2f override;
        auto getGlobalBounds() const -> ns::FloatRect override;

    private:
        const sf::Texture* m_texture = nullptr;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            states.texture = m_texture;
            target.draw(static_cast<sf::VertexArray>(*this), states);
        }
    };

}
