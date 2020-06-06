/**
* Created by Modar Nasser on 15/04/2020.
**/

#pragma once

#include "NasNas/data/AppComponent.hpp"
#include "NasNas/data/Rect.hpp"

#include "NasNas/core/Layers.hpp"
#include "NasNas/core/Scene.hpp"
#include "NasNas/core/Camera.hpp"
#include "NasNas/core/Window.hpp"
#include "NasNas/core/Debug.hpp"
#include "NasNas/core/Entities.hpp"

namespace ns {

    class App {
    public:
        explicit App(const std::string& title, int w_width=960, int w_height=540,
                int v_width=0, int v_height=0, int desired_fps=60);
        ~App();

        const int W_WIDTH;
        const int W_HEIGHT;

        auto getTitle() -> std::string&;

        auto allScenes() -> std::vector<Scene*>&;
        auto allCameras() -> std::vector<Camera*>&;

        auto getInputs() -> std::vector<sf::Keyboard::Key>&;

        void run();

    protected:
        Scene* scene = nullptr;
        Camera* game_camera = nullptr;

        auto createScene(int width, int height) -> Scene*;

        auto createCamera(const std::string& name, int order, const IntRect& view, const FloatRect& viewport) -> Camera*;
        auto createCamera(const std::string& name, int order, const IntRect& view) -> Camera*;

        template<typename T>
        void addDebugText(T* var_address, const std::string& label,const sf::Vector2f& position, const sf::Color& color = ns::DebugText<T>::color);

        template<typename T>
        void addDebugText(const T* var_address, const std::string& label,const sf::Vector2f& position, const sf::Color& color = ns::DebugText<T>::color);

        template<typename T>
        void addDebugText(BaseEntity* object_address, std::function<T(BaseEntity &)> method_address, std::string label, const sf::Vector2f& position, const sf::Color& color = ns::DebugText<T>::color);

        template<typename T>
        void addDebugText(ns::DebugText<T>* debug_text);

        auto getWindow() -> AppWindow&;
        void toggleFullscreen();

        virtual void onEvent(sf::Event event) = 0;

        virtual void update() = 0;

    private:
        std::string title;
        int desired_fps;
        bool fullscreen;
        AppWindow window;

        sf::Clock fps_clock;
        double dt;
        std::vector<Camera*> cameras;
        std::vector<Scene*> scenes;
        std::vector<std::variant<DebugText<int>*, DebugText<float>*, DebugText<sf::Vector2f>*>> debug_texts;
        std::vector<sf::Keyboard::Key> inputs;

        void storeInputs(sf::Event event);

        void render();
    };

    template<typename T>
    void App::addDebugText(T* var_address, const std::string& label, const sf::Vector2f& position, const sf::Color& color) {
        sf::Color old_color = ns::DebugText<T>::color;
        ns::DebugText<T>::color = color;
        this->debug_texts.push_back(new DebugText<T>(var_address, label, position));
        ns::DebugText<T>::color = old_color;
    }
    template<typename T>
    void App::addDebugText(const T* var_address, const std::string& label, const sf::Vector2f& position, const sf::Color& color) {
        sf::Color old_color = ns::DebugText<T>::color;
        ns::DebugText<T>::color = color;
        this->debug_texts.push_back(new DebugText<T>(var_address, label, position));
        ns::DebugText<T>::color = old_color;
    }
    template<typename T>
    void App::addDebugText(BaseEntity* object_address, std::function<T(BaseEntity &)> method_address, std::string label, const sf::Vector2f& position, const sf::Color& color) {
        sf::Color old_color = ns::DebugText<T>::color;
        ns::DebugText<T>::color = color;
        this->debug_texts.push_back(new DebugText<T>(object_address, method_address, label, position));
        ns::DebugText<T>::color = old_color;
    }
    template<typename T>
    void App::addDebugText(ns::DebugText<T>* debug_text) {
        this->debug_texts.push_back(debug_text);
    }

}
