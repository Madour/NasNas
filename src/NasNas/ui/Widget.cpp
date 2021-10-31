// Created by Modar Nasser on 10/10/2021.

#include <NasNas/ui/Widget.hpp>

using namespace ns;
using namespace ns::ui;

void Widget::setCallback(Callback cb_type, std::function<void(Widget*)> cb) {
    m_callbacks[cb_type] = cb;
}

void Widget::call(Callback cb_type) {
    if (m_callbacks.find(cb_type) != m_callbacks.end())
        m_callbacks.at(cb_type)(this);
}
