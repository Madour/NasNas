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

    class Layer {
        using DrawablesTypes = std::variant<
                std::shared_ptr<ns::Drawable>,
                std::shared_ptr<ns::DrawableTransformable>,
                std::shared_ptr<sf::Shape>,
                std::shared_ptr<sf::Text>,
                std::shared_ptr<sf::Sprite>,
                ns::Drawable*,
                ns::DrawableTransformable*,
                sf::Shape*,
                sf::Text*,
                sf::Sprite*
        >;
        using DrawablesSharedTypes = std::variant<
                std::shared_ptr<ns::Drawable>,
                std::shared_ptr<ns::DrawableTransformable>,
                std::shared_ptr<sf::Shape>,
                std::shared_ptr<sf::Text>,
                std::shared_ptr<sf::Sprite>
        >;
        using DrawablesRawTypes = std::variant<
                ns::Drawable*,
                ns::DrawableTransformable*,
                sf::Shape*,
                sf::Text*,
                sf::Sprite*
        >;
    public:
        /**
         * \brief Construct a Layer object
         *
         * A Layer is a container that keep pointers to drawables objects.
         * It is used to organize the order of drawing of multiples drawables.
         *
         * \param name Layer name
         */
        explicit Layer(std::string name);

        /**
         * \brief Removes all the drawable
         */
        void clear();

        /**
         * \brief Add a drawable to the Layer
         *
         * \param drawable Shared pointer to the drawable to add
         */
        void add(const DrawablesSharedTypes& drawable);

        /**
         * \brief Add a drawable to the Layer
         * The pointer is managed by the Layer
         *
         * \param drawable Pointer to the drawable to add
         */
        void add(const DrawablesRawTypes& drawable);

        /**
         * \brief Add a drawable to the layer
         * The pointer is not managed by the Layer,
         * and you have to delete it manually when it is no more used
         *
         * \param drawable Pointer to the drawable to add
         */
        void addRaw(const DrawablesRawTypes& drawable);

        /**
         * \brief Remove a drawable from the Layer
         *
         * \param drawable Drawable to remove
         */
        void remove(const DrawablesTypes& drawable);

        /**
         * \brief Get a vector of all drawables added to the Layer
         *
         * \return Vector of variant drawables (ns::Drawable, sf::Shape, sf::Text)
         */
        auto getDrawables() -> std::vector<DrawablesTypes>&;

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
        std::vector<DrawablesTypes> m_drawables;///< Vector of all drawables of the Layer
    };

}
