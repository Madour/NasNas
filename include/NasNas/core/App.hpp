/**
* Created by Modar Nasser on 15/04/2020.
**/


#pragma once

#include "NasNas/data/Config.hpp"
#include "NasNas/data/ShaderHolder.hpp"

#include "NasNas/core/Scene.hpp"
#include "NasNas/core/Layers.hpp"
#include "NasNas/core/Camera.hpp"
#include "NasNas/core/Window.hpp"
#include "NasNas/core/Transition.hpp"
#include "NasNas/core/Debug.hpp"

namespace ns {

    class App : public ShaderHolder {
    public:
        /**
         * \brief Contructs an App from ns::Config configuration
         */
        App();

        /**
         * \brief Constructs an App from constructor arguments
         * \param title App title
         * \param resolution Resolution of you application
         * \param scale Resolution * scale = WindowSize
         * \param fps Desired framerate limit
         * \param ups Update per second
         */
        App(const std::string& title, sf::Vector2u resolution,
            unsigned int scale=1,
            int fps=ns::Config::Window::framerate_limit,
            int ups=ns::Config::Window::update_rate
        );

        /**
         * \brief Contructs an App from constructor arguments
         *
         * \param title App title
         * \param w_width AppWindow width
         * \param w_height AppWindow height
         * \param v_width View width
         * \param v_height View height
         * \param fps Desired framerate limit
         * \param ups Update per second
         */
        App(const std::string& title, int w_width, int w_height,
            int v_width=ns::Config::Window::view_width,
            int v_height=ns::Config::Window::view_height,
            int fps=ns::Config::Window::framerate_limit,
            int ups=ns::Config::Window::update_rate
        );

        /**
         * \brief Delete all Scene, Camera and DebugText objects and free loaded resources
         */
        virtual ~App();

        /**
         * \brief Returns the title of the App
         *
         * \return Title of the App
         */
        auto getTitle() -> std::string&;

        /**
         * \brief Get all the Scene objects created within the App
         *
         * \return Vector of pointers to Scene objects
         */
        auto allScenes() -> std::vector<Scene*>&;

        /**
         * \brief Get all the Camera objects created within the App
         *
         * \return Vector of pointers to Camera objects
         */
        auto allCameras() -> std::vector<Camera*>&;

        /**
         * \brief Get all the pressed sf::Keyboard::Keys
         *
         * \return Vector of sf::Keyboard::Key
         */
        auto getInputs() -> std::vector<sf::Keyboard::Key>&;

        /**
         * \brief Starts the game loop.
         */
        void run();

        /**
             * \brief Get the AppWindow
             *
             * \return Reference to the AppWindow
             */
        auto getWindow() -> AppWindow&;

    protected:

        /**
         * \brief Creates a Scene object and returns a pointer to it
         *
         * \param width Width of the new Scene
         * \param height Height of the new Scene
         *
         * \return Pointer to the created Scene object
         */
        auto createScene(const std::string& name) -> Scene*;

        /**
         * \brief Creates a Camera object and returns a pointer to it
         *
         * \param name Name of the Camera
         * \param order Order of rendering of the Camera
         * \param view Rectangle representing the position and size of the Camera
         * \param viewport Viewport of the Camera on the AppWindow
         *
         * \return Pointer to the created Camera object
         */
        auto createCamera(const std::string& name, int order, const ns::IntRect& view, const ns::FloatRect& viewport) -> Camera*;

        /**
         * \brief Creates a Camera object and returns a pointer to it
         *
         * \param name Name of the Camera
         * \param order Order of rendering of the Camera
         * \param view Rectangle representing the position and size of the Camera
         *
         * \return Pointer to the created Camera object *
         */
        auto createCamera(const std::string& name, int order, const ns::IntRect& view) -> Camera*;

        /**
         * \brief Creates a DebugText object and render it on the AppWindow directly
         *
         * DebugText takes the address of a variable and will display its value on the AppWindow
         * at the given position. The label is displayed near the value. DebugText let you visualize
         * the variable's value changing in real time.
         *
         * \tparam T Type of the variable to be displayed
         *
         * \param var_address Address of the variable
         * \param label Label of the DebugText
         * \param position Position of the DebugText on the AppWindow
         * \param color Fill color of the DebugText
         */
        template<typename T>
        void addDebugText(T* var_address, const std::string& label,const sf::Vector2f& position, const sf::Color& color = ns::DebugTextInterface::color);

        /**
         * \brief Creates a DebugText object and render it on the AppWindow directly
         *
         * DebugText takes the address of a variable and will display its value on the AppWindow
         * at the given position. The label is displayed near the value. DebugText let you visualize
         * the variable's value changing in real time.
         *
         * \tparam T Type of the variable to be displayed
         *
         * \param var_address Address of the variable (const)
         * \param label Label of the DebugText
         * \param position Position of the DebugText on the AppWindow
         * \param color Fill color of the DebugText
         */
        template<typename T>
        void addDebugText(const T* var_address, const std::string& label,const sf::Vector2f& position, const sf::Color& color = ns::DebugTextInterface::color);

