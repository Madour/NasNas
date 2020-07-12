/**
* Created by Modar Nasser on 11/07/2020.
**/


#pragma once

#include <variant>
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "NasNas/thirdparty/pugixml.hpp"

namespace ns::tm {

    using PropertyTypes = std::variant<int, float, std::string, bool, sf::Color>;

    class PropertiesContainer {
    public:
        template <typename T>
        auto getProperty(const std::string& name) -> T;

        template <typename T>
        void addProperty(const std::string& name, const T& value);

    protected:
        void addProperty(const pugi::xml_node& xml_prop);
        std::unordered_map<std::string, PropertyTypes> m_properties;

    };

    template<typename T>
    auto PropertiesContainer::getProperty(const std::string& name) -> T {
        if (m_properties.count(name)) {
            if (std::holds_alternative<T>(m_properties[name])) {
                return std::get<T>(m_properties[name]);
            }
            std::cout << "Error (bad_variant_access) : Property «" << name
                      << "» is not of type " << typeid(T).name()
                      << ". You are requesting the wrong type." << std::endl;
            exit(-1);
        }
        std::cout << "Error : Property named «" << name << "» does not exist." << std::endl;
        exit(-1);
    }

    template<typename T>
    void PropertiesContainer::addProperty(const std::string& name, const T& value) {
        if (std::is_same_v<int, T> || std::is_same_v<float, T> || std::is_same_v<bool, T> ||
            std::is_same_v<std::string, T> || std::is_same_v<sf::Color, T>) {
            m_properties[name] = value;
        }
        else {
            std::cout << "Error : Cannot add property of type " << typeid(T).name()
                      << ". (Accepted types are int, float, bool, std::string, sf::Color)."<< std::endl;
            exit(-1);
        }
    }
}
