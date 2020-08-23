/**
* Created by Modar Nasser on 11/07/2020.
**/


#include "NasNas/tilemapping/Layer.hpp"

using namespace ns;
using namespace ns::tm;

Layer::Layer(const pugi::xml_node& xml_node, TiledMap* tiledmap) :
PropertiesContainer(xml_node.child("properties")) {
    m_tiledmap = tiledmap;

    m_id = xml_node.attribute("id").as_uint();
    m_name = xml_node.attribute("name").as_string();
    if (xml_node.attribute("visible"))
        m_visible = xml_node.attribute("visible").as_bool();
    if (xml_node.attribute("opacity"))
        m_opacity = xml_node.attribute("opacity").as_float();
    if (xml_node.attribute("offsetx"))
        m_transformable.setPosition(xml_node.attribute("offsetx").as_float(), m_transformable.getPosition().y);
    if (xml_node.attribute("offsety"))
        m_transformable.setPosition(m_transformable.getPosition().x, xml_node.attribute("offsety").as_float());
    if (xml_node.attribute("tintcolor"))
        m_tintcolor = toColor(std::string(xml_node.attribute("tintcolor").as_string()));
}

auto Layer::getId() const -> unsigned int {
    return m_id;
}

auto Layer::getName() -> std::string& {
    return m_name;
}

auto Layer::getPosition() -> sf::Vector2f {
    return m_transformable.getPosition();
}

void Layer::setPosition(float x, float y) {
    m_transformable.setPosition(x, y);
}

void Layer::setPosition(sf::Vector2f position) {
    m_transformable.setPosition(position);
}

void Layer::move(float x, float y) {
    m_transformable.move(x, y);
}

auto Layer::isVisible() const -> bool {
    return m_visible;
}

void Layer::setVisible(bool value) {
    m_visible = value;
}
