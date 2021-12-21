// Created by Modar Nasser on 10/06/2020.

#pragma once

#include <string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include <NasNas/core/graphics/Anim.hpp>
#include <NasNas/core/graphics/Spritesheet.hpp>
#include <NasNas/ecs/components/GraphicsComponent.hpp>

namespace ns::ecs {

    class SpriteComponent : public GraphicsComponent {
    public:
        SpriteComponent(Spritesheet* spritesheet, const sf::Vector2f& pos_offset);
        explicit SpriteComponent(Spritesheet* spritesheet, const std::string& anim_state="", const sf::Vector2f& pos_offset={0, 0});
        void setSpritesheet(Spritesheet* spritesheet);
        auto getAnimState() const -> const std::string&;
        void setAnimState(const std::string& anim_state);
        auto getAnimPlayer() -> AnimPlayer&;
        auto getDrawable() -> sf::Sprite& override;
        auto getGlobalBounds() -> ns::FloatRect override;
        void update() override;

    private:
        Spritesheet* m_spritesheet = nullptr;
        AnimPlayer m_anim_player;
        sf::Sprite m_drawable;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    using Sprite = SpriteComponent;

}

