/**
* Created by Modar Nasser on 27/08/2020.
**/

#include "ShaderTransition.hpp"

#include <utility>

using namespace ns;

ShaderInTransition::ShaderInTransition(std::string  uniform_name) :
        m_uniform_name(std::move(uniform_name)),
m_shader(app().getShader()),
m_treshold(1.f)
{}

void ShaderInTransition::onUpdate() {
    m_treshold -= 0.025f;
    if (m_treshold <= 0.25)
        end();
    if (m_shader)
        m_shader->setUniform(m_uniform_name, m_treshold);
}

ShaderOutTransition::ShaderOutTransition(std::string  uniform_name) :
        m_uniform_name(std::move(uniform_name)),
        m_shader(app().getShader()),
        m_treshold(0.25)
{}

void ShaderOutTransition::onUpdate() {
    m_treshold += 0.025f;
    if (m_treshold >= 1.5)
        end();
    if (m_shader)
        m_shader->setUniform(m_uniform_name, m_treshold);
}
