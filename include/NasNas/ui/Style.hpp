// Created by Modar Nasser on 26/11/2021.

#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

#include <NasNas/ui/Region.hpp>


namespace ns::ui {
    namespace internal {
        template <typename T>
        struct shared_ptr : private std::shared_ptr<T> {
            shared_ptr() = default;

            shared_ptr(T* ptr) {
                this->reset(ptr);
            }

            auto operator=(T* ptr) -> shared_ptr<T>& {
                this->reset(ptr);
                return *this;
            }

            using std::shared_ptr<T>::operator bool;
            using std::shared_ptr<T>::operator->;
            using std::shared_ptr<T>::operator*;
        };
    }

    namespace style {
        struct Basic {
        private:
            struct Padding {
                float left = 0.f;
                float top = 0.f;
                float right = 0.f;
                float bottom = 0.f;
                auto topleft() const -> sf::Vector2f { return {left, top}; }
                auto bottomright() const -> sf::Vector2f { return {right, bottom}; }
            };
        public:
            Padding padding{};
            sf::Drawable* drawable = nullptr;
        };

        struct Button : Basic {
            sf::Drawable* drawable_hovered = nullptr;
            sf::Drawable* drawable_focused = nullptr;
            internal::shared_ptr<Region> region;
        };
    }

    enum class TextAlign {
        Left,
        Center,
        Right
    };
}
