/**
* Created by Modar Nasser on 15/04/2020.
**/

#pragma once

#include "NasNas/data/AppComponent.hpp"
#include "NasNas/core/Sprite.hpp"
#include "NasNas/ecs/AnimPlayer.hpp"

namespace ns {

    class BaseEntity: public AppComponent, public Drawable {
    public:
        friend App;
        explicit BaseEntity(const std::string& name, const std::string& default_anim_state = "idle");
        explicit BaseEntity(const std::string& name, Sprite* sprite_data, const std::string& default_anim_state = "idle");
        ~BaseEntity() override;

        void setSprite(Sprite* sprite_data);
        virtual void update();

        auto getPosition() -> sf::Vector2f override;
        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);

        auto getX() const -> float;
        void setX(float value);

        auto getY() const -> float;
        void setY(float value);

        auto getVelocity() const -> sf::Vector2f;
        void setVelocity(float dx, float dy);

        void move(float offsetx, float offsety) override;

    private:
        std::string m_name;

        int m_gx = 0, m_gy = 0;
        float m_rx = 0, m_ry = 0;

        sf::Vector2f m_acceleration = {1, 1};

        Sprite* m_spr_data = nullptr;
        std::string m_anim_state;
        ecs::AnimPlayer m_anim_player;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    protected:
        sf::Vector2f m_velocity = {0, 0};
        sf::Sprite m_sprite;
    };

}
