/**
* Created by Modar Nasser on 25/04/2020.
**/


#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <NasNas/core/graphics/Anim.hpp>

namespace ns {

    class Spritesheet {
    public:

        Spritesheet() = default;

        explicit Spritesheet(const sf::Texture& texture);

        /**
         * \brief Constructs a Spritesheet object
         *
         * \param name Spritesheet name
         * \param texture Spritesheet texture
         * \param anims Spritesheet animations, vector of pointers to Anim objects
         */
        Spritesheet(const sf::Texture& texture, const std::vector<Anim*>& anims);

        /**
         * \brief Delete all the Anim objects of this Spritesheet
         */
        ~Spritesheet();

        void setTexture(const sf::Texture& texture);

        auto getTexture() const -> const sf::Texture*;

        void setGrid(const sf::Vector2i& cell_size, int columns_nb, int margin=0, int spacing=0);

        void addAnim(Anim* new_anim);

        void addAnim(const std::string& anim_name, unsigned int first_frame, unsigned int nb_of_frames, int duration, const sf::Vector2i& origin={0,0});
        void addAnim(const std::string& anim_name, unsigned int first_frame, unsigned int nb_of_frames, int duration, const std::vector<sf::Vector2i>& origins);
        void addAnim(const std::string& anim_name, unsigned int first_frame, unsigned int nb_of_frames, const std::vector<int>& durations, const sf::Vector2i& origin={0,0});
        void addAnim(const std::string& anim_name, unsigned int first_frame, unsigned int nb_of_frames, const std::vector<int>& durations, const std::vector<sf::Vector2i>& origins);

        void addAnim(const std::string& anim_name, const std::vector<unsigned int>& frames, int duration, const sf::Vector2i& origin={0,0});
        void addAnim(const std::string& anim_name, const std::vector<unsigned int>& frames, int duration, const std::vector<sf::Vector2i>& origins);
        void addAnim(const std::string& anim_name, const std::vector<unsigned int>& frames, const std::vector<int>& durations, const sf::Vector2i& origin={0,0});
        void addAnim(const std::string& anim_name, const std::vector<unsigned int>& frames, const std::vector<int>& durations, const std::vector<sf::Vector2i>& origins);

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

    private:
        const sf::Texture* m_texture = nullptr; ///< Spritesheet texture
        std::unordered_map<std::string, Anim*> m_anims_map;
        sf::Vector2i m_cell_size;
        int m_margin = 0;
        int m_spacing = 0;
        int m_columns = 1;

        auto getFrameTexCoords(unsigned int frame_index) const -> sf::Vector2i;
    };

}
