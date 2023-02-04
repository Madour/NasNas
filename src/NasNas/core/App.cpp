/**
* Created by Modar Nasser on 15/04/2020.
**/

#include <NasNas/core/App.hpp>

#include <numeric>

#include <SFML/Window/Touch.hpp>

#include <NasNas/core/graphics/Renderable.hpp>
#include <NasNas/core/Inputs.hpp>
#include <NasNas/core/Transition.hpp>

using namespace ns;

App::App() : App(
    Settings::user_config.title,
    Settings::user_config.resolution,
    Settings::user_config.scale,
    Settings::user_config.frame_rate,
    Settings::user_config.update_rate
)
{}

App::App(std::string title, sf::Vector2u resolution, float scale, int fps, int ups) :
        m_title(std::move(title)),
        m_fullscreen(false),
        m_ups(ups),
        m_fps(fps)
{
    detail::AppComponent::app = this;

    sf::Vector2u window_size = {static_cast<unsigned>(resolution.x*scale), static_cast<unsigned>(resolution.y*scale)};
    sf::Vector2f view_size = {static_cast<float>(resolution.x), static_cast<float>(resolution.y)};
    float view_ratio = view_size.x / view_size.y;

    Settings::user_config.title = m_title;
    Settings::user_config.resolution = resolution;
    Settings::user_config.scale = scale;
    Settings::user_config.frame_rate = m_fps;
    Settings::user_config.update_rate = m_ups;
    Settings::user_config.video_mode.width = window_size.x;
    Settings::user_config.video_mode.height = window_size.y;
    Settings::user_config.view_size = view_size;
    Settings::user_config.view_ratio = view_ratio;

    m_window.create(Settings::user_config.video_mode, m_title, Settings::user_config.window_style);

    if (fps > 0)
        m_window.setFramerateLimit(fps);

    m_renderer.create((unsigned int)m_window.getAppView().getSize().x, (unsigned int)m_window.getAppView().getSize().y);
    m_debug_bounds.reserve(100*4);

    m_dt = 0.0;
    m_fps_clock.restart();
}

auto App::getTitle() const -> const std::string& {
    return m_title;
}

auto App::getWindow() -> AppWindow& {
    return m_window;
}

auto App::getMousePosition() const -> sf::Vector2f {
    return sf::Vector2f(sf::Mouse::getPosition(m_window));
}

auto App::getMousePosition(Camera& cam) const -> sf::Vector2f {
    auto offset = m_window.mapCoordsToPixel(cam.getSprite().getPosition(), m_window.getAppView());
    const auto& global_vport = m_window.getAppView().getViewport();
    const auto& local_vport = cam.getViewport();
    auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(m_window));
    mouse_pos.x = (mouse_pos.x - offset.x) / (global_vport.width * local_vport.width);
    mouse_pos.y = (mouse_pos.y - offset.y) / (global_vport.height * local_vport.height);
    mouse_pos = m_window.mapPixelToCoords(sf::Vector2i(mouse_pos), cam);
    return mouse_pos;
}

auto App::getTouchPosition(int finger) const -> sf::Vector2f {
    return sf::Vector2f(sf::Touch::getPosition(finger, m_window));
}

auto App::getTouchPosition(int finger, Camera& cam) const -> sf::Vector2f {
    auto offset = m_window.mapCoordsToPixel(cam.getPosition(), m_window.getAppView());
    const auto& global_vport = m_window.getAppView().getViewport();
    const auto& local_vport = cam.getViewport();
    auto finger_pos = sf::Vector2f(sf::Touch::getPosition(finger, m_window));
    finger_pos.x = (finger_pos.x - offset.x) / (global_vport.width * local_vport.width);
    finger_pos.y = (finger_pos.y - offset.y) / (global_vport.height * local_vport.height);
    finger_pos = m_window.mapPixelToCoords(sf::Vector2i(finger_pos), cam);
    return finger_pos;
}

auto App::allScenes() -> std::list<Scene>& {
    return m_scenes;
}

auto App::getScene(const std::string& name) -> Scene& {
    for (auto& scene : m_scenes)
        if (scene.m_name == name)
            return scene;

    std::cout << "Error (App::getScene) : No Scene named " << name
              << " was found. Make sure the Scene you are requesting was created.";
    std::exit(-1);
}

auto App::allCameras() -> std::list<Camera>& {
    return m_cameras;
}

