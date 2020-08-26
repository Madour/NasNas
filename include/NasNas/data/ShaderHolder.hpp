/**
* Created by Modar Nasser on 26/08/2020.
**/

#pragma once

#include <SFML/Graphics.hpp>

namespace ns {

    class ShaderHolder {
    public:
        /**
         * \brief Set the shader to be applied when rendering
         *
         * \param shader The shader
         */
        void setShader(sf::Shader* shader);

        /**
         * \brief Toggle shader
         */
        void toggleShader();

        /**
         * \brief Remove the shader
         *
         * Is the same as calling setShader(nullptr)
         */
        void clearShader();

    protected:
        sf::Shader* m_shader = nullptr;

    private:
        sf::Shader* m_saved_shared = nullptr;
    };

}
