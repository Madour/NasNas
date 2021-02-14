/**
* Created by Modar Nasser on 06/10/2020.
**/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "NasNas/core/graphics/Drawable.hpp"
#include "NasNas/core/App.hpp"


namespace ns {

    class SpriteBatch : public ns::Drawable {

        struct SpriteBatchLayer {
            explicit SpriteBatchLayer(const sf::Texture* tex);
            const sf::Texture* texture;
            sf::VertexBuffer buffer;
            std::vector<const sf::Sprite*> sprites;
            std::vector<sf::Vertex> vertices;
        };

    public:
        SpriteBatch();
        ~SpriteBatch() override;

        void clear();

        void start(sf::VertexBuffer::Usage usage);

        void draw(const sf::Sprite* sprite);
        void draw(const sf::Texture* texture, const sf::Vector2f& pos, const sf::IntRect& rect, const sf::Color& color = sf::Color::White);
        void draw(const sf::Texture* texture, const sf::IntRect& rect, const sf::Transformable& tr, const sf::Color& color = sf::Color::White);

        void end();

        auto getDepth() const -> int;
        auto getUsage() const -> sf::VertexBuffer::Usage;
        auto getPosition() const -> sf::Vector2f override;
        auto getGlobalBounds() const -> ns::FloatRect override;

    private:
        friend App;
        void render();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        ns::FloatRect m_global_bounds;
        sf::VertexBuffer::Usage m_usage;

        std::vector<SpriteBatchLayer> m_layers;
        std::vector<const sf::Sprite*> m_owned_sprites;

        static std::vector<SpriteBatch*> list;
    };

}
