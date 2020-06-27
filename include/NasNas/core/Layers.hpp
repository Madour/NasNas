/**
* Created by Modar Nasser on 15/04/2020.
**/

#pragma once

#include <SFML/Graphics.hpp>
#include "NasNas/data/AppComponent.hpp"

namespace ns {

    class Layer: public sf::Drawable {
        using DrawablesTypes = std::variant<std::shared_ptr<ns::Drawable>, std::shared_ptr<sf::Shape>, std::shared_ptr<sf::Text>>;
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
             * \brief Add a ns::Drawable object to the Layer
             *
             * \param drawable Shared pointer to the ns::Drawable object to add
             */
            void add(const std::shared_ptr<ns::Drawable>& drawable);

            /**
             * \brief Add a sf::Shape object to the Layer
             *
             * \param drawable Shared pointer to the sf::Shape object to add
             */
            void add(const std::shared_ptr<sf::Shape>& drawable);

            /**
             * \brief Add a sf::Text object to the Layer
             *
             * \param drawable Shared pointer to the sf::Text object to add
             */
            void add(const std::shared_ptr<sf::Text>& drawable);

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
            std::string m_name;                     ///< Name of the Layer
            std::vector<DrawablesTypes> m_drawables;///< Vector of all drawables of the Layer

            /**
             * \brief Draws all the drawables of the Layer on the Scene
             *
             * \param target Scene
             * \param states Render states
             */
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
