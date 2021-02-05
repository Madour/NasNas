/**
* Created by Modar Nasser on 05/02/2021.
**/

#include "NasNas/ecs/ShapeComponent.hpp"

using namespace ns;
using namespace ns::ecs;

template <>
unsigned long ShapeComponent<sf::CircleShape>::uid = BaseComponent::getNextId();

template <>
unsigned long ShapeComponent<ns::EllipseShape>::uid = BaseComponent::getNextId();

template <>
unsigned long ShapeComponent<ns::LineShape>::uid = BaseComponent::getNextId();

template <>
unsigned long ShapeComponent<sf::RectangleShape>::uid = BaseComponent::getNextId();

template <>
unsigned long ShapeComponent<sf::ConvexShape>::uid = BaseComponent::getNextId();
