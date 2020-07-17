/**
* Created by Modar Nasser on 09/07/2020.
**/


#include "NasNas/tilemapping/TileLayer.hpp"

using namespace ns;
using namespace ns::tm;

TileLayer::TileLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) :
Layer(xml_node, tiledmap) {
    m_width = xml_node.attribute("width").as_int();
    m_height = xml_node.attribute("height").as_int();
    m_tiles.reserve(m_width * m_height);
    for (const auto& tileset : m_tiledmap->allTilesets()) {
        m_vertices[tileset.get()].resize(4 * m_width * m_height);
        m_vertices[tileset.get()].setPrimitiveType(sf::PrimitiveType::Quads);
    }

    // parsing properties
    for (const auto& xml_prop : xml_node.child("properties").children()) {
        addProperty(xml_prop);
    }
    // parsing data
    auto xml_data = xml_node.child("data");
    auto encoding = std::string(xml_data.attribute("encoding").as_string());
    if (encoding == "csv") {
        auto layer_data = xml_data.text().as_string();
        std::uint32_t current_gid = 0;
        int tile_counter = 0;

        while (*layer_data != '\0') {
            switch (*layer_data) {
                case '\n':
                    break;
                case ',':
                    addTile(current_gid, tile_counter);
                    current_gid = 0;
                    tile_counter ++;
                    break;
                default:
                    current_gid *= 10;
                    current_gid += *layer_data - '0';
            }
            layer_data++;
        }
        addTile(current_gid, tile_counter);
    }
    else {
        std::cout << "Encoding «" << encoding << "» is not supported, please use CSV instead." << std::endl;
        exit(-1);
    }
}

void TileLayer::addTile(unsigned int gid, unsigned int tile_count) {
    if (gid == 0) return;

    auto& tileset = m_tiledmap->getTileTileset(gid);
    std::uint32_t mask = 0x1fffffff;
    std::uint8_t tile_transform = (uint8_t)((gid & ~mask))>>28u;
    auto id = (gid & mask) - tileset->firstgid;
    auto tilewidth = tileset->tilewidth;
    auto tileheight = tileset->tileheight;
    auto x = (tile_count % m_width) * m_tiledmap->getTileSize().x;
    auto y = (tile_count / m_width) * m_tiledmap->getTileSize().y;
    auto tx = (id % tileset->columns) * tilewidth;
    auto ty = (id / tileset->columns) * tileheight;

    m_tiles.emplace_back(id , tile_transform);
    m_vertices[tileset.get()][tile_count*4 + 0] = sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(tx, ty));
    m_vertices[tileset.get()][tile_count*4 + 1] = sf::Vertex(sf::Vector2f(x + tilewidth, y), sf::Vector2f(tx + tilewidth, ty));
    m_vertices[tileset.get()][tile_count*4 + 2] = sf::Vertex(sf::Vector2f(x + tilewidth, y + tileheight), sf::Vector2f(tx + tilewidth, ty + tileheight));
    m_vertices[tileset.get()][tile_count*4 + 3] = sf::Vertex(sf::Vector2f(x, y + tileheight), sf::Vector2f(tx, ty + tileheight));
}

auto TileLayer::getGlobalBounds() -> ns::FloatRect {
    return ns::FloatRect(getPosition().x, getPosition().y, m_width * m_tiledmap->getTileSize().x, m_height * m_tiledmap->getTileSize().y);
}

void TileLayer::move(float offsetx, float offsety) {
    m_transformable.move(offsetx, offsety);
}

void TileLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto& [tileset, vertices] : m_vertices) {
        states.texture = &tileset->getTexture();
        states.transform *= m_transformable.getTransform();
        target.draw(vertices, states);
    }
}

