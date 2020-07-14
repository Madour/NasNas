/**
* Created by Modar Nasser on 14/07/2020.
**/


#include "NasNas/tilemapping/Tileset.hpp"

using namespace ns;
using namespace ns::tm;

Tileset::Tileset(const pugi::xml_node& xml_node, const std::string& path) :
name(xml_node.attribute("name").as_string()),
tilewidth(xml_node.attribute("tilewidth").as_uint()),
tileheight(xml_node.attribute("tileheight").as_uint()),
tilecount(xml_node.attribute("tilecount").as_uint()),
columns(xml_node.attribute("columns").as_uint()) {
    m_image_source = xml_node.child("image").attribute("source").as_string();
    m_texture = new sf::Texture();
    m_texture->loadFromFile(path + m_image_source);
}

auto Tileset::getTexture() const -> const sf::Texture & {
    return *m_texture;
}
