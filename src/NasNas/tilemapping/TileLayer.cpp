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
        const auto* layer_data = xml_data.text().as_string();
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

void TileLayer::addTile(std::uint32_t gid, unsigned int tile_count) {
    if (gid == 0) return;

    const auto& tileset = m_tiledmap->getTileTileset(gid);

    // storing all needed variables
    std::uint32_t mask = 0x1fffffff;
    std::uint8_t tile_transform = ((gid & ~mask)>>28u);
    auto id = (gid & mask) - tileset->firstgid;
    auto tilewidth = tileset->tilewidth;
    auto tileheight = tileset->tileheight;
    auto x = (tile_count % m_width) * m_tiledmap->getTileSize().x;
    auto y = (tile_count / m_width) * m_tiledmap->getTileSize().y;
    auto tx = (id % tileset->columns) * tilewidth;
    auto ty = (id / tileset->columns) * tileheight;

    // storing animated tiles position for efficient iteration in update
    if (tileset->getTileAnim(id)) {
        m_animated_tiles_pos[gid&mask].index = 0;
        m_animated_tiles_pos[gid&mask].clock.restart();
        m_animated_tiles_pos[gid&mask].positions.push_back({x, y});
    }
    // adding tile data
    m_tiles.emplace_back(id , tile_transform);
    // creating the quad for drawing
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

void TileLayer::update() {
    for (auto& [gid, anim_info] : m_animated_tiles_pos) {
        auto& anim_index = anim_info.index;
        auto& clock = anim_info.clock;
        auto& positions = anim_info.positions;
        const auto& tileset = m_tiledmap->getTileTileset(gid);
        // calculating tile id from gid
        auto id = gid - tileset->firstgid;
        // getting tile anim frames
        const auto& anim_frames = tileset->getTileAnim(id)->frames;
        // go to next anim frame when elapsed time is more than frame duration
        if (clock.getElapsedTime().asMilliseconds() > anim_frames[anim_index].duration) {
            anim_index = (anim_index+1) % anim_frames.size();
            clock.restart();
            auto new_id = anim_frames[anim_index].tileid;
            for (const auto& pos : positions) {
                // calculating tile index in the VertexArray
                auto tile_index = pos.x/m_tiledmap->getTileSize().x + (pos.y/m_tiledmap->getTileSize().y)*m_width;
                // calculating new texture coordinates and updating the VertexArray
                float tx = (new_id % tileset->columns) * tileset->tilewidth;
                float ty = (new_id / tileset->columns) * tileset->tileheight;
                m_vertices[tileset.get()][tile_index*4 + 0].texCoords = {tx, ty};
                m_vertices[tileset.get()][tile_index*4 + 1].texCoords = {tx + tileset->tilewidth, ty};
                m_vertices[tileset.get()][tile_index*4 + 2].texCoords = {tx + tileset->tilewidth, ty + tileset->tileheight};
                m_vertices[tileset.get()][tile_index*4 + 3].texCoords = {tx, ty + tileset->tileheight};
            }
        }
    }
}

void TileLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto& [tileset, vertices] : m_vertices) {
        states.texture = &tileset->getTexture();
        states.transform *= m_transformable.getTransform();
        target.draw(vertices, states);
    }
}
