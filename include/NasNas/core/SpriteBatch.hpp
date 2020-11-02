/**
* Created by Modar Nasser on 06/10/2020.
**/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "NasNas/data/Drawable.hpp"
#include "NasNas/core/App.hpp"


namespace ns {

    class SpriteBatch : public ns::Drawable {
    public:

        explicit SpriteBatch(std::string name);
        ~SpriteBatch() override;

        void clear();

        void draw(sf::Sprite* sprite);

        void draw(sf::Texture* texture, sf::Vector2f pos, sf::IntRect rect);

        void end();

        auto getPosition() const -> sf::Vector2f override;
        auto getGlobalBounds() const -> ns::FloatRect override;

    private:
        friend App;
        void render();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        std::string m_name;
        std::vector<sf::Sprite*> m_owned_sprites;
        std::vector<std::vector<sf::Sprite*>> m_sprites;
        std::vector<std::pair<const sf::Texture*, std::vector<sf::Vertex>>> m_vertices;
        ns::FloatRect m_global_bounds;

        static std::vector<SpriteBatch*> list;
    };

}
