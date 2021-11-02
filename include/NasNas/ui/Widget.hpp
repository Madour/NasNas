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
        Widget() = default;
        Widget(GuiRoot* root, Container* parent);

        virtual auto getGlobalBounds() const -> sf::FloatRect = 0;
        void setCallback(Callback cb_type, std::function<void(Widget*)> cb);
        void call(Callback cb_type);
        bool m_hovered = false;
        bool m_focused = false;

    protected:
        GuiRoot* m_root = nullptr;
        Container* m_parent = nullptr;
    private:
        std::unordered_map<Callback, std::function<void(Widget*)>> m_callbacks;

    };

}
