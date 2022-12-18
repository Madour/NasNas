/**
* Created by Modar Nasser on 23/06/2020.
**/


#pragma once

#include <string>
#include <unordered_map>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <NasNas/core/data/Utils.hpp>
#include <NasNas/core/AppAccess.hpp>

#if defined(__APPLE__) && defined(__MACH__)
#include "TargetConditionals.h"
#endif

namespace ns {
    struct AppConfig {
        std::string title = "NasNas app";
        sf::Vector2u resolution = {720, 480};
        float scale = 1.f;
        int frame_rate = 60;
        int update_rate = 60;
        bool vertical_sync = false;
        int window_style = sf::Style::Default;
        unsigned antialiasing_level = 0;
        bool key_repeat = false;
        bool cursor_visible = true;
        bool cursor_grabbed = false;

        auto getViewSize() const -> const sf::Vector2f&;

        auto getViewRatio() const -> float;

    private:    // private configs set by the App
        friend App;
        sf::VideoMode video_mode;
        sf::Vector2f view_size;
        float view_ratio = 1.f;
    };

    class Settings : AppAccess<> {
        friend App;
        static AppConfig user_config;

        struct debug_info : public utils::bool_switch {
            friend Settings;

            debug_info(const debug_info&) = delete;

            utils::bool_switch show_fps;
            utils::bool_switch show_text;
            utils::bool_switch show_bounds;

            auto operator=(bool value) -> debug_info& override;

        private:
            debug_info();

            unsigned int m_state;
        };

    public:
        static debug_info debug_mode;

        static void setConfig(AppConfig config);

        static auto getConfig() -> const AppConfig&;
    };

    namespace Module {
        extern const bool Core;
        extern const bool Reslib;
        extern const bool Ecs;
        extern const bool Tilemapping;
        extern const bool Ui;
    }

    namespace Platform {
        constexpr bool Windows =
#if defined(_WIN32)
                true;
#define NASNAS_WINDOWS
#else
                false;
#endif
        constexpr bool Linux =
#if defined(__unix__) && !defined(__ANDROID__)
                true;
#define NASNAS_LINUX
#else
                false;
#endif
        constexpr bool Android =
#if defined(__unix__) && defined(__ANDROID__)
                true;
#define NASNAS_ANDROID
#else
                false;
#endif
        constexpr bool macOS =
#if defined(__APPLE__) && defined(__MACH__) && (!TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR)
                true;
#define NASNAS_MACOS
#else
                false;
#endif
        constexpr bool iOS =
#if defined(__APPLE__) && defined(__MACH__) && (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
                true;
#define NASNAS_IOS
#else
                false;
#endif
    }
}
