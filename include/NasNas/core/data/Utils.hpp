/**
* Created by Modar Nasser on 10/11/2020.
**/

#pragma once

#include <string>
#include <functional>
#include "NasNas/core/data/Rect.hpp"

namespace ns::utils {

    namespace path {
        auto getFilename(const std::string& path) -> std::string;
        auto getStem(const std::string& path) -> std::string;
        auto getExtension(const std::string& path) -> std::string;
        auto getPath(const std::string& path) -> std::string;
        void removeFilename(std::string& path);
    }

    struct bool_switch {
        bool_switch(std::function<void()>  on_true, std::function<void()>  on_false);
        virtual auto operator=(bool value) -> bool_switch&;
        auto operator=(const bool_switch& other) -> bool_switch&;
        virtual explicit operator bool() const;
    protected:
        bool m_val;
        std::function<void()> m_on_true;
        std::function<void()> m_on_false;
    };

    auto getRandomFloat(float min, float max) -> float;
    auto getRandomInt(int min, int max) -> int;

    /**
     * \brief Compute the union between multiple FloatRect
     * \param rects list of FloatRects
     * \return The FloatRect containings all the rects
     */
    auto computeBounds(std::initializer_list<sf::FloatRect> rects) -> ns::FloatRect;
}
