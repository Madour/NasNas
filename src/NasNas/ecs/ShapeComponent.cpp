/**
* Created by Modar Nasser on 11/06/2020.
**/


#include "NasNas/ecs/ShapeComponent.hpp"

using namespace ns;
using namespace ns::ecs;

template<>
ShapeComponent<sf::CircleShape>::ShapeComponent(BaseEntity* entity, float radius, int point_count, const sf::Vector2f& pos_offset) :
GraphicsComponent(entity) {
    m_drawable = sf::CircleShape(radius, point_count);
    m_drawable.setPosition(entity->getPosition());
    m_pos_offset = pos_offset;
}

template<>
ShapeComponent<sf::CircleShape>::ShapeComponent(BaseEntity* entity, float radius, const sf::Vector2f& pos_offset):
GraphicsComponent(entity) {
    m_drawable = sf::CircleShape(radius);
    m_drawable.setPosition(entity->getPosition());
    m_pos_offset = pos_offset;
}

template<>
ShapeComponent<sf::RectangleShape>::ShapeComponent(BaseEntity* entity, const sf::Vector2f& size, const sf::Vector2f& pos_offset):
GraphicsComponent(entity) {
    m_drawable = sf::RectangleShape(size);
    m_drawable.setPosition(entity->getPosition());
    m_pos_offset = pos_offset;
}

template<>
ShapeComponent<sf::ConvexShape>::ShapeComponent(BaseEntity* entity, int point_count, const sf::Vector2f& pos_offset) :
GraphicsComponent(entity) {
    m_drawable = sf::ConvexShape(point_count);
    m_drawable.setPosition(entity->getPosition());
    m_pos_offset = pos_offset;
}
