/**
* Created by Modar Nasser on 11/07/2020.
**/


#include "NasNas/tilemapping/PropertiesContainer.hpp"
#include "NasNas/core/Logger.hpp"

using namespace ns;
using namespace ns::tm;

void PropertiesContainer::addProperty(const pugi::xml_node& xml_prop) {
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
        // temporary, TODO : convert #color string to sf::Color
        prop_value = xml_prop.attribute("value").as_string();
    } else
        prop_value = xml_prop.attribute("value").as_string();

    m_properties[prop_name] = prop_value;
}


void PropertiesContainer::printProperties() const {
    for (const auto& [prop_name, prop_value] : m_properties) {
        std::cout << prop_name << " : ";
        std::visit([](auto & value){std::cout << value << std::endl;}, prop_value);
    }
}