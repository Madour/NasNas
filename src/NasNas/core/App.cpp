/**
* Created by Modar Nasser on 15/04/2020.
**/


#include "NasNas/core/App.hpp"

using namespace ns;

App::App()
: App(
    Config::Window::title,
    Config::Window::size.x,
    Config::Window::size.y,
    Config::Window::view_size.x,
    Config::Window::view_size.y,
    Config::Window::framerate_limit,
    Config::Window::update_rate
)
{}

App::App(const std::string &title, sf::Vector2u resolution, float scale, int fps, int ups) :
App(
    title,
    static_cast<int>(resolution.x*scale), static_cast<int>(resolution.y*scale),
    resolution.x, resolution.y,
    fps, ups
)
{}

App::App(std::string title, int w_width, int w_height, int v_width, int v_height, int fps, int ups) :
m_title(std::move(title)),
m_fullscreen(false),
m_ups(ups),
m_desired_fps(fps)
{
    AppComponent::app = this;

    Config::Window::title = title;
    Config::Window::size.x = w_width;
    Config::Window::size.y = w_height;
    Config::Window::view_size.x = v_width == 0 ? w_width : v_width;
    Config::Window::view_size.y = v_height == 0 ? w_height : v_height;
    Config::Window::framerate_limit = fps;
    Config::Window::update_rate = ups;

    m_window.create(sf::VideoMode(w_width, w_height), title, Config::Window::style);
    m_window.setTitle(m_title);
    if (fps > 0)
        m_window.setFramerateLimit(fps);

    m_renderer.create((unsigned int)m_window.getAppView().getSize().x, (unsigned int)m_window.getAppView().getSize().y);

    m_dt = 0.0;
    m_fps_clock.restart();
}

App::~App() {
    for (auto* scn : m_scenes)
        delete(scn);
    for (auto* cam : m_cameras)
        delete(cam);
    for (auto* dbg_txt : m_debug_texts)
        delete(dbg_txt);
    for (auto* transition : Transition::list)
        delete(transition);
}

auto App::getTitle() const -> const std::string& {
    return m_title;
}

auto App::getWindow() -> AppWindow& {
    return m_window;
}

auto App::getMousePosition(Camera* cam) const -> sf::Vector2f {
    auto offset = m_window.mapCoordsToPixel(cam->getSprite().getPosition(), m_window.getAppView());
    const auto& global_vport = m_window.getAppView().getViewport();
    const auto& local_vport = cam->getViewport();
    auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(m_window));
    mouse_pos.x = (mouse_pos.x - offset.x) / (global_vport.width * local_vport.width);
    mouse_pos.y = (mouse_pos.y - offset.y) / (global_vport.height * local_vport.height);
    mouse_pos = m_window.mapPixelToCoords(sf::Vector2i(mouse_pos), *cam);
    return mouse_pos;
}

auto App::allScenes() -> std::vector<Scene*>& {
    return m_scenes;
}

auto App::getScene(const std::string& name) -> Scene* {
    for (auto* scene : m_scenes)
        if (scene->m_name == name)
            return scene;

    std::cout << "Error (App::getScene) : No Scene named " << name
              << " was found. Make sure the Scene you are requesting was created.";
    std::exit(-1);
}

auto App::allCameras() -> std::vector<Camera*>& {
    return m_cameras;
}

auto App::getCamera(const std::string& name) -> Camera* {
    for (auto* camera : m_cameras)
        if (camera->m_name == name)
            return camera;

    std::cout << "Error (App::getCamera) : No Camera named " << name
              << " was found. Make sure the Camera you are requesting was created.";
    std::exit(-1);
}

auto App::createScene(const std::string& name) -> Scene* {
    auto* new_scene = new Scene(name);
    m_scenes.push_back(new_scene);
    return new_scene;
}

auto App::createCamera(const std::string& cam_name, int order, const ns::IntRect& view, const ns::FloatRect& viewport) -> Camera* {
    auto* new_cam = new Camera(cam_name, order);
    new_cam->reset(view.topleft(), view.size());
    if (viewport.left <= 1 && viewport.top <= 1 && viewport.width <= 1 && viewport.height <= 1)
        new_cam->resetViewport(viewport.topleft(), viewport.size());
    else {
        auto x = viewport.left/float(ns::Config::Window::view_size.x);
        auto width = viewport.width/float(ns::Config::Window::view_size.x);
        auto y = viewport.top/float(ns::Config::Window::view_size.y);
        auto height = viewport.height/float(ns::Config::Window::view_size.y);
        new_cam->resetViewport(x, y, width, height);
    }
    m_cameras.push_back(new_cam);

    // sorting cameras by their render order, order 0 being always drawn first
    std::sort(
        m_cameras.begin(), m_cameras.end(),
        [](auto& lhs, auto& rhs){
            return lhs->getRenderOrder() < rhs->getRenderOrder();
        }
    );

    return new_cam;
}