        /**
         * \brief Creates a DebugText object and render it on the AppWindow directly
         *
         * \tparam T Type of the value returned by the lambda function
         *
         * \param fn Lambda function to be evaluated
         * \param label Label of the DebugText
         * \param position Position of the DebugText on the AppWindow
         * \param color Fill color of the DebugText
         */
        template<typename T>
        void addDebugText(std::function<T()> fn, const std::string& label, const sf::Vector2f& position, const sf::Color& color = ns::DebugTextInterface::color);

        /**
         * \brief Creates a DebugText object and render it on the AppWindow directly
         *
         * \tparam T Return type of the method to be evaluated
         * \tparam ObjT Type of the method's object
         *
         * \param object_address Address of the object
         * \param method_address Address of the method
         * \param label Label of the DebugText
         * \param position Position of the DebugText on the AppWindow
         * \param color Fill color of the DebugText
         */
        template<typename T, typename ObjT>
        void addDebugText(
                ObjT* object_address,
                std::function<T(ObjT &)> method_address,
                const std::string& label,
                const sf::Vector2f& position,
                const sf::Color& color = ns::DebugTextInterface::color
        );

        /**
         * \brief Adds a DebugText to the App from a DebugText pointer
         *
         * \tparam T Return type of the method to be evaluated
         * \tparam ObjT Type of the method's object
         *
         * \param debug_text Pointer to a DebugText object
         */
        template<typename T, typename ObjT>
        void addDebugText(DebugText<T, ObjT>* debug_text);

        /**
         * \brief Toggle fullscreen display.
         */
        void toggleFullscreen();

        /**
         * \brief Handles SFML events
         *
         * Virtual method, can be defined by the user.
         * `onEvent` will be called each time a window event occures.
         *
         * \param event The sf::Event that happened
         */
        virtual void onEvent(const sf::Event& event);

        /**
         * \brief App update method
         *
         * Pure virtual method, has to be defined by the user.
         * `update` will be called as many times it needs to match the ups (update per second) parameter
         */
        virtual void update() = 0;

    private:
        AppWindow m_window;     ///< AppWindow
        std::string m_title;    ///< Title of the App
        bool m_fullscreen;      ///< Is the AppWindow fullscreen ?
        int m_ups;              ///< Update per second
        int m_desired_fps;      ///< Frame per second
        sf::Clock m_fps_clock;  ///< Clock to compute real FPS
        double m_dt;            ///< Delta time, time between two frames

        std::vector<Camera*> m_cameras;                 ///< Vector of Camera pointers
        std::vector<Scene*> m_scenes;                   ///< Vector of Scene pointers
        std::vector<DebugTextInterface*> m_debug_texts; ///< Vector of DebugText pointers

        std::vector<sf::Keyboard::Key> m_inputs;        ///< Vector of pressed keys

        /**
         * \brief Updates m_inputs everytime a key event occurs
         *
         * Inserts key code when event is KeyPressed and removes it when event is KeyReleased
         *
         * \param event The key event
         */
        void storeInputs(sf::Event event);

        /**
         * \brief Render App content to the AppWindow
         */
        void render();
    };

    template<typename T>
    void App::addDebugText(T* var_address, const std::string& label, const sf::Vector2f& position, const sf::Color& color) {
        sf::Color old_color = ns::DebugTextInterface::color;
        ns::DebugTextInterface::color = color;
        m_debug_texts.push_back(new DebugText<T, char>(var_address, label, position));
        ns::DebugTextInterface::color = old_color;
    }
    template<typename T>
    void App::addDebugText(const T* var_address, const std::string& label, const sf::Vector2f& position, const sf::Color& color) {
        sf::Color old_color = ns::DebugTextInterface::color;
        ns::DebugTextInterface::color = color;
        m_debug_texts.push_back(new DebugText<T, char>(var_address, label, position));
        ns::DebugTextInterface::color = old_color;
    }
    template<typename T>
    void App::addDebugText(std::function<T()> fn, const std::string& label, const sf::Vector2f& position, const sf::Color& color) {
        sf::Color old_color = ns::DebugTextInterface::color;
        ns::DebugTextInterface::color = color;
        m_debug_texts.push_back(new DebugText<T, char>(fn, label, position));
        ns::DebugTextInterface::color = old_color;
    }
    template<typename T, typename ObjT>
    void App::addDebugText(ObjT* object_address, std::function<T(ObjT &)> method_address, const std::string& label, const sf::Vector2f& position, const sf::Color& color) {
        sf::Color old_color = ns::DebugTextInterface::color;
        ns::DebugTextInterface::color = color;
        m_debug_texts.push_back(new DebugText<T, ObjT>(object_address, method_address, label, position));
        ns::DebugTextInterface::color = old_color;
    }
    template<typename T, typename ObjT>
    void App::addDebugText(ns::DebugText<T, ObjT>* debug_text) {
        m_debug_texts.push_back(debug_text);
    }

}
