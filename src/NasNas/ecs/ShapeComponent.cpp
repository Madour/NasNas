/**
* Created by Modar Nasser on 05/02/2021.
**/

#include "NasNas/ecs/ShapeComponent.hpp"

using namespace ns;
using namespace ns::ecs;

template <>
const unsigned long Shape<sf::CircleShape>::uid = BaseComponent::getNextId();

template <>
const unsigned long Shape<ns::EllipseShape>::uid = BaseComponent::getNextId();

template <>
const unsigned long Shape<ns::LineShape>::uid = BaseComponent::getNextId();

template <>
const unsigned long Shape<sf::RectangleShape>::uid = BaseComponent::getNextId();

template <>
const unsigned long Shape<sf::ConvexShape>::uid = BaseComponent::getNextId();
