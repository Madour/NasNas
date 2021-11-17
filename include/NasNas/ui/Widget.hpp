// Created by Modar Nasser on 10/10/2021.

#pragma once

#include <functional>
#include <unordered_map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <NasNas/ui/Callbacks.hpp>

namespace ns::ui {
    class GuiRoot;
    class Container;

    class Widget : public sf::Drawable, public sf::Transformable {
        friend Container;
    public:
        Widget();

        virtual auto getGlobalBounds() const -> sf::FloatRect = 0;
        void setCallback(Callback cb_type, std::function<void(Widget*)> cb);

        GuiRoot* m_root = nullptr;
        Container* m_parent = nullptr;

        bool m_hovered = false;
        bool m_focused = false;
        bool m_iscontainer = false;

    private:
        void call(Callback cb_type);
        std::unordered_map<Callback, std::function<void(Widget*)>> m_default_callbacks;
        std::unordered_map<Callback, std::function<void(Widget*)>> m_user_callbacks;
    };

}
