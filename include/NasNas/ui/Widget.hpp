// Created by Modar Nasser on 10/10/2021.

#pragma once

#include <functional>
#include <unordered_map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <NasNas/ui/Callbacks.hpp>
#include <NasNas/ui/Style.hpp>

namespace ns::ui {
    class GuiRoot;
    class Container;

    class Widget : public sf::Drawable, public sf::Transformable {
        friend Container;
    public:
        Widget();

        virtual auto getGlobalBounds() const -> sf::FloatRect = 0;
        void setCallback(Callback cb_type, std::function<void(Widget*)> cb);
        void setStyle(const Style& widget_style);

        auto isHovered() const -> bool { return m_hovered; }
        auto isFocused() const -> bool { return m_focused; }

    protected:
        GuiRoot* m_root = nullptr;
        Container* m_parent = nullptr;

        Style m_style;
        bool m_iscontainer = false;

    private:
        void call(Callback cb_type);
        std::unordered_map<Callback, std::function<void(Widget*)>> m_default_callbacks;
        std::unordered_map<Callback, std::function<void(Widget*)>> m_user_callbacks;

        bool m_hovered = false;
        bool m_focused = false;
    };

}
