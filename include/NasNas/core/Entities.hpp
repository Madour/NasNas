/**
* Created by Modar Nasser on 15/04/2020.
**/

#pragma once

#include "NasNas/data/AppComponent.hpp"
#include "NasNas/core/Sprite.hpp"

namespace ns {

    class BaseEntity: public AppComponent, public Drawable {
    public:
        friend App;
        BaseEntity();
        explicit BaseEntity(const std::string& name, const std::string& default_anim_state = "idle");
        explicit BaseEntity(const std::string& name, Sprite* sprite_data, const std::string& default_anim_state = "idle");
        ~BaseEntity() override;

        void setSprite(Sprite* sprite_data);
        void update();

        auto getPosition() const -> sf::Vector2f override;
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
        Sprite* data = nullptr;
        std::string name;
        std::string anim_state;
        sf::Vector2f velocity = {0, 0};
        sf::Vector2f acceleration = {1, 1};
        sf::Sprite sprite;
        AnimPlayer anim_player;
        int gx = 0, gy = 0;
        float rx = 0, ry = 0;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    };

}
