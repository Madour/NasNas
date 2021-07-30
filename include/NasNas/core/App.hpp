/**
* Created by Modar Nasser on 15/04/2020.
**/


#pragma once

#include "NasNas/core/data/Config.hpp"
#include "NasNas/core/data/ShaderHolder.hpp"

#include "NasNas/core/Scene.hpp"
#include "NasNas/core/Layer.hpp"
#include "NasNas/core/Camera.hpp"
#include "NasNas/core/Window.hpp"
#include "NasNas/core/Transition.hpp"
#include "NasNas/core/graphics/SpriteBatch.hpp"
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
            float scale=1.f,
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
        App(std::string title, int w_width, int w_height,
            int v_width=ns::Config::Window::view_size.x,
            int v_height=ns::Config::Window::view_size.y,
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
        auto getTitle() const -> const std::string&;

        /**
         * \brief Get the AppWindow
         *
         * \return Reference to the AppWindow
         */
        auto getWindow() -> AppWindow&;

        auto getMousePosition(Camera& cam) const -> sf::Vector2f;

        /**
         * \brief Get all the Scene objects created within the App
         *
         * \return Vector of Scene objects
         */
        auto allScenes() -> std::vector<Scene>&;

        /**
         * \brief Get a Scene by name
         *
         * \param name Name of the Scene to get
         * \return Reference to the requested Scene object
         */
        auto getScene(const std::string& name) -> Scene&;

        /**
         * \brief Get all the Camera objects created within the App
         *
         * \return Vector of Camera objects
         */
        auto allCameras() -> std::vector<Camera>&;

        /**
         * \brief Get a Camera by name
         *
         * \param name Name of the Camera to get
         * \return Reference to the requested Camera
         */
        auto getCamera(const std::string& name) -> Camera&;

        /**
        * \brief Toggle fullscreen display.
        */
        void toggleFullscreen();

        /**
         * \brief Starts the game loop.
         */
        void run();

    protected:

        /**
         * \brief Creates a Scene object and returns a reference to it
         *
         * \param width Width of the new Scene
         * \param height Height of the new Scene
         *
         * \return Reference to the created Scene object
         */
        auto createScene(const std::string& name) -> Scene&;

        /**
         * \brief Creates a Camera object and returns a reference to it
         *
         * \param name Name of the Camera
         * \param order Order of rendering of the Camera
         * \param view Rectangle representing the position and size of the Camera
         * \param viewport Viewport of the Camera on the AppWindow
         *
         * \return Reference to the created Camera object
         */
        auto createCamera(
                const std::string& name, int order,
                const ns::IntRect& view={{0, 0}, Config::Window::view_size},
                const ns::FloatRect& viewport={0, 0, 1.f, 1.f}
        ) -> Camera&;

        /**
         * \brief Creates a Camera object and returns a reference to it
         *
         * \param name Name of the Camera
         * \param order Order of rendering of the Camera
         * \param view Rectangle representing the position and size of the Camera
         *
         * \return Reference to the created Camera object *
         */
        auto createCamera(const std::string& name, int order, const ns::FloatRect& viewport) -> Camera&;


        /**
         * \brief Creates a label only DebugText object and render it on the AppWindow directly
         */
        void addDebugText(const std::string& label, const sf::Vector2f& position, const sf::Color& color = ns::DebugTextInterface::color);

        /**
         * \brief Creates a DebugText object and render it on the AppWindow directly
         *
         * DebugText takes the address of a variable and will display its value on the AppWindow
         * at the given position. The label is displayed near the value. DebugText let you visualize
         * the variable's value changing in real time.
         *
         * \tparam T Type of the variable to be displayed
         *
         * \param label Label of the DebugText
         * \param var_address Address of the variable
         * \param position Position of the DebugText on the AppWindow
         * \param color Fill color of the DebugText
         */
        template<typename T>
        void addDebugText(const std::string& label, T* var_address, const sf::Vector2f& position, const sf::Color& color = ns::DebugTextInterface::color);

        /**
         * \brief Creates a DebugText object and render it on the AppWindow directly
         *
         * DebugText takes the address of a variable and will display its value on the AppWindow
         * at the given position. The label is displayed near the value. DebugText let you visualize
         * the variable's value changing in real time.
         *
         * \tparam T Type of the variable to be displayed
         *
         * \param label Label of the DebugText
         * \param var_address Address of the variable (const)
         * \param position Position of the DebugText on the AppWindow
         * \param color Fill color of the DebugText
         */
        template<typename T>
        void addDebugText(const std::string& label, const T* var_address,const sf::Vector2f& position, const sf::Color& color = ns::DebugTextInterface::color);

        /**
         * \brief Creates a DebugText object and render it on the AppWindow directly
         *
         * \tparam T Type of the value returned by the lambda function
         *
         * \param label Label of the DebugText
         * \param fn Lambda function to be evaluated
         * \param position Position of the DebugText on the AppWindow
         * \param color Fill color of the DebugText
         */
        template<typename T>
        void addDebugText(const std::string& label, std::function<T()> fn, const sf::Vector2f& position, const sf::Color& color = ns::DebugTextInterface::color);

        /**
         * \brief Adds a DebugText to the App from a DebugText pointer
         *
         * \tparam T Return type of the method to be evaluated
         * \tparam ObjT Type of the method's object
         *
         * \param debug_text Pointer to a DebugText object
         */
        template<typename T>
        void addDebugText(DebugText<T>* debug_text);

        /**
         * \brief The App enters sleep mode, the App will not update.
         * Used for Android when application runs in background
         */
        void sleep();

        /**
         * \brief The App awakes from sleep mode.
         * Used for Android when application run as main process.
         */
        void awake();

        auto getDt() const -> float;

        /**
         * \brief Handles SFML events
         *
         * Virtual method, can be defined by the user.
         * `onEvent` will be called each time a window event occurs.
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

        /**
         * \brief Optional method called just before rendering
         *
         * Virtual method, can be defined by the user
         * It can be used to execute code before rendering outside of the `update`
         */
        virtual void preRender() {};

    private:
        AppWindow m_window;     ///< AppWindow
        sf::RenderTexture m_renderer;
        std::string m_title;    ///< Title of the App
        bool m_fullscreen;      ///< Is the AppWindow fullscreen ?
        int m_ups;              ///< Update per second
        int m_desired_fps;      ///< Frame per second
        sf::Clock m_fps_clock;  ///< Clock to compute real FPS
        float m_dt;             ///< Delta time, time between two frames
        bool m_sleeping = false;

        std::vector<Camera> m_cameras;
        std::vector<Scene> m_scenes;
        std::multimap<int, Camera*> m_cameras_map;
        std::vector<DebugTextInterface*> m_debug_texts;
        std::vector<sf::Vertex> m_debug_bounds;

        /**
         * \brief Updates m_inputs everytime a key event occurs
         *
         * Inserts key code when event is KeyPressed and removes it when event is KeyReleased
         *
         * \param event The key event
         */
        static void storeInputs(sf::Event event);

        /**
         * \brief Render App content to the AppWindow
         */
        void render();

        void renderDebugBounds();
        void storeDrawableDebugRects(const ns::FloatRect& drawable_bounds, Camera& cam,
                                     const sf::FloatRect& render_bounds, sf::Vector2f& offset,
                                     const sf::FloatRect& global_vport, const sf::FloatRect& local_vport);
    };

    template<typename T>
    void App::addDebugText(const std::string& label, T* var_address, const sf::Vector2f& position, const sf::Color& color) {
        auto* dbg_txt = new DebugText<T>(label, var_address, position);
        dbg_txt->setFillColor(color);
        m_debug_texts.push_back(dbg_txt);
    }
    template<typename T>
    void App::addDebugText(const std::string& label, const T* var_address, const sf::Vector2f& position, const sf::Color& color) {
        auto* dbg_txt = new DebugText<T>(label, var_address, position);
        dbg_txt->setFillColor(color);
        m_debug_texts.push_back(dbg_txt);
    }
    template<typename T>
    void App::addDebugText(const std::string& label, std::function<T()> fn, const sf::Vector2f& position, const sf::Color& color) {
        auto* dbg_txt = new DebugText<T>(label, fn, position);
        dbg_txt->setFillColor(color);
        m_debug_texts.push_back(dbg_txt);
    }
    template<typename T>
    void App::addDebugText(ns::DebugText<T>* debug_text) {
        m_debug_texts.push_back(debug_text);
    }

}
