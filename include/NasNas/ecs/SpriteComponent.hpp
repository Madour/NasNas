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
        static auto getId() -> unsigned long;

        SpriteComponent(BaseEntity* entity, Spritesheet* spritesheet, const sf::Vector2f& pos_offset);
        SpriteComponent(BaseEntity* entity, Spritesheet* spritesheet, const std::string& anim_state="", const sf::Vector2f& pos_offset={0, 0});
        void setSpritesheet(Spritesheet* spritesheet);
        auto getAnimState() const -> const std::string&;
        void setAnimState(const std::string& anim_state);
        auto getAnimPlayer() -> AnimPlayer&;
        auto getDrawable() -> sf::Sprite& override;
        auto getGlobalBounds() -> ns::FloatRect override;
        void update() override;

    private:
        static unsigned long uid;

        Spritesheet* m_spritesheet = nullptr;
        AnimPlayer m_anim_player;
        sf::Sprite m_drawable;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}

