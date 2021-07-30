/**
* Created by Modar Nasser on 06/10/2020.
**/

#pragma once

#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "NasNas/core/graphics/Renderable.hpp"
#include "NasNas/core/graphics/Sprite.hpp"

namespace ns {

    class SpriteBatch : public sf::Drawable, ns::Renderable {

        struct SpriteBatchLayer {
            explicit SpriteBatchLayer(const sf::Texture* tex);
            const sf::Texture* texture;
            sf::VertexBuffer buffer;
            std::vector<const ns::Sprite*> sprites;
            std::vector<sf::Vertex> vertices;
        };

    public:
        enum class DrawOrder {Front, Back};

        SpriteBatch();
        void clear();

        void start(sf::VertexBuffer::Usage usage);

        void setDrawOrder(DrawOrder order);

        void draw(const ns::Sprite* sprite);
        void draw(const sf::Texture* texture, const sf::Vector2f& pos, const sf::IntRect& rect, const sf::Color& color = sf::Color::White);
        void draw(const sf::Texture* texture, const sf::IntRect& rect, const sf::Transformable& tr, const sf::Color& color = sf::Color::White);

        void erase(const ns::Sprite* sprite);

        void end();

        auto getDepth() const -> unsigned ;
        auto getUsage() const -> sf::VertexBuffer::Usage;
        auto getPosition() const -> sf::Vector2f;
        auto getGlobalBounds() const -> ns::FloatRect;

    private:
        void render() override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        ns::FloatRect m_global_bounds;
        sf::VertexBuffer::Usage m_usage;
        DrawOrder m_draw_order = DrawOrder::Front;

        std::list<SpriteBatchLayer> m_layers;
        std::vector<std::unique_ptr<const ns::Sprite>> m_gc;

        bool m_need_end = false;
    };

}
