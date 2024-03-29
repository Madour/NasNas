/**
* Created by Modar Nasser on 26/08/2020.
**/

#include <NasNas/core/data/ShaderHolder.hpp>

#include <SFML/Graphics/Shader.hpp>

using namespace ns;

void ShaderHolder::setShader(sf::Shader* shader) {
    m_shader = shader;
}

auto ShaderHolder::getShader() const -> sf::Shader* {
    return m_shader;
}

void ShaderHolder::toggleShader() {
    if (m_shader) {
        m_saved_shared = m_shader;
        m_shader = nullptr;
    }
    else {
        m_shader = m_saved_shared;
        m_saved_shared = nullptr;
    }
}

void ShaderHolder::clearShader() {
    m_shader = nullptr;
}
