/**
* Created by Modar Nasser on 09/07/2020.
**/


#include "NasNas/tilemapping/TileLayer.hpp"
#include "NasNas/tilemapping/TiledMap.hpp"

using namespace ns;
using namespace ns::tm;

TileLayer::TileLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) :
Layer(xml_node, tiledmap),
m_width(xml_node.attribute("width").as_int()),
m_height(xml_node.attribute("height").as_int())
{
    m_render_texture.create(m_width*m_tiledmap.getTileSize().x, m_height*m_tiledmap.getTileSize().y);
    for (const auto& tileset : m_tiledmap.allTilesets()) {
        m_vertices[&tileset].resize(6u * (size_t)m_width * (size_t)m_height);
        m_vertices[&tileset].setPrimitiveType(sf::PrimitiveType::Triangles);
    }

    m_tiles.resize(m_width*m_height, Tile::None);
    // parsing data
    auto xml_data = xml_node.child("data");
    auto encoding = std::string(xml_data.attribute("encoding").as_string());
    if (encoding == "csv") {
        std::string layer_data_str{xml_data.text().as_string()};
        const char* layer_data = xml_data.text().as_string();
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

    m_render_texture.clear(sf::Color::Transparent);
    for (const auto& [tileset, vertices] : m_vertices) {
        m_render_texture.draw(vertices, sf::RenderStates(&tileset->data.getTexture()));
    }
    m_render_texture.display();
    m_sprite.setTexture(m_render_texture.getTexture());
    m_sprite.setColor(m_tintcolor);
}

auto TileLayer::getTile(int x, int y) const -> const std::optional<Tile>& {
    if (x > m_width || y > m_height) return Tile::None;
    return m_tiles.at(x + y*m_width);
}

auto TileLayer::getTile(sf::Vector2i pos) const -> const std::optional<Tile>& {
    return getTile(pos.x, pos.y);
}

auto TileLayer::getGlobalBounds() const -> ns::FloatRect {
    return m_sprite.getGlobalBounds();
}

void TileLayer::update() {
    for (auto& [gid, anim_info] : m_animated_tiles_pos) {
        auto& anim_index = anim_info.index;

        // getting tile anim frames from tileset
        const auto& tileset = m_tiledmap.getTileTileset(gid);
        const auto& anim_frames = tileset.data.getTileData(gid - tileset.firstgid).animframes;

        // go to next anim frame when elapsed time is more than frame duration
        if (anim_info.clock.getElapsedTime().asMilliseconds() > anim_frames[anim_index].duration) {
            anim_info.clock.restart();
            anim_index = (anim_index+1) % anim_frames.size();
            auto next_id = anim_frames[anim_index].tileid;
            for (const auto& pos : anim_info.positions) {
                // calculating tile index
                auto tile_index = pos.x + pos.y*m_width;
                auto& base_tile = m_tiles[tile_index].value();
                // calculating new texture coordinates and updating the VertexArray
                const auto& tex_coordinates = tileset.data.getTileTexCoo(next_id, base_tile.flip);
                m_vertices[&tileset][tile_index*6 + 0].texCoords = tex_coordinates[0];
                m_vertices[&tileset][tile_index*6 + 1].texCoords = tex_coordinates[1];
                m_vertices[&tileset][tile_index*6 + 2].texCoords = tex_coordinates[2];
                m_vertices[&tileset][tile_index*6 + 3].texCoords = tex_coordinates[2];
                m_vertices[&tileset][tile_index*6 + 4].texCoords = tex_coordinates[3];
                m_vertices[&tileset][tile_index*6 + 5].texCoords = tex_coordinates[0];
            }
        }
    }

    m_render_texture.clear(sf::Color::Transparent);
    for (const auto& [tileset, vertices] : m_vertices) {
        m_render_texture.draw(vertices, sf::RenderStates(&tileset->data.getTexture()));
    }
    m_render_texture.display();
    m_sprite.setTexture(m_render_texture.getTexture());
    m_sprite.setColor(m_tintcolor);
}

void TileLayer::addTile(std::uint32_t gid, int tile_count) {
    if (gid == 0) {
        return;
    }
    // getting tile transformation bits and removing them from the gid
    std::uint32_t mask = 0x1fffffff;
    auto tile_transform = static_cast<Tile::Flip>((gid & ~mask) >> 28u);
    gid = gid & mask;

    // getting the tileset of the tile
    const auto& tileset = m_tiledmap.getTileTileset(gid);
    // storing all needed variables
    auto id = gid - tileset.firstgid;
    auto tilewidth = tileset.data.tilewidth;
    auto tileheight = tileset.data.tileheight;
    auto x = (tile_count % m_width);
    auto y = (tile_count / m_width);
    auto px = static_cast<float>(x * m_tiledmap.getTileSize().x);
    auto py = static_cast<float>(y * m_tiledmap.getTileSize().y);

    // storing animated tiles position for efficient iteration in update
    if (!tileset.data.getTileData(id).animframes.empty()) {
        m_animated_tiles_pos[gid].index = 0;
        m_animated_tiles_pos[gid].clock.restart();
        m_animated_tiles_pos[gid].positions.emplace_back(x, y);
    }
    // adding tile data to tiles vector
    m_tiles[tile_count].emplace(tileset.data.getTileData(id), tileset.data, gid, x, y, tile_transform);
    auto& tile = m_tiles.at(tile_count).value();
    // calculating texture coordnates and creating the quad for drawing
    const auto& tex_coordinates = tile.getTileTexCoo();

    m_vertices[&tileset][tile_count*6 + 0] = {sf::Vector2f(px,           py),            tex_coordinates[0]};
    m_vertices[&tileset][tile_count*6 + 1] = {sf::Vector2f(px+tilewidth, py),            tex_coordinates[1]};
    m_vertices[&tileset][tile_count*6 + 2] = {sf::Vector2f(px+tilewidth, py+tileheight), tex_coordinates[2]};
    m_vertices[&tileset][tile_count*6 + 3] = {sf::Vector2f(px+tilewidth, py+tileheight), tex_coordinates[2]};
    m_vertices[&tileset][tile_count*6 + 4] = {sf::Vector2f(px,           py+tileheight), tex_coordinates[3]};
    m_vertices[&tileset][tile_count*6 + 5] = {sf::Vector2f(px,           py),            tex_coordinates[0]};
}

void TileLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= m_transformable.getTransform();
    target.draw(m_sprite, states);
}
