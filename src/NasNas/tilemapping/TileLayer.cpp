/**
* Created by Modar Nasser on 09/07/2020.
**/


#include "NasNas/tilemapping/TileLayer.hpp"

using namespace ns;
using namespace ns::tm;

TileLayer::TileLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) :
Layer(xml_node, tiledmap) {
    m_width = xml_node.attribute("width").as_uint();
    m_height = xml_node.attribute("height").as_uint();
    m_tiles.reserve((size_t)m_width * (size_t)m_height);
    for (const auto& tileset : m_tiledmap->allTilesets()) {
        m_vertices[tileset.get()].resize(4u * (size_t)m_width * (size_t)m_height);
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

auto TileLayer::getGlobalBounds() -> ns::FloatRect {
    return ns::FloatRect(getPosition().x, getPosition().y, m_width * m_tiledmap->getTileSize().x, m_height * m_tiledmap->getTileSize().y);
}

void TileLayer::move(float offsetx, float offsety) {
    m_transformable.move(offsetx, offsety);
}

void TileLayer::update() {
    for (auto& [gid, anim_info] : m_animated_tiles_pos) {
        auto& anim_index = anim_info.index;

        // getting tile anim frames from tileset
        const auto& tileset = m_tiledmap->getTileTileset(gid);
        const auto& anim_frames = tileset->getTileAnim(gid - tileset->firstgid)->frames;

        // go to next anim frame when elapsed time is more than frame duration
        if (anim_info.clock.getElapsedTime().asMilliseconds() > anim_frames[anim_index].duration) {
            anim_index = (anim_index+1) % anim_frames.size();
            anim_info.clock.restart();
            auto new_id = anim_frames[anim_index].tileid;
            for (const auto& pos : anim_info.positions) {
                // calculating tile index
                auto tile_index = pos.x/m_tiledmap->getTileSize().x + (pos.y/m_tiledmap->getTileSize().y)*m_width;
                // calculating new texture coordinates and updating the VertexArray
                const auto& tex_coordinates = getTileTexCoo(new_id+tileset->firstgid, m_tiles[tile_index].flip);
                m_vertices[tileset.get()][tile_index*4 + 0].texCoords = tex_coordinates[0];
                m_vertices[tileset.get()][tile_index*4 + 1].texCoords = tex_coordinates[1];
                m_vertices[tileset.get()][tile_index*4 + 2].texCoords = tex_coordinates[2];
                m_vertices[tileset.get()][tile_index*4 + 3].texCoords = tex_coordinates[3];
            }
        }
    }
}

void TileLayer::addTile(std::uint32_t gid, unsigned int tile_count) {
    if (gid == 0) {
        m_tiles.emplace_back(0, 0);
        return;
    }
    // getting tile transformation bits and removing them from the gid
    std::uint32_t mask = 0x1fffffff;
    std::uint8_t tile_transform = ((gid & ~mask)>>28u);
    gid = gid & mask;

    // getting the tileset of the tile
    const auto& tileset = m_tiledmap->getTileTileset(gid);
    // storing all needed variables
    auto id = gid - tileset->firstgid;
    auto tilewidth = tileset->tilewidth;
    auto tileheight = tileset->tileheight;
    auto x = (tile_count % m_width) * m_tiledmap->getTileSize().x;
    auto y = (tile_count / m_width) * m_tiledmap->getTileSize().y;

    // storing animated tiles position for efficient iteration in update
    if (tileset->getTileAnim(id)) {
        m_animated_tiles_pos[gid&mask].index = 0;
        m_animated_tiles_pos[gid&mask].clock.restart();
        m_animated_tiles_pos[gid&mask].positions.emplace_back(x, y);
    }
    // adding tile data to tiles vector
    m_tiles.emplace_back(gid , tile_transform);
    // calculating texture coordnates and creating the quad for drawing
    const auto& tex_coordinates = getTileTexCoo(m_tiles[tile_count]);
    m_vertices[tileset.get()][tile_count*4 + 0] = sf::Vertex(sf::Vector2f(x, y), tex_coordinates[0]);
    m_vertices[tileset.get()][tile_count*4 + 1] = sf::Vertex(sf::Vector2f(x + tilewidth, y), tex_coordinates[1]);
    m_vertices[tileset.get()][tile_count*4 + 2] = sf::Vertex(sf::Vector2f(x + tilewidth, y + tileheight), tex_coordinates[2]);
    m_vertices[tileset.get()][tile_count*4 + 3] = sf::Vertex(sf::Vector2f(x, y + tileheight), tex_coordinates[3]);
}

auto TileLayer::getTileTexCoo(const TileLayer::Tile& tile) -> std::vector<sf::Vector2f> {
    return getTileTexCoo(tile.gid, tile.flip);
}

auto TileLayer::getTileTexCoo(std::uint32_t gid, std::uint8_t transformation) -> std::vector<sf::Vector2f> {
    const auto& tileset = m_tiledmap->getTileTileset(gid);
    auto id = gid - tileset->firstgid;
    auto tx = (id % tileset->columns) * (tileset->tilewidth + tileset->spacing) + tileset->margin;
    auto ty = (id / tileset->columns) * (tileset->tileheight + tileset->spacing) + tileset->margin;

    auto res = std::vector<sf::Vector2f>(4);
    res[0] = sf::Vector2f(tx, ty);
    res[1] = sf::Vector2f(tx + tileset->tilewidth, ty);
    res[2] = sf::Vector2f(tx + tileset->tilewidth, ty + tileset->tileheight);
    res[3] = sf::Vector2f(tx, ty + tileset->tileheight);

    if (transformation & (std::uint8_t)TileTransformation::VerticalFlip) {
        auto temp = res[0];
        res[0].y = res[3].y; res[1].y = res[2].y;
        res[3].y = temp.y; res[2].y = temp.y;
    }
    if (transformation & (std::uint8_t)TileTransformation::HorizontalFlip) {

        auto temp = res[0];
        res[0].x = res[1].x; res[1].x = temp.x;
        res[3].x = res[0].x; res[2].x = res[1].x;
    }
    if (transformation & (std::uint8_t)TileTransformation::DiagonalFlip) {
        int i1 = 1, i2 = 3;
        if (transformation == (std::uint8_t)TileTransformation::Rotation90 ||
            transformation == (std::uint8_t)TileTransformation::Rotation270) {
            i1 = 0; i2 = 2;
        }
        auto temp = res[i1];
        res[i1] = res[i2];
        res[i2] = temp;
    }
    return res;
}

void TileLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= m_transformable.getTransform();
    for (const auto& [tileset, vertices] : m_vertices) {
        states.texture = &tileset->getTexture();
        target.draw(vertices, states);
    }
}