auto App::getCamera(const std::string& name) -> Camera& {
    for (auto& camera : m_cameras)
        if (camera.m_name == name)
            return camera;

    std::cout << "Error (App::getCamera) : No Camera named " << name
              << " was found. Make sure the Camera you are requesting was created.";
    std::exit(-1);
}

auto App::isRunningTransition() const -> bool {
    return !m_transitions.empty();
}

auto App::createScene(const std::string& name) -> Scene& {
    return m_scenes.emplace_back(name);
}

auto App::createCamera(const std::string& cam_name, int order, const ns::IntRect& view, const ns::FloatRect& viewport) -> Camera& {
    auto& new_cam = m_cameras.emplace_back(cam_name, order);
    new_cam.reset(view.topleft(), view.size());

    if (viewport.left <= 1 && viewport.top <= 1 && viewport.width <= 1 && viewport.height <= 1)
        new_cam.resetViewport(viewport.topleft(), viewport.size());
    else {
        auto& view_size = Settings::user_config.view_size;
        auto x = viewport.left/view_size.x;
        auto width = viewport.width/view_size.x;
        auto y = viewport.top/view_size.y;
        auto height = viewport.height/view_size.y;
        new_cam.resetViewport(x, y, width, height);
    }

    return new_cam;
}

auto App::createCamera(const std::string& cam_name, int order, const ns::FloatRect & viewport) -> Camera& {
    return createCamera(cam_name, order, {{0, 0}, sf::Vector2i(Settings::user_config.view_size)}, viewport);
}

void App::sleep() {
    m_sleeping = true;
}

void App::awake() {
    m_sleeping = false;
}

auto App::getDt() const -> float {
    return m_dt;
}

void App::toggleFullscreen() {
    auto clear_color = m_window.getClearColor();
    if(!m_fullscreen) {
        m_window.create(sf::VideoMode::getFullscreenModes()[0], m_title, sf::Style::None);
        m_window.setMouseCursorVisible(false);
    }
    else {
        m_window.create(Settings::user_config.video_mode, m_title, Settings::user_config.window_style);
    }
    m_window.setClearColor(clear_color);
    m_window.setFramerateLimit(m_fps);
    m_fullscreen = !m_fullscreen;
}

void App::addDebugText(const std::string& label, const sf::Vector2f& position, const sf::Color& color) {
    auto* dbg_txt = new DebugText<char>(label, position);
    dbg_txt->setFillColor(color);
    m_debug_texts.emplace_back(dbg_txt);
}

void App::storeInputs(const sf::Event& event) {
    auto& inputs = Inputs::get();
    if (event.type == sf::Event::KeyPressed) {
        inputs.m_keys_down.emplace_back(event.key.code);
        inputs.m_keys_states[event.key.code] = true;
        inputs.m_keys_pressed[event.key.code] = true;
    }
    else if (event.type == sf::Event::KeyReleased) {
        auto key_iter = std::find(inputs.m_keys_down.begin(), inputs.m_keys_down.end(), event.key.code);
        if (key_iter != inputs.m_keys_down.end())
            inputs.m_keys_down.erase(key_iter);
        inputs.m_keys_states[event.key.code] = false;
        inputs.m_keys_released[event.key.code] = true;
    }
}

void App::onEvent(const sf::Event& event) {
    if (event.type == sf::Event::Closed)
        m_window.close();
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            m_window.close();
        else if (event.key.code == sf::Keyboard::F1)
            Settings::debug_mode = !Settings::debug_mode;
        else if (event.key.code == sf::Keyboard::F2)
            Settings::debug_mode.show_fps = !Settings::debug_mode.show_fps;
        else if (event.key.code == sf::Keyboard::F3)
            Settings::debug_mode.show_text = !Settings::debug_mode.show_text;
        else if (event.key.code == sf::Keyboard::F4)
            Settings::debug_mode.show_bounds = !Settings::debug_mode.show_bounds;
    }
}

void App::update() {}

