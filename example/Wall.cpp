/**
* Created by Modar Nasser on 26/07/2020.
**/

#include "Wall.hpp"

Wall::Wall(float x, float y) : ns::BaseEntity("Wall") {
    setPosition(x, y);
    addComponent<ns::ecs::ColliderComponent>(this, new ns::ecs::RectangleCollision(100, 200), sf::Vector2f(50, 100));

    auto shape_comp = std::make_shared<ns::ecs::ShapeComponent<sf::RectangleShape>>(this, sf::Vector2f(100, 200));
    shape_comp->getDrawable().setFillColor(sf::Color::Transparent);
    shape_comp->getDrawable().setOutlineColor(sf::Color::Black);
    shape_comp->getDrawable().setOutlineThickness(1);
    addComponent<ns::ecs::ShapeComponent<sf::RectangleShape>>(shape_comp);

}
