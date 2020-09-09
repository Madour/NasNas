/**
* Created by Modar Nasser on 15/04/2020.
**/


#pragma once

#include <variant>
#include <memory>
#include <SFML/Graphics.hpp>
#include "NasNas/data/Drawable.hpp"

#ifdef NS_TILEMAPPING
#include "NasNas/tilemapping/TileLayer.hpp"
#include "NasNas/tilemapping/ObjectLayer.hpp"
#endif

namespace ns {

    using LayerDrawablesTypes = std::variant<
            std::shared_ptr<ns::Drawable>,
            std::shared_ptr<sf::Shape>,
            std::shared_ptr<sf::Text>,
            std::shared_ptr<sf::Sprite>,
            ns::Drawable*,
            sf::Shape*,
            sf::Text*,
            sf::Sprite*
    >;

    class Layer {
    public:
        /**
         * \brief Construct a Layer object
         *
         * A Layer is a container that keep pointers to drawables objects.
         * It is used to organize the order of drawing of multiples drawables.
         *
         * \param name Layer name
         */
        explicit Layer(const std::string& name);

        /**
         * \brief Removes all the drawable
         */
        void clear();

        /**
         * \brief Add a drawable to the Layer
         *
         * \param drawable Drawable to add
         */
        void add(const LayerDrawablesTypes& drawable);

        /**
         * \brief Remove a drawable from the Layer
         *
         * \param drawable Drawable to remove
         */
        void remove(const LayerDrawablesTypes& drawable);

        /**
         * \brief Get a vector of all drawables added to the Layer
         *
         * \return Vector of variant drawables (ns::Drawable, sf::Shape, sf::Text)
         */
        auto getDrawables() -> std::vector<LayerDrawablesTypes>&;

        /**
         * \brief Sorts Layer drawables by their Y coordinate
         *
         * `ySort` can be used to perform Z ordring for top down games
         */
        void ySort();

        /**
         * \brief Get the name of the Layer
         *
         * \return Name of the Layer
         */
        auto getName() -> const std::string&;

    private:
        std::string m_name;                          ///< Name of the Layer
        std::vector<LayerDrawablesTypes> m_drawables;///< Vector of all drawables of the Layer
    };

}
