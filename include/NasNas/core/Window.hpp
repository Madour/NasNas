/**
* Created by Modar Nasser on 22/04/2020.
**/


#pragma once

#include "NasNas/core/Camera.hpp"

namespace ns {

    class AppWindow : public sf::RenderWindow {
    public:
        void onCreate() override;
        void onResize() override;

        auto getAppView() const -> const Camera&;
        auto getScreenView() const -> const sf::View&;
        void scaleView();

        auto getClearColor() const -> const sf::Color&;
        void setClearColor(const sf::Color& color);

    private:
        sf::Color m_clear_color;
        Camera m_app_view;
        sf::View m_screen_view;

    };

}
