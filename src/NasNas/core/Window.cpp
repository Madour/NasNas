/**
* Created by Modar Nasser on 22/04/2020.
**/


#include "NasNas/core/Window.hpp"
#include "NasNas/core/App.hpp"

using namespace ns;

void AppWindow::onCreate() {
    sf::RenderTarget::initialize();

    setKeyRepeatEnabled(ns::Config::Window::key_repeat);
    setVerticalSyncEnabled(ns::Config::Window::vertical_sync);
    setMouseCursorVisible(ns::Config::Window::cursor_visible);
    setMouseCursorGrabbed(ns::Config::Window::cursor_grabbed);

    m_app_view.reset({0, 0, (float)ns::Config::Window::view_width, (float)ns::Config::Window::view_height});
    m_screen_view.reset({0, 0, (float)getSize().x, (float)getSize().y});

    m_clear_color = sf::Color::Black;
    scaleView();
}

void AppWindow::onResize() {
    scaleView();
}

auto AppWindow::getAppView() const -> const sf::View& {
    return m_app_view;
}

auto AppWindow::getScreenView() const -> const sf::View& {
    return m_screen_view;
}

void AppWindow::scaleView(){
    // wider than base window
    float vp_w, vp_h, vp_x, vp_y;
    float win_w = (float)getSize().x, win_h = (float)getSize().y;
    float screen_ratio = (float)ns::Config::Window::width / (float)ns::Config::Window::height;
    if (win_w / win_h > screen_ratio) {
        vp_w = win_h * screen_ratio / win_w;
        vp_x = (1 - vp_w) / 2;
        vp_h = 1;
        vp_y = 0;
    }
    // higher than usual window
    else {
        vp_w = 1;
        vp_x = 0;
        vp_h = win_w / screen_ratio / win_h;
        vp_y = (1 - vp_h)/2;
    }
    m_app_view.setViewport({vp_x, vp_y, vp_w, vp_h});
    m_screen_view.reset({0, 0, win_w, win_h});
}

auto AppWindow::getClearColor() const -> const sf::Color& {
    return m_clear_color;
}

void AppWindow::setClearColor(const sf::Color& color) {
    m_clear_color = color;
}
