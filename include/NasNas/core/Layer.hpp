/**
* Created by Modar Nasser on 15/04/2020.
**/


#pragma once

#include <functional>
#include <limits>
#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "NasNas/core/data/Rtti.hpp"

namespace ns {
    class Scene;

    class Layer {
    public:
        /**
         * \brief Construct a Layer object
         *
         * A Layer is a container that keep pointers to drawables objects.
         * It is used to organize the order of drawing of multiple drawables.
         *
         * \param name Layer name
         */
        explicit Layer(std::string name);

        Layer(const Layer&) = delete;
        Layer(Layer&&) = default;
        Layer& operator=(const Layer&) = delete;
        Layer& operator=(Layer&&) = default;

        /**
         * \brief Removes all the drawables
         */
        void clear();

        /**
         * \brief Add a drawable to the Layer
         *
         * \param drawable Drawable to add
         */
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<sf::Drawable, T>>>
        void add(const T& dr);

        template <typename T, typename = std::enable_if_t<std::is_pointer_v<T>>, typename = std::enable_if_t<std::is_base_of_v<sf::Drawable, std::remove_pointer_t<T>>>>
        void add(T dr);

        /**
         * \brief Add a drawable to the layer
         * The pointer is not managed by the Layer,
         * and you have to delete it manually after removing it from the Layer
         *
         * \param drawable Pointer to the drawable to add
         */
        template <typename T, typename = std::enable_if_t<std::is_pointer_v<T>>, typename = std::enable_if_t<std::is_base_of_v<sf::Drawable, std::remove_pointer_t<T>>>>
        void addRaw(T dr);

        /**
         * \brief Remove a drawable from the Layer
         *
         * \param drawable Drawable to remove
         */
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<sf::Drawable, T>>>
        void remove(const T& dr);

        template <typename T, typename = std::enable_if_t<std::is_pointer_v<T>>, typename = std::enable_if_t<std::is_base_of_v<sf::Drawable, std::remove_pointer_t<T>>>>
        void remove(T dr);

        /**
         * \brief Get a vector of all drawables added to the Layer
         *
         * \return Vector of const sf::Drawable*
         */
        auto allDrawables() const -> const std::vector<const sf::Drawable*>&;

        auto getDrawablePosition(const sf::Drawable* dr) const -> sf::Vector2f;
        auto getDrawableBounds(const sf::Drawable* dr) const -> sf::FloatRect;

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
        std::string m_name;
        std::vector<const sf::Drawable*> m_drawables;
        std::vector<std::unique_ptr<const sf::Drawable>> m_gc;
        std::unordered_map<const sf::Drawable*, std::function<sf::Vector2f()>> m_position_getters;
        std::unordered_map<const sf::Drawable*, std::function<sf::FloatRect()>> m_bounds_getters;
    };

    template <typename T, typename>
    void Layer::add(const T& dr) {
        static constexpr auto float_min = std::numeric_limits<float>::lowest();
        static constexpr auto float_max = std::numeric_limits<float>::max();

        m_drawables.emplace_back(&dr);
        if constexpr(rtti::has_getPosition_v<T>)
            m_position_getters[&dr] = [&dr]() { return dr.getPosition(); };
        else
            m_position_getters[&dr] = []() { return sf::Vector2f{0, float_min}; };

        if constexpr(rtti::has_getGlobalBounds_v<T>)
            m_bounds_getters[&dr] = [&dr]() { return dr.getGlobalBounds(); };
        else if constexpr(rtti::has_getBounds_v<T>)
            m_bounds_getters[&dr] = [&dr]() { return dr.getBounds(); };
        else
            m_bounds_getters[&dr] = []() { return sf::FloatRect(float_min/2.f, float_min/2.f, float_max, float_max); };
    }

    template <typename T, typename, typename>
    void Layer::add(const T dr) {
        add(*dr);
        m_gc.emplace_back(dr);
    }

    template <typename T, typename, typename>
    void Layer::addRaw(const T dr) {
        add(*dr);
    }

    template <typename T, typename>
    void Layer::remove(const T& dr) {
        auto it = std::find(m_drawables.begin(), m_drawables.end(), &dr);
        if (it != m_drawables.end()) {
            m_drawables.erase(it);
            m_position_getters.erase(&dr);
            m_bounds_getters.erase(&dr);
        }
        else
            std::cout << "Warning : trying to remove a non existant drawable from Layer.\n";
    }

    template <typename T, typename, typename>
    void Layer::remove(const T dr) {
        remove(*dr);
        m_gc.erase(
            std::remove_if(m_gc.begin(), m_gc.end(), [dr](auto& uptr) { return uptr.get() == dr; }),
            m_gc.end()
        );
    }

}
