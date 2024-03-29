// Created by Modar Nasser on 10/10/2021.

#include <NasNas/ui/Widget.hpp>

using namespace ns;
using namespace ns::ui;

Widget::Widget() {
    m_default_callbacks[CursorCallback::onHover] = [](Widget* w) { w->m_hovered = true; };
    m_default_callbacks[CursorCallback::onUnhover] = [](Widget* w) { w->call(CursorCallback::onUnfocus); w->m_hovered = false; };
    m_default_callbacks[CursorCallback::onFocus] = [](Widget* w) { w->m_focused = true; };
    m_default_callbacks[CursorCallback::onUnfocus] = [](Widget* w) { w->m_focused = false; };
}

void Widget::setCallback(CursorCallback cb_type, std::function<void(Widget*)> cb) {
    m_user_callbacks[cb_type] = std::move(cb);
}

void Widget::call(CursorCallback cb_type) {
    if (m_default_callbacks.find(cb_type) != m_default_callbacks.end())
        m_default_callbacks.at(cb_type)(this);
    if (m_user_callbacks.find(cb_type) != m_user_callbacks.end())
        m_user_callbacks.at(cb_type)(this);
}

void Widget::call(ClickCallback cb_type) {}

ClickableWidget::ClickableWidget() : Widget() {
    m_type |= Type::Clickable;
}

void ClickableWidget::setCallback(ClickCallback cb_type, std::function<void(Widget*)> cb) {
    m_user_callbacks[cb_type] = std::move(cb);
}

void ClickableWidget::call(ClickCallback cb_type) {
    if (m_user_callbacks.find(cb_type) != m_user_callbacks.end())
        m_user_callbacks.at(cb_type)(this);
}
