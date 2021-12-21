/**
* Created by Modar Nasser on 19/12/2020.
**/

#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace ns {
    class VertexArray : public sf::VertexArray {
    public:
        void setTexture(const sf::Texture& texture) {
            m_texture = &texture;
        }
        auto getPosition() const -> sf::Vector2f;

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        const sf::Texture* m_texture = nullptr;
    };
}
