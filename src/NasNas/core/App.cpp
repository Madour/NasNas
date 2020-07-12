/**
* Created by Modar Nasser on 15/04/2020.
**/


#include "NasNas/core/App.hpp"

using namespace ns;

App::App()
: App(
    ns::Config::Window::title,
    ns::Config::Window::width,
    ns::Config::Window::height,
    ns::Config::Window::view_width,
    ns::Config::Window::view_height,
    ns::Config::Window::framerate_limit,
    ns::Config::Window::update_rate
)
{}

App::App(const std::string& title, int w_width, int w_height, int v_width, int v_height, int fps, int ups) {
    ns::Config::Window::title = title;
    ns::Config::Window::width = w_width;
    ns::Config::Window::height = w_height;
    ns::Config::Window::framerate_limit = fps;
    ns::Config::Window::update_rate = ups;

    AppComponent::app = this;
    if (!v_width) v_width = w_width;
    if (!v_height) v_height = w_height;
    ns::Config::Window::view_width = v_width;
    ns::Config::Window::view_height = v_height;

    m_title = title;
    m_desired_fps = fps;
    m_ups = ups;
    m_fullscreen = false;

    m_window.create(sf::VideoMode(w_width, w_height), title, ns::Config::Window::style);
    m_window.setAppView(v_width, v_height);
    m_window.setFramerateLimit(fps);

    m_dt = 0.0;
    m_fps_clock.restart();
}

App::~App() {
    for (auto& scn: m_scenes) {
        delete(scn);
    }
    for (auto& cam: m_cameras) {
        delete(cam);
    }
    for (auto& dbg_txt: m_debug_texts) {
        delete(dbg_txt);
    }
    Res::dispose();
}

auto App::getTitle() -> std::string& {
    return m_title;
}

auto App::getWindow() -> AppWindow& {
    return m_window;
}

auto App::allScenes() -> std::vector<Scene*>& {
    return m_scenes;
}

auto App::allCameras() -> std::vector<Camera*>& {
    return m_cameras;
}

auto App::getInputs() -> std::vector<sf::Keyboard::Key>& {
    return m_inputs;
}

auto App::createScene(const std::string& name) -> Scene* {
    auto* new_scene = new Scene(name);
    m_scenes.push_back(new_scene);
    return new_scene;
}

auto App::createCamera(const std::string& cam_name, int order, const ns::IntRect& view, const ns::FloatRect& viewport) -> Camera* {
    auto* new_cam = new Camera(cam_name, order);
    new_cam->reset(view.topleft(), view.size());
    new_cam->resetViewport(viewport.topleft(), viewport.size());
    m_cameras.push_back(new_cam);
    return new_cam;
}

auto App::createCamera(const std::string& cam_name, int order, const ns::IntRect& view) -> Camera* {
    return createCamera(cam_name, order, view, ns::FloatRect(0, 0, 1, 1));
}

void App::toggleFullscreen() {
    auto clear_color = m_window.getClearColor();
    if(!m_fullscreen) {
        m_window.create(sf::VideoMode::getFullscreenModes()[0], m_title, sf::Style::None);
        m_window.setMouseCursorVisible(false);
    }
    else {
        m_window.create(sf::VideoMode(ns::Config::Window::width, ns::Config::Window::height), m_title, ns::Config::Window::style);
    }
    m_window.setClearColor(clear_color);
    m_window.setFramerateLimit(m_desired_fps);
    m_window.scaleView();
    m_inputs.clear();
    m_fullscreen = !m_fullscreen;
}

void App::storeInputs(sf::Event event) {
    if (event.type == sf::Event::KeyPressed)
        if (std::find(m_inputs.begin(), m_inputs.end(), event.key.code) == m_inputs.end())
            m_inputs.insert(m_inputs.begin(), event.key.code);

    if (event.type == sf::Event::KeyReleased)
        if (std::find(m_inputs.begin(), m_inputs.end(), event.key.code) != m_inputs.end())
            m_inputs.erase(std::find(m_inputs.begin(), m_inputs.end(), event.key.code));

}

void App::render() {

    // sorting cameras by their render order, order 0 being always drawn first
    std::sort(
        m_cameras.begin(), m_cameras.end(),
        [](auto& lhs, auto& rhs){
            return lhs->getRenderOrder() < rhs->getRenderOrder();
        }
    );

    // drawing Camera contents on App view
    m_window.setView(m_window.getAppView());
    // for each camera, if it has a scene and is visible, render the content
    for (Camera*& cam: m_cameras) {
        if (cam->hasScene() && cam->isVisible()) {
            cam->render(m_window);
        }
    }

    // drawing debug texts on DefaultView
    m_window.setView(m_window.getDefaultView());
    for(auto& dbg_txt: m_debug_texts) {
        dbg_txt->update(); m_window.draw(*dbg_txt);
    }
}

void App::run() {
    double current_slice = 0.;
    double slice_time = 1.0/m_ups;
    m_window.scaleView();
    while (m_window.isOpen()) {
        m_dt = m_fps_clock.restart().asSeconds();
        current_slice += m_dt;

        if (ns::Config::debug)
            m_window.setTitle(m_title+ " | FPS :" + std::to_string(1 / m_dt));

        // getting and storing inputs
        sf::Event event{};
        while (m_window.pollEvent(event)) {
            storeInputs(event);
            onEvent(event);
        }
        // updating app
        while (current_slice >= slice_time) {
            current_slice -= slice_time;
            update();
            for (Camera*& cam: m_cameras)
                cam->update();
        }
        // rendering drawables and displaying window
        m_window.clear(m_window.getClearColor());
        render();
        m_window.display();
    }
}