void App::render() {
    // draw Cameras content on AppView
    m_window.setView(m_window.getAppView());

    m_renderer.clear(sf::Color::Transparent);

    // render renderables
    for (auto* renderable : Renderable::list) {
        renderable->render();
    }

    // for each camera, if it has a scene and is visible, render the content
    for (auto& cam : m_cameras) {
        if (cam.hasScene() && cam.isVisible()) {
            cam.render(m_renderer);
        }
    }
    // render transitions
    for (auto& transition : m_transitions) {
        if (transition->hasStarted()) {
            m_renderer.draw(*transition);
        }
    }

    m_renderer.display();
    m_window.draw(sf::Sprite(m_renderer.getTexture()), getShader());

    // draw debug things on ScreenView
    m_window.setView(m_window.getScreenView());
    // draw debug bounds
    if (Settings::debug_mode && Settings::debug_mode.show_bounds) {
       renderDebugBounds();
    }
    // draw debug texts
    if (Settings::debug_mode && Settings::debug_mode.show_text) {
        for (auto& dbg_txt: m_debug_texts) {
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
    for (auto& cam : m_cameras) {
        if (cam.hasScene() && cam.isVisible()) {
            auto render_bounds = cam.getGlobalBounds();
            const auto& global_vport = m_window.getAppView().getViewport();
            const auto& local_vport = cam.getViewport();
            sf::Vector2f offset{m_window.mapCoordsToPixel(cam.getSprite().getPosition(), m_window.getAppView())};

            for (const auto* dr : cam.m_scene->getDefaultLayer().allDrawables()) {
                storeDrawableDebugRects(cam.m_scene->getDefaultLayer().getDrawableBounds(dr), cam, render_bounds, offset, global_vport, local_vport);
            }
            for (const auto& layer : cam.m_scene->m_layers) {
                for (const auto* dr : layer.allDrawables()) {
                    storeDrawableDebugRects(layer.getDrawableBounds(dr), cam, render_bounds, offset, global_vport, local_vport);
                }
            }
        }
    }
    m_window.draw(m_debug_bounds.data(), m_debug_bounds.size(), sf::PrimitiveType::Lines);
}

void App::storeDrawableDebugRects(const ns::FloatRect& drawable_bounds, Camera& cam,
                                  const sf::FloatRect& render_bounds, sf::Vector2f& offset,
                                  const sf::FloatRect& global_vport, const sf::FloatRect& local_vport) {
    if (render_bounds.intersects(drawable_bounds)) {
        // local view transformation
        sf::Vector2f topleft{m_window.mapCoordsToPixel(drawable_bounds.topleft(), cam)};
        sf::Vector2f topright{m_window.mapCoordsToPixel(drawable_bounds.topright(), cam)};
        sf::Vector2f bottomright{m_window.mapCoordsToPixel(drawable_bounds.bottomright(), cam)};
        sf::Vector2f bottomleft{m_window.mapCoordsToPixel(drawable_bounds.bottomleft(), cam)};
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
    // initialize Inputs manager
    Inputs::init();
    // sort cameras by render order
    m_cameras.sort([](Camera& lhs, Camera& rhs) { return lhs.getRenderOrder() < rhs.getRenderOrder(); });

    float slice_time = 1.f / static_cast<float>(m_ups);
    float current_slice = slice_time;
    sf::Clock timer;
    sf::Clock update_clock;
    std::array<float, 30> dt_buffer{};
    size_t dt_i = 0;
    while (m_window.isOpen()) {
        m_dt = m_fps_clock.restart().asSeconds();
        current_slice += m_dt;

        if (Settings::debug_mode && Settings::debug_mode.show_fps && timer.getElapsedTime().asMilliseconds()>200) {
            auto dt_average = std::accumulate(dt_buffer.begin(), dt_buffer.end(), 0.f) / dt_buffer.size();;
            m_window.setTitle(m_title+ " | FPS :" + std::to_string(static_cast<int>(1 / dt_average)) + " (" + std::to_string((1/m_dt)) + ")");
            timer.restart();
        }
        dt_buffer[dt_i++] = m_dt;
        dt_i %= dt_buffer.size();

        // get and store inputs
        sf::Event event{};
        while (m_window.pollEvent(event)) {
            storeInputs(event);
            onEvent(event);
            m_cb_onevent(event);
        }
        // update the app
        update_clock.restart();
        while (current_slice >= slice_time) {
            current_slice -= slice_time;
            if (update_clock.getElapsedTime().asSeconds() > slice_time)
                break;
            if (!m_sleeping) {
                m_dt = slice_time;
                update();
                m_cb_update();
                for (auto& cam : m_cameras)
                    cam.update();

                // remove transitions that already ended
                m_transitions.remove_if([](auto& transition) { return transition->hasEnded(); });

                for (auto& transition : m_transitions)
                    transition->update();

                Inputs::get().m_keys_pressed.clear();
                Inputs::get().m_keys_released.clear();
            }
        }
        // render drawables and display window
        if (!m_sleeping) {
            m_window.clear(m_window.getClearColor());
            preRender();
            m_cb_prerender();
            render();
            m_window.display();
        }
    }
}
