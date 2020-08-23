/**
* Created by Modar Nasser on 11/07/2020.
**/


#include "NasNas/tilemapping/PropertiesContainer.hpp"
#include "NasNas/core/Logger.hpp"

using namespace ns;
using namespace ns::tm;

auto ns::tm::toColor(const std::string& color_string) -> sf::Color {
    sf::Color color = sf::Color::White;
    if (color_string.length() == 9)  // with alpha
        color = sf::Color(
                std::stoul(color_string.substr(3, 2), nullptr, 16),
                std::stoul(color_string.substr(5, 2), nullptr, 16),
                std::stoul(color_string.substr(7, 2), nullptr, 16),
                std::stoul(color_string.substr(1, 2), nullptr, 16)
        );
    else   // no alpha
        color = sf::Color(
                std::stoul(color_string.substr(1, 2), nullptr, 16),
                std::stoul(color_string.substr(3, 2), nullptr, 16),
                std::stoul(color_string.substr(5, 2), nullptr, 16)
        );
    return color;
}

PropertiesContainer::PropertiesContainer() = default;

PropertiesContainer::PropertiesContainer(const pugi::xml_node& xmlnode_props) {
    parseProperties(xmlnode_props);
}

void PropertiesContainer::parseProperties(const pugi::xml_node& xmlnode_props) {
    m_properties.clear();
    for (const auto& xml_prop : xmlnode_props) {
        std::string prop_name = xml_prop.attribute("name").as_string();
        std::string prop_type = xml_prop.attribute("type").as_string();
        PropertyTypes prop_value;

        if (prop_type == "int") {
            prop_value = xml_prop.attribute("value").as_int();
        }
        else if (prop_type == "float") {
            prop_value = xml_prop.attribute("value").as_float();
        }
        else if (prop_type == "bool") {
            prop_value = xml_prop.attribute("value").as_bool();
        }
        else if (prop_type == "color") {
            const auto& c = std::string(xml_prop.attribute("value").as_string());
            auto color = toColor(c);
            prop_value = color;
        }
        else
            prop_value = std::string(xml_prop.attribute("value").as_string());

        m_properties[prop_name] = prop_value;
    }
}


void PropertiesContainer::printProperties() const {
    for (const auto& [prop_name, prop_value] : m_properties) {
        std::cout << prop_name << " : ";
        std::visit([](auto & value){std::cout << value << std::endl;}, prop_value);
    }
}