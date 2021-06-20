/**
* Created by Modar Nasser on 15/04/2020.
**/


#pragma once

#include <variant>
#include <memory>
#include <SFML/Graphics.hpp>
#include "NasNas/core/graphics/DrawableTransformable.hpp"

namespace ns {
    class Scene;

    class Layer {
        using DrawablesSPtrTypes = std::variant<
                std::shared_ptr<const ns::Drawable>,
                std::shared_ptr<const ns::DrawableTransformable>,
                std::shared_ptr<const sf::Shape>,
                std::shared_ptr<const sf::Text>,
                std::shared_ptr<const sf::Sprite>
        >;
    public:
        using DrawablesTypes = std::variant<
                const ns::Drawable*,
                const ns::DrawableTransformable*,
                const sf::Shape*,
                const sf::Text*,
                const sf::Sprite*
        >;

        /**
         * \brief Construct a Layer object
         *
         * A Layer is a container that keep pointers to drawables objects.
         * It is used to organize the order of drawing of multiples drawables.
         *
         * \param name Layer name
         */
        explicit Layer(std::string name);

        Layer(const Layer&) = delete;
        Layer(Layer&&) = default;

        /**
         * \brief Removes all the drawable
         */
        void clear();

        /**
         * \brief Add a drawable to the Layer
         *
         * \param drawable Drawable to add
         */
        void add(const ns::Drawable& drawable);
        void add(const ns::DrawableTransformable& drawable);
        void add(const sf::Shape& drawable);
        void add(const sf::Text& drawable);
        void add(const sf::Sprite& drawable);
        void add(const DrawablesTypes& drawable);

        /**
         * \brief Add a drawable to the layer
         * The pointer is not managed by the Layer,
         * and you have to delete it manually when it is no more used
         *
         * \param drawable Pointer to the drawable to add
         */
        void addRaw(const DrawablesTypes& drawable);


        /**
         * \brief Remove a drawable from the Layer
         *
         * \param drawable Drawable to remove
         */
        void remove(const ns::Drawable& drawable);
        void remove(const ns::DrawableTransformable& drawable);
        void remove(const sf::Shape& drawable);
        void remove(const sf::Text& drawable);
        void remove(const sf::Sprite& drawable);
        void remove(const DrawablesTypes& drawable);

        /**
         * \brief Get a vector of all drawables added to the Layer
         *
         * \return Vector of variant drawables (ns::Drawable, sf::Shape, sf::Text)
         */
        auto getDrawables() const -> const std::vector<DrawablesTypes>&;

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
        auto getName() const -> const std::string&;

    private:
        friend Scene;

        std::string m_name;                        ///< Name of the Layer
        std::vector<DrawablesTypes> m_drawables;   ///< Vector of all drawables of the Layer
        std::vector<DrawablesSPtrTypes> m_gc;
    };

}
