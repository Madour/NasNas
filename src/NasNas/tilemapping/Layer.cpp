/**
* Created by Modar Nasser on 11/07/2020.
**/


#include "NasNas/tilemapping/Layer.hpp"

using namespace ns;
using namespace ns::tm;

Layer::Layer(const pugi::xml_node& xml_node, TiledMap* tiledmap) {
    m_tiledmap = tiledmap;

    m_id = xml_node.attribute("id").as_uint();
    m_name = xml_node.attribute("name").as_string();
    if (xml_node.attribute("visible"))
        m_visible = xml_node.attribute("visible").as_bool();
    if (xml_node.attribute("opacity"))
        m_opacity = xml_node.attribute("opacity").as_float();
    if (xml_node.attribute("offsetx"))
        m_position.x = xml_node.attribute("offsetx").as_float();
    if (xml_node.attribute("offsety"))
        m_position.y = xml_node.attribute("offsety").as_float();
}

auto Layer::getId() const -> unsigned int {
    return m_id;
}

auto Layer::getName() -> std::string& {
    return m_name;
}

auto Layer::isVisible() const -> bool {
    return m_visible;
}

void Layer::setVisible(bool value) {
    m_visible = value;
}