auto App::createCamera(const std::string& cam_name, int order, const ns::IntRect& view) -> Camera* {
    return createCamera(cam_name, order, view, ns::FloatRect(0, 0, 1, 1));
}

void App::sleep() {
    m_sleeping = true;
}

void App::awake() {
    m_sleeping = false;
}

void App::toggleFullscreen() {
    auto clear_color = m_window.getClearColor();
    if(!m_fullscreen) {
        m_window.create(sf::VideoMode::getFullscreenModes()[0], m_title, sf::Style::Fullscreen);
        m_window.setMouseCursorVisible(false);
    }
    else {
        m_window.create(sf::VideoMode(Config::Window::size.x, Config::Window::size.y), m_title, Config::Window::style);
    }
    m_window.setClearColor(clear_color);
    m_window.setFramerateLimit(m_desired_fps);
    m_fullscreen = !m_fullscreen;
}

void App::addDebugText(const std::string& label, const sf::Vector2f& position, const sf::Color& color) {
    auto* dbg_txt = new DebugText<char>(label, position);
    dbg_txt->setFillColor(color);
    m_debug_texts.push_back(dbg_txt);
}

void App::storeInputs(sf::Event event) {
    auto& pressed_keys = Config::Inputs::pressed_keys;
    if (event.type == sf::Event::KeyPressed)
        if (std::find(pressed_keys.begin(), pressed_keys.end(), event.key.code) == pressed_keys.end())
            pressed_keys.insert(pressed_keys.begin(), event.key.code);

    if (event.type == sf::Event::KeyReleased)
        if (std::find(pressed_keys.begin(), pressed_keys.end(), event.key.code) != pressed_keys.end())
            pressed_keys.erase(std::find(pressed_keys.begin(), pressed_keys.end(), event.key.code));
}

void App::onEvent(const sf::Event& event) {
    if (event.type == sf::Event::Closed)
        m_window.close();
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            m_window.close();
        if (event.key.code == sf::Keyboard::F1)
            Config::debug = !Config::debug;
    }
}

void App::render() {
    // draw Cameras content on AppView
    m_window.setView(m_window.getAppView());

    m_renderer.clear(sf::Color::Transparent);

    // render renderables
    for (auto* renderable : Renderable::list) {
        renderable->render();
    }

    // for each camera, if it has a scene and is visible, render the content
    for (auto* cam: m_cameras) {
        if (cam->hasScene() && cam->isVisible()) {
            cam->render(m_renderer);
        }
    }
    // render transitions, delete it when it has ended
    for (unsigned int i = 0; i < Transition::list.size(); ++i) {
        auto* tr = Transition::list[i];
        if (tr->hasStarted())
            m_renderer.draw(*tr);
        if (tr->hasEnded()) {
            Transition::list.erase(Transition::list.begin() + i--);
            delete(tr);
        }
    }
    m_renderer.display();
    m_window.draw(sf::Sprite(m_renderer.getTexture()), getShader());

    // draw debug things on ScreenView
    m_window.setView(m_window.getScreenView());
    // draw debug bounds
    if (Config::debug && Config::debug.show_bounds) {
       renderDebugBounds();
    }
    // draw debug texts
    if (Config::debug && Config::debug.show_text) {
        for (auto* dbg_txt: m_debug_texts) {
            dbg_txt->update();
            m_window.draw(*dbg_txt);
        }
    }
}

