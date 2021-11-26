// Created by Modar Nasser on 10/10/2021.

#include <utility>

#include <NasNas/ui/Widget.hpp>

using namespace ns;
using namespace ns::ui;

Widget::Widget() {
    m_default_callbacks[Callback::onHover] = [](Widget* w) { w->m_hovered = true; };
    m_default_callbacks[Callback::onUnhover] = [](Widget* w) { w->call(Callback::onUnfocus); w->m_hovered = false; };
    m_default_callbacks[Callback::onFocus] = [](Widget* w) { w->m_focused = true; };
    m_default_callbacks[Callback::onUnfocus] = [](Widget* w) { w->m_focused = true; };
}


void Widget::setCallback(Callback cb_type, std::function<void(Widget*)> cb) {
    m_user_callbacks[cb_type] = std::move(cb);
}

void Widget::setStyle(const Style& widget_style) {
    m_style = widget_style;
}

void Widget::call(Callback cb_type) {
    if (m_default_callbacks.find(cb_type) != m_default_callbacks.end())
        m_default_callbacks.at(cb_type)(this);
    if (m_user_callbacks.find(cb_type) != m_user_callbacks.end())
        m_user_callbacks.at(cb_type)(this);
}
