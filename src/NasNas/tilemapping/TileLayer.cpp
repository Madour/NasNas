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
    // create tile vertices that will be rendered
    for (const auto& tileset : m_tiledmap->allTilesets()) {
        m_vertices[&tileset].resize(6u * (size_t)m_width * (size_t)m_height);
        m_vertices[&tileset].setPrimitiveType(sf::PrimitiveType::Triangles);
    }
    // create the tiles
    m_tiles.reserve(m_width*m_height);
    for (int i = 0; i < m_width*m_height; ++i)
        m_tiles.emplace_back(Tile::None);

    auto xml_data = xml_node.child("data");
    auto encoding = std::string(xml_data.attribute("encoding").as_string());
    if (encoding != "csv") {
        std::cout << "Encoding «" << encoding << "» is not supported, please use CSV instead." << std::endl;
        exit(-1);
    }
    // parse data and set the tiles
    const char* layer_data = xml_data.text().as_string();
    std::uint32_t current_gid = 0;
    int tile_counter = 0;
    while (*layer_data != '\0') {
        switch (*layer_data) {
            case '\n':
                break;
            case ',':
                addTile(tile_counter, current_gid);
                current_gid = 0;
                tile_counter ++;
                break;
            default:
                current_gid *= 10;
                current_gid += *layer_data - '0';
        }
        layer_data++;
    }
    addTile(tile_counter, current_gid);

    // create the render texture
    m_render_texture.create(m_width*m_tiledmap->getTileSize().x, m_height*m_tiledmap->getTileSize().y);
}

auto TileLayer::getTile(int x, int y) const -> const std::optional<Tile>& {
    if (x > m_width || y > m_height) return Tile::None;
    return m_tiles.at(x + y*m_width);
}

auto TileLayer::getTile(sf::Vector2i pos) const -> const std::optional<Tile>& {
    return getTile(pos.x, pos.y);
}

void TileLayer::setTile(int x, int y, std::uint32_t gid) {
    if (gid == 0) {
        return;
    }
    // get tile transformation
    auto tile_flip = Tile::getFlipFromGid(gid);
    gid = gid & Tile::gidmask;

    // get tile tileset, id and index
    const auto& tileset = m_tiledmap->getTileTileset(gid);
    auto id = gid - tileset.firstgid;
    auto tile_index = x + y*m_width;

    // if tile is animated, update animation positions
    auto old_gid = getTile(x, y)->gid;
    if (m_animated_tiles_pos.count(old_gid) > 0) {
        auto& v = m_animated_tiles_pos.at(old_gid).positions;
        v.erase(std::remove(v.begin(), v.end(), sf::Vector2u(x, y)), v.end());
    }
    if (!tileset.data.getTileData(id).animframes.empty()) {
        m_animated_tiles_pos[gid].index = 0;
        m_animated_tiles_pos[gid].clock.restart();
        m_animated_tiles_pos[gid].positions.emplace_back(x, y);
    }

    // update the tile
    m_tiles[tile_index].emplace(tileset.data.getTileData(id), tileset.data, gid, x, y, tile_flip);
    // update tile texture coordinates
    const auto& tex_coordinates = m_tiles.at(tile_index)->getTileTexCoo();
    updateTileTexCoo(tileset, tile_index, tex_coordinates);
}

void TileLayer::update() {
    for (auto& [gid, anim_info] : m_animated_tiles_pos) {
        auto& anim_index = anim_info.index;

        // get tileset and animation frames
        const auto& tileset = m_tiledmap->getTileTileset(gid);
        const auto& anim_frames = tileset.data.getTileData(gid - tileset.firstgid).animframes;

        // go to next anim frame when elapsed time is more than frame duration
        if (anim_info.clock.getElapsedTime().asMilliseconds() > anim_frames[anim_index].duration) {
            anim_info.clock.restart();
            anim_index = (anim_index+1) % anim_frames.size();
            auto next_id = anim_frames[anim_index].tileid;
            // for each position where this animated tile is on the map
            for (const auto& pos : anim_info.positions) {
                auto tile_index = pos.x + pos.y*m_width;
                auto tile_flip = m_tiles[tile_index]->flip;
                // update next frame texture coordinates
                const auto& tex_coordinates = tileset.data.getTileTexCoo(next_id, tile_flip);
                updateTileTexCoo(tileset, tile_index, tex_coordinates);
            }
        }
    }
}

void TileLayer::addTile(int tile_index, std::uint32_t gid) {
    if (gid == 0) {
        return;
    }
    const auto& tileset = m_tiledmap->getTileTileset(gid&0x1fffffff);
    auto x = tile_index % m_width;
    auto y = tile_index / m_width;
    auto px = static_cast<float>(x * m_tiledmap->getTileSize().x);
    auto py = static_cast<float>(y * m_tiledmap->getTileSize().y);
    auto tilewidth = tileset.data.tilewidth;
    auto tileheight = tileset.data.tileheight;

    m_vertices[&tileset][tile_index*6 + 0].position = sf::Vector2f(px, py);
    m_vertices[&tileset][tile_index*6 + 1].position = sf::Vector2f(px+tilewidth, py);
    m_vertices[&tileset][tile_index*6 + 2].position = sf::Vector2f(px+tilewidth, py+tileheight);
    m_vertices[&tileset][tile_index*6 + 3].position = sf::Vector2f(px+tilewidth, py+tileheight);
    m_vertices[&tileset][tile_index*6 + 4].position = sf::Vector2f(px, py+tileheight);
    m_vertices[&tileset][tile_index*6 + 5].position = sf::Vector2f(px, py);

    setTile(x, y, gid);
}

void TileLayer::updateTileTexCoo(const Tileset& tileset, unsigned tile_index, const std::vector<sf::Vector2f>& tex_coo) {
    m_vertices[&tileset][tile_index*6 + 0].texCoords = tex_coo[0];
    m_vertices[&tileset][tile_index*6 + 1].texCoords = tex_coo[1];
    m_vertices[&tileset][tile_index*6 + 2].texCoords = tex_coo[2];
    m_vertices[&tileset][tile_index*6 + 3].texCoords = tex_coo[2];
    m_vertices[&tileset][tile_index*6 + 4].texCoords = tex_coo[3];
    m_vertices[&tileset][tile_index*6 + 5].texCoords = tex_coo[0];
}

void TileLayer::render() {
    m_render_texture.clear(sf::Color::Transparent);
    for (const auto& [tileset, vertices] : m_vertices) {
        m_render_texture.draw(vertices, sf::RenderStates(&tileset->data.getTexture()));
    }
    m_render_texture.display();
    m_sprite.setTexture(m_render_texture.getTexture());
    m_sprite.setColor(getTintColor());
}

void TileLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}
