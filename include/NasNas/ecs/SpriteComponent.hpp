/**
* Created by Modar Nasser on 10/06/2020.
**/


#pragma once

#include "NasNas/core/Anim.hpp"
#include "NasNas/core/Spritesheet.hpp"
#include "NasNas/ecs/GraphicsComponent.hpp"

namespace ns::ecs {

    class SpriteComponent : public  GraphicsComponent {
    public:
        SpriteComponent(BaseEntity* entity, Spritesheet* spritesheet, const std::string& anim_state);
        SpriteComponent(BaseEntity* entity, Spritesheet* spritesheet, const std::string& anim_state, const sf::Vector2f& pos_offset);
        void setSpritesheet(Spritesheet* spritesheet);
        void setAnimState(const std::string& anim_state);
        auto getDrawable() -> sf::Sprite& override;
        auto getGlobalBounds() -> ns::FloatRect override;
        void update() override;

    private:
        Spritesheet* m_spritesheet = nullptr;
        AnimPlayer m_anim_player;
        sf::Vector2f m_pos_offset = {0, 0};
        sf::Sprite m_drawable;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}

