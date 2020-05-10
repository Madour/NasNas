/**
* Created by Modar Nasser on 15/04/2020.
**/

#include "NasNas/core/App.hpp"

using namespace ns;

App::App(const std::string& title, int w_width, int w_height, int v_width, int v_height, int fps) :
W_WIDTH(w_width)
,W_HEIGHT(w_height)
{
    AppComponent::app = this;
    if (!v_width) v_width = w_width;
    if (!v_height) v_height = w_height;

    this->title = title;
    this->desired_fps = fps;
    this->fullscreen = false;

    this->window.create(sf::VideoMode(w_width, w_height), title, sf::Style::Default);
    this->window.setUIView(v_width, v_height);
    this->window.setFramerateLimit(fps);

    this->scene = this->createScene(w_width, w_height);
    this->game_camera = this->createCamera("game_camera", 0, IntRect(0, 0, v_width, v_height));
    this->game_camera->lookAt(this->scene);

    this->dt = 0.0;
    this->fps_clock.restart();

}

App::~App() {
    for (auto& scn: this->scenes) {
        delete(scn);
    }
    for (auto& cam: this->cameras) {
        delete(cam);
    }
    for (auto& dbg_txt: this->debug_texts) {
        std::visit([&](auto&& arg){delete(arg);}, dbg_txt);
    }
    Res::dispose();
}

auto App::getTitle() -> std::string& {
    return this->title;
}

auto App::getWindow() -> AppWindow& {
    return this->window;
}

auto App::allScenes() -> std::vector<Scene*>& {
    return this->scenes;
}

auto App::allCameras() -> std::vector<Camera*>& {
    return this->cameras;
}

auto App::getInputs() -> std::vector<sf::Keyboard::Key> & {
    return this->inputs;
}

auto App::createScene(int width, int height) -> Scene* {
    auto* new_scene = new Scene(width, height);
    this->scenes.push_back(new_scene);
    return new_scene;
}

auto App::createCamera(const std::string& cam_name, int order, const IntRect& view, const FloatRect& viewport) -> Camera* {
    auto* new_cam = new Camera(cam_name, order);
    new_cam->reset(view.topleft, view.size);
    new_cam->resetViewport(viewport.topleft, viewport.size);
    this->cameras.push_back(new_cam);
    return new_cam;
}

auto App::createCamera(const std::string& cam_name, int order, const IntRect& view) -> Camera* {
    return this->createCamera(cam_name, order, view, FloatRect(0, 0, 1, 1));
}

void App::toggleFullscreen() {
    if(!this->fullscreen) {
        this->window.create(sf::VideoMode::getFullscreenModes()[0], this->title, sf::Style::None);
    }
    else {
        this->window.create(sf::VideoMode(this->W_WIDTH, this->W_HEIGHT), this->title);
    }
    this->window.setFramerateLimit(this->desired_fps);
    this->window.scaleView();
    this->inputs.clear();
    this->fullscreen = !this->fullscreen;
}

void App::storeInputs(sf::Event event) {
    if (event.type == sf::Event::KeyPressed)
        if (std::find(this->inputs.begin(), this->inputs.end(), event.key.code) == this->inputs.end())
            this->inputs.insert(this->inputs.begin(), event.key.code);

    if (event.type == sf::Event::KeyReleased)
        if (std::find(this->inputs.begin(), this->inputs.end(), event.key.code) != this->inputs.end())
            this->inputs.erase(std::find(this->inputs.begin(), this->inputs.end(), event.key.code));

}

void App::render() {
    // updating all scenes by rendering on their textures
    for (Scene*& scn: this->scenes) {
        scn->render();
    }

    // sorting cameras by their render order, order 0 being always drawn first
    std::sort(
            this->cameras.begin(), this->cameras.end(),
            [](auto& lhs, auto& rhs){
                return lhs->getRenderOrder() < rhs->getRenderOrder();
            }
    );
    // for each camera, if it has a scene and is visible, draw its scene on its view.
    for (Camera*& cam: this->cameras) {
        cam->update();
        if (cam->hasScene() && cam->isVisible()) {
            this->window.setView(*cam);
            this->window.draw(cam->getScene());
        }
    }
    this->window.setView(this->window.getUIView());
    this->window.setView(this->window.getDefaultView());
    for(std::variant<DebugText<int>*, DebugText<float>*, DebugText<sf::Vector2f>*>& dbg_txt: this->debug_texts) {
        std::visit([&](auto&& arg){arg->update(); window.draw(*arg);}, dbg_txt);
    }
}


void App::run() {
    this->window.scaleView();
    while (this->window.isOpen()) {
        this->dt = this->fps_clock.restart().asSeconds();
        this->window.setTitle(this->title + " | FPS :" + std::to_string(1 / this->dt));

        sf::Event event{};
        while (this->window.pollEvent(event)) {
            this->storeInputs(event);
            this->onEvent(event);
        }

        this->update();

        this->window.clear(this->window.getClearColor());
        this->render();
        this->window.display();
    }
}