void App::renderDebugBounds() {
    // draw app view bounds
    sf::Vector2f s{m_window.getAppView().getViewport().width*m_window.getSize().x,
                   m_window.getAppView().getViewport().height*m_window.getSize().y};
    sf::Vector2f p{m_window.getAppView().getViewport().left*m_window.getSize().x,
                   m_window.getAppView().getViewport().top*m_window.getSize().y};
    sf::RectangleShape r{s};
    r.setPosition(p);
    r.setFillColor(sf::Color::Transparent);
    r.setOutlineColor(sf::Color::Red);
    r.setOutlineThickness(-1);
    m_window.draw(r);

    // draw drawables debug bounds
    m_debug_bounds.clear();
    for (Camera* cam: m_cameras) {
        if (cam->hasScene() && cam->isVisible()) {
            auto render_bounds = cam->getGlobalBounds();
            const auto& global_vport = m_window.getAppView().getViewport();
            const auto& local_vport = cam->getViewport();
            sf::Vector2f offset{m_window.mapCoordsToPixel(cam->getSprite().getPosition(), m_window.getAppView())};

            for (const auto& drawable_variant: cam->m_scene->m_default_layer.getDrawables()) {
                storeDrawableDebugRects(drawable_variant, cam, render_bounds, offset, global_vport, local_vport);
            }
            for (const auto& [key, layer]: cam->m_scene->m_layers) {
                for (const auto& drawable_variant: layer.getDrawables()) {
                    storeDrawableDebugRects(drawable_variant, cam, render_bounds, offset, global_vport, local_vport);
                }
            }
        }
    }
    m_window.draw(m_debug_bounds.data(), m_debug_bounds.size(), sf::PrimitiveType::Lines);
}

void App::storeDrawableDebugRects(const Layer::DrawablesTypes& variant, Camera* cam,
                                  const sf::FloatRect& render_bounds, sf::Vector2f& offset,
                                  const sf::FloatRect& global_vport, const sf::FloatRect& local_vport) {
    if (std::visit([&](auto&& drawable){return render_bounds.intersects(drawable->getGlobalBounds());}, variant)) {
        ns::FloatRect global_bounds;
        std::visit([&](auto&& drawable){global_bounds = drawable->getGlobalBounds();}, variant);

        // local view transformation
        sf::Vector2f topleft{m_window.mapCoordsToPixel(global_bounds.topleft(), *cam)};
        sf::Vector2f topright{m_window.mapCoordsToPixel(global_bounds.topright(), *cam)};
        sf::Vector2f bottomright{m_window.mapCoordsToPixel(global_bounds.bottomright(), *cam)};
        sf::Vector2f bottomleft{m_window.mapCoordsToPixel(global_bounds.bottomleft(), *cam)};
        topleft = {topleft.x*local_vport.width, topleft.y*local_vport.height};
        topright = {topright.x*local_vport.width, topright.y*local_vport.height};
        bottomright = {bottomright.x*local_vport.width, bottomright.y*local_vport.height};
        bottomleft = {bottomleft.x*local_vport.width, bottomleft.y*local_vport.height};

        // app view transformation
        sf::Vector2f pos0{offset.x + topleft.x*global_vport.width, offset.y + topleft.y*global_vport.height};
        sf::Vector2f pos1{offset.x + topright.x*global_vport.width+2, offset.y + topright.y*global_vport.height};
        sf::Vector2f pos2{offset.x + bottomright.x*global_vport.width+2, offset.y + bottomright.y*global_vport.height+2};
        sf::Vector2f pos3{offset.x + bottomleft.x*global_vport.width, offset.y + bottomleft.y*global_vport.height+2};
        m_debug_bounds.emplace_back(pos0, sf::Color::Red); m_debug_bounds.emplace_back(pos1, sf::Color::Red);
        m_debug_bounds.emplace_back(pos1, sf::Color::Red); m_debug_bounds.emplace_back(pos2, sf::Color::Red);
        m_debug_bounds.emplace_back(pos2, sf::Color::Red); m_debug_bounds.emplace_back(pos3, sf::Color::Red);
        m_debug_bounds.emplace_back(pos3, sf::Color::Red); m_debug_bounds.emplace_back(pos0, sf::Color::Red);
    }
}

void App::run() {
    double current_slice = 0.;
    double slice_time = 1.0/m_ups;
    while (m_window.isOpen()) {
        m_dt = m_fps_clock.restart().asSeconds();
        current_slice += m_dt;

        if (Config::debug && Config::debug.show_fps)
            m_window.setTitle(m_title+ " | FPS :" + std::to_string(1 / m_dt));

        // get and store inputs
        sf::Event event{};
        while (m_window.pollEvent(event)) {
            storeInputs(event);
            onEvent(event);
        }
        // update the app
        while (current_slice >= slice_time) {
            current_slice -= slice_time;
            if (!m_sleeping) {
                update();
                for (auto* cam : m_cameras)
                    cam->update();
                for (unsigned int i = 0; i < Transition::list.size(); ++i)
                    Transition::list[i]->update();
            }
        }
        // render drawables and display window
        m_window.clear(m_window.getClearColor());
        if (!m_sleeping) {
            preRender();
            render();
        }
        m_window.display();
    }
}
