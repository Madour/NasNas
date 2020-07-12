/**
* Created by Modar Nasser on 25/04/2020.
**/


#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "NasNas/core/Anim.hpp"

namespace ns {

    class Spritesheet {
    public:
        /**
         * \brief Constructs a Spritesheet object
         *
         * \param name Spritesheet name
         * \param texture Spritesheet texture
         * \param anims Spritesheet animations, vector of pointers to Anim objects
         */
        Spritesheet(std::string  name, const sf::Texture& texture, const std::vector<Anim*>& anims);

        /**
         * \brief Delete all the Anim objects of this Spritesheet
         */
        ~Spritesheet();

        /**
         * \brief Get a map containing all the Anim objects
         * \return Unordered map of <Anim name, pointer to Anim>
         */
        auto getAnimsMap() -> const std::unordered_map<std::string, Anim*>&;

        /**
         * \brief Get an Anim by its name
         * \param anim_name Anim name
         * \return The Anim
         */
        auto getAnim(const std::string& anim_name) -> const Anim&;

        const std::string name;     ///< Anim name
        const sf::Texture* texture; ///< Anim texture

    private:
        /// Anim map containing all the Anim objects in the spritesheet
        std::unordered_map<std::string, Anim*> m_anims_map;
    };

}
