/**
* Created by Modar Nasser on 11/07/2020.
**/


#include "NasNas/core/data/Maths.hpp"
#include "NasNas/tilemapping/TiledMap.hpp"
#include "NasNas/tilemapping/Layer.hpp"
#include "NasNas/tilemapping/GroupLayer.hpp"

using namespace ns;
using namespace ns::tm;

Layer::Layer(const pugi::xml_node& xml_node, TiledMap* tiledmap) :
m_tiledmap(tiledmap)
{
    m_id = xml_node.attribute("id").as_uint();
    m_name = xml_node.attribute("name").as_string();
    if (xml_node.attribute("visible"))
        m_visible = xml_node.attribute("visible").as_bool();
    if (xml_node.attribute("opacity"))
        m_opacity = xml_node.attribute("opacity").as_float();
    if (xml_node.attribute("offsetx"))
        m_offset.x = xml_node.attribute("offsetx").as_float();
    if (xml_node.attribute("offsety"))
        m_offset.y = xml_node.attribute("offsety").as_float();
    if (xml_node.attribute("tintcolor"))
        m_tintcolor = hexToColor(std::string(xml_node.attribute("tintcolor").as_string()));
    if (xml_node.attribute("parallaxx"))
        m_parallax_factor.x = xml_node.attribute("parallaxx").as_float();
    if (xml_node.attribute("parallaxy"))
        m_parallax_factor.y = xml_node.attribute("parallaxy").as_float();

    parseProperties(xml_node.child("properties"));
}

auto Layer::getId() const -> unsigned int {
    return m_id;
}

auto Layer::getName() const -> const std::string& {
    return m_name;
}

auto Layer::isVisible() const -> bool {
    return m_visible;
}

void Layer::setVisible(bool value) {
    m_visible = value;
}

auto Layer::getOffset() const -> const sf::Vector2f& {
    return m_offset;
}

auto Layer::getTotalOffset() const -> sf::Vector2f {
    if (m_parent_group)
        return getOffset() + m_parent_group->getOffset();
    return getOffset();
}

auto Layer::getParallaxFactor() const -> const sf::Vector2f& {
    return m_parallax_factor;
}

auto Layer::getTotalParallaxFactor() const -> sf::Vector2f {
    if (m_parent_group) {
        return getParallaxFactor() * m_parent_group->getTotalParallaxFactor();
    }
    return getParallaxFactor();
}

auto Layer::getGlobalBounds() const -> ns::FloatRect {
    return {getPosition(), m_tiledmap->getSize()};
}
