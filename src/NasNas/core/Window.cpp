/**
* Created by Modar Nasser on 22/04/2020.
**/

#include "NasNas/core/Window.hpp"
#include "NasNas/core/App.hpp"
#include "NasNas/data/Config.hpp"

using namespace ns;

void AppWindow::onCreate() {
    sf::RenderTarget::initialize();

    setKeyRepeatEnabled(ns::Config::Window::key_repeat);
    setVerticalSyncEnabled(ns::Config::Window::vertical_sync);
    setMouseCursorVisible(ns::Config::Window::cursor_visible);
    setMouseCursorGrabbed(ns::Config::Window::cursor_grabbed);

    m_clear_color = sf::Color::Black;
}

void AppWindow::onResize() {
    scaleView();
}

auto AppWindow::getUIView() const -> const Camera& {
    return m_ui_view;
}

void AppWindow::setUIView(int v_width, int v_height) {
    m_ui_view = Camera("UI", -1);
    m_ui_view.reset(0, 0, v_width, v_height);
    m_ui_view.resetViewport(0, 0, 1, 1);
}

void AppWindow::scaleView(){
    // wider than base window
    float vp_w = 0, vp_h = 0, vp_x = 0, vp_y = 0;
    float win_w = (float)getSize().x, win_h = (float)getSize().y;
    float screen_ratio = (float)ns::Config::Window::width / (float)ns::Config::Window::height;
    if (win_w / win_h > screen_ratio) {
        vp_w = win_h * screen_ratio / win_w;
        vp_h = 1;
        vp_x = (1 - vp_w) / 2;
        vp_y = 0;
    }
    // higher than usual window
    else {
        vp_w = 1;
        vp_h = win_w / screen_ratio / win_h;
        vp_x = 0;
        vp_y = (1 - vp_h)/2;
    }
    auto new_vp = [&](const FloatRect& vp){
        return FloatRect(
                vp_x + vp.left * (1 - 2 * vp_x), vp_y + vp.top * (1 - 2 * vp_y),
                vp_w * vp.width, vp_h * vp.height
        );
    };
    for (Camera*& cam: app->allCameras()) {
        cam->setViewport(new_vp(cam->m_base_viewport));
    }
    m_ui_view.setViewport(new_vp(m_ui_view.m_base_viewport));
}

auto AppWindow::getClearColor() const -> const sf::Color & {
    return m_clear_color;
}

void AppWindow::setClearColor(const sf::Color& color) {
    m_clear_color = color;
}
