/**
* Created by Modar Nasser on 27/08/2020.
**/


#pragma once


#include "../NasNas.h"

class ShaderInTransition : public ns::Transition {
public:
    explicit ShaderInTransition(std::string  uniform_name);
    void onUpdate() override;

private:
    std::string m_uniform_name;
    sf::Shader* m_shader;
    float m_treshold;
};

class ShaderOutTransition : public ns::Transition {
public:
    explicit ShaderOutTransition(std::string  uniform_name);
    void onUpdate() override;

private:
    std::string m_uniform_name;
    sf::Shader* m_shader;
    float m_treshold;
};