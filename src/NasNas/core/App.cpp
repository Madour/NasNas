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

App::App(const std::string &title, sf::Vector2u resolution, unsigned int scale, int fps, int ups) :
App(title, resolution.x*scale, resolution.y*scale, resolution.x, resolution.y, fps, ups)
{}

App::App(const std::string& title, int w_width, int w_height, int v_width, int v_height, int fps, int ups) {
    AppComponent::app = this;

    Config::Window::title = title;
    Config::Window::size.x = w_width;
    Config::Window::size.y = w_height;
    Config::Window::view_size.x = v_width == 0 ? w_width : v_width;
    Config::Window::view_size.y = v_height == 0 ? w_height : v_height;
    Config::Window::framerate_limit = fps;
    Config::Window::update_rate = ups;

    m_title = title;
    m_desired_fps = fps;
    m_ups = ups;
    m_fullscreen = false;

    m_window.create(sf::VideoMode(w_width, w_height), title, Config::Window::style);
    m_window.setFramerateLimit(fps);

    m_dt = 0.0;
    m_fps_clock.restart();
}

App::~App() {
    for (auto& scn : m_scenes)
        delete(scn);
    for (auto& cam : m_cameras)
        delete(cam);
    for (auto& dbg_txt : m_debug_texts)
        delete(dbg_txt);
    for (auto& transition : Transition::list)
        delete(transition);
}

auto App::getTitle() const -> const std::string& {
    return m_title;
}

auto App::getWindow() -> AppWindow& {
    return m_window;
}

auto App::allScenes() -> std::vector<Scene*>& {
    return m_scenes;
}

auto App::getScene(const std::string& name) -> Scene* {
    for (const auto& scene : m_scenes)
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
    for (const auto& camera : m_cameras)
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
    new_cam->resetViewport(viewport.topleft(), viewport.size());
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
}

void App::render() {
    // drawing Camera contents on App view
    m_window.setView(m_window.getAppView());

    sf::RenderTexture renderer;
    renderer.create((unsigned int)m_window.getAppView().getSize().x, (unsigned int)m_window.getAppView().getSize().y);
    renderer.clear(sf::Color::Transparent);
    // for each camera, if it has a scene and is visible, render the content
    for (Camera*& cam: m_cameras) {
        if (cam->hasScene() && cam->isVisible()) {
            cam->render(renderer);
        }
    }
    for (unsigned int i = 0; i < Transition::list.size(); ++i) {
        auto* tr = Transition::list[i];
        if (tr->hasStarted())
            renderer.draw(*tr);
        if (tr->hasEnded()) {
            Transition::list.erase(Transition::list.begin() + i--);
            delete(tr);
        }
    }
    renderer.display();
    m_window.draw(sf::Sprite(renderer.getTexture()), getShader());

    // drawing debug texts and rectangles on ScreenView
    m_window.setView(m_window.getScreenView());

    auto drawDebugRectangle = [&](const ns::FloatRect& global_bounds, const Camera* view) {
        auto view_center = sf::Vector2f(getWindow().mapCoordsToPixel(view->getCenter() - view->getPosition(), getWindow().getAppView()));
        auto topleft = sf::Vector2f(getWindow().mapCoordsToPixel(global_bounds.topleft() - view->getPosition(), getWindow().getAppView()));
        auto bottomright = sf::Vector2f(getWindow().mapCoordsToPixel(global_bounds.bottomright() - view->getPosition(), getWindow().getAppView()));
        auto viewport = view->getViewport();
        auto pos = sf::Vector2f(topleft.x*viewport.width, topleft.y*viewport.height);
        auto pos2 = sf::Vector2f(bottomright.x*viewport.width, bottomright.y*viewport.height);
        auto size = sf::Vector2f(pos2-pos);
        auto center = sf::Vector2f(view_center.x*viewport.width, view_center.y*viewport.height);
        sf::RectangleShape dbg_bounds{sf::Vector2f(size.x, size.y)};
        dbg_bounds.setOrigin(center-pos);
        dbg_bounds.setPosition(pos+dbg_bounds.getOrigin());
        dbg_bounds.setOutlineThickness(1);
        dbg_bounds.setOutlineColor(sf::Color::Red);
        dbg_bounds.setFillColor(sf::Color::Transparent);
        dbg_bounds.rotate(-view->getRotation());
        m_window.draw(dbg_bounds);
    };
    if (Config::debug) {
        // drawing drawables global bounds
        for (Camera*& cam: m_cameras) {
            if (cam->hasScene() && cam->isVisible()) {
                auto render_bounds = cam->getGlobalBounds();
                for (const auto& drawable_variant: cam->m_scene->m_default_layer->getDrawables()) {
                    if (std::visit([&](auto&& drawable) {
                        return render_bounds.intersects(drawable->getGlobalBounds());
                    }, drawable_variant)) {
                        ns::FloatRect drawable_bounds;
                        std::visit([&](auto&& drawable) { drawable_bounds = drawable->getGlobalBounds(); }, drawable_variant);
                        drawDebugRectangle(drawable_bounds, cam);
                    }
                }
                for (const auto&[key, layer]: cam->m_scene->m_layers) {
                    for (const auto& drawable_variant: layer->getDrawables()) {
                        if (std::visit([&](auto&& drawable) {
                            return render_bounds.intersects(drawable->getGlobalBounds());
                        }, drawable_variant)) {
                            ns::FloatRect drawable_bounds;
                            std::visit([&](auto&& drawable) { drawable_bounds = drawable->getGlobalBounds(); }, drawable_variant);
                            drawDebugRectangle(drawable_bounds, cam);
                        }
                    }
                }
            }
        }
        // drawing debug texts
        for (auto& dbg_txt: m_debug_texts) {
            dbg_txt->update();
            m_window.draw(*dbg_txt);
        }
    }
}

void App::run() {
    double current_slice = 0.;
    double slice_time = 1.0/m_ups;
    while (m_window.isOpen()) {
        m_dt = m_fps_clock.restart().asSeconds();
        current_slice += m_dt;

        if (Config::debug)
            m_window.setTitle(m_title+ " | FPS :" + std::to_string(1 / m_dt));
        else
            m_window.setTitle(m_title);

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
            for (const auto& cam : m_cameras)
                cam->update();
            for (unsigned int i = 0; i < Transition::list.size(); ++i)
                Transition::list[i]->update();
        }
        // rendering drawables and displaying window
        m_window.clear(m_window.getClearColor());
        render();
        m_window.display();
    }
}
