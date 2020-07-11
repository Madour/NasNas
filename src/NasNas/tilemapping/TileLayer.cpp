/**
* Created by Modar Nasser on 09/07/2020.
**/


#include "NasNas/tilemapping/TileLayer.hpp"
#include "NasNas/core/Logger.hpp"

using namespace ns;
using namespace ns::tm;

TileLayer::TileLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) :
Layer(xml_node, tiledmap) {
    m_width = m_xml_node.attribute("width").as_int();
    m_height = m_xml_node.attribute("height").as_int();

    // parsing properties
    for (const auto& xml_prop : m_xml_node.child("properties").children()) {
        addProperty(xml_prop);
    }
    // parsing data
    auto xml_data = m_xml_node.child("data");
    auto encoding = std::string(xml_data.attribute("encoding").as_string());

    if (encoding == "csv") {
        auto layer_data = xml_data.text().as_string();
        std::uint32_t current_gid = 0;

        while (*layer_data != '\0') {
            switch (*layer_data) {
                case '\n':
                    break;
                case ',':
                    m_tiles.push_back({ current_gid & 0x1fffffff , (uint8_t)((current_gid&0xe0000000)>>28) });
                    current_gid = 0;
                    break;
                default:
                    current_gid *= 10;
                    current_gid += *layer_data - '0';
            }
            layer_data++;
        }
    }
    else {
        std::cout << "Encoding «" << encoding << "» is not supported, please use CSV instead." << std::endl;
        exit(-1);
    }
}
