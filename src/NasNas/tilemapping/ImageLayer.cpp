// Created by Modar Nasser on 06/09/2021.

#include <NasNas/tilemapping/ImageLayer.hpp>

#include <SFML/Graphics/Sprite.hpp>

#include <NasNas/thirdparty/pugixml.hpp>
#include <NasNas/tilemapping/TiledMap.hpp>

#ifdef NS_RESLIB
#include <NasNas/reslib/ResourceManager.hpp>
#endif

using namespace ns;
using namespace ns::tm;

ImageLayer::ImageLayer(const pugi::xml_node& xml_node, ns::tm::TiledMap* tiledmap) :
Layer(xml_node, tiledmap),
m_width(xml_node.child("image").attribute("width").as_int()),
m_height(xml_node.child("image").attribute("height").as_int()),
m_image_source(xml_node.child("image").attribute("source").as_string())
{
#ifdef NS_RESLIB
    m_texture = &ns::Res::getTexture(tiledmap->getTMXFilePath() + m_image_source);
#else
    m_texture = new sf::Texture();
    m_texture->loadFromFile(tiledmap->getTMXFilePath() + m_image_source);
#endif
}


ImageLayer::~ImageLayer()
#ifdef NS_RESLIB
= default;
#else
{
    if(m_texture && m_texture->getSize().x > 0 && m_texture->getSize().y > 0) {
        delete (m_texture);
        m_texture = nullptr;
    }
}
#endif

auto ImageLayer::getTexture() const -> const sf::Texture& {
    return *m_texture;
}

auto ImageLayer::getSize() const -> sf::Vector2i {
    return {m_width, m_height};
}

void ImageLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sf::Sprite(*m_texture), states);
}
