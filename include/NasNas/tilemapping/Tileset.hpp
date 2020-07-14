/**
* Created by Modar Nasser on 14/07/2020.
**/


#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "NasNas/thirdparty/pugixml.hpp"

namespace ns::tm {
    class Tileset {
    public:
        explicit Tileset(const pugi::xml_node& xml_node, const std::string& base_path);
        auto getTexture() const -> const sf::Texture&;

        const std::string name;
        const unsigned int tilewidth;
        const unsigned int tileheight;
        const unsigned int tilecount;
        const unsigned int columns;

    private:
        std::string m_image_source;
        sf::Texture* m_texture;
    };

}
