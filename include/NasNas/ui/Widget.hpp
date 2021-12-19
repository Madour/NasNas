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
        virtual auto contains(const sf::Vector2f& pos) const -> bool = 0;

        void setCallback(MouseCallback cb_type, std::function<void(Widget*)> cb);

        auto isHovered() const -> bool { return m_hovered; }
        auto isFocused() const -> bool { return m_focused; }

    protected:
        GuiRoot* m_root = nullptr;
        Container* m_parent = nullptr;

        void call(MouseCallback cb_type);
        virtual void call(ClickCallback cb_type);

        enum Type {
            None = 0,
            Parent = 1 << 0,
            Styled = 1 << 1,
            Clickable = 1 << 2
        };
        unsigned m_type = Type::None;

    private:
        std::unordered_map<MouseCallback, std::function<void(Widget*)>> m_default_callbacks;
        std::unordered_map<MouseCallback, std::function<void(Widget*)>> m_user_callbacks;

        bool m_hovered = false;
        bool m_focused = false;
    };

    template <typename T>
    class StyledWidget : virtual public Widget {
    public:
        using Style = T;

        StyledWidget() : Widget() {
            m_type |= Type::Styled;
        }
        T style;
    };

    class ClickableWidget : public virtual Widget {
    public:
        ClickableWidget();

        using Widget::setCallback;
        void setCallback(ClickCallback cb_type, std::function<void(Widget*)> cb);

    private:
        using Widget::call;
        void call(ClickCallback cb_type) override;
        std::unordered_map<ClickCallback, std::function<void(Widget*)>> m_user_callbacks;

    };

}
