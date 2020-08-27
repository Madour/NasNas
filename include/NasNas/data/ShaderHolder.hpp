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
         * \brief Get the current Shader
         * \return Pointer to the current Shader
         */
        auto getShader() -> sf::Shader*;

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

    private:
        sf::Shader* m_shader = nullptr;
        sf::Shader* m_saved_shared = nullptr;
    };

}
