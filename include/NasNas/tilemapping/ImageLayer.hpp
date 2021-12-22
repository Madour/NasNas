// Created by Modar Nasser on 06/09/2021.

#pragma once

#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <NasNas/tilemapping/Layer.hpp>

namespace ns::tm {
    class TiledMap;

    class ImageLayer : public Layer {
    public:
        ImageLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap);
        ~ImageLayer() override;

        auto getTexture() const -> const sf::Texture&;
        auto getSize() const -> sf::Vector2i;
    private:
        std::string m_image_source;
        int m_width;
        int m_height;
        sf::Texture* m_texture;

        void draw(sf::RenderTarget&, sf::RenderStates) const override;
    };
}
