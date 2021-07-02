// Created by Modar Nasser on 01/07/2021.

#include "NasNas/tilemapping/GroupLayer.hpp"

using namespace ns;
using namespace ns::tm;

GroupLayer::GroupLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) :
Layer(xml_node, tiledmap)
{

}

void GroupLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}