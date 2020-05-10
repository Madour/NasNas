/**
* Created by Modar Nasser on 22/04/2020.
**/

#pragma once

#include "NasNas/data/AppComponent.hpp"
#include "NasNas/core/Camera.hpp"

namespace ns {

    class AppWindow: public AppComponent, public sf::RenderWindow {
    public:
        friend App;

        void onCreate() override;
        void onResize() override;
        auto getUIView() const -> const Camera&;
        void scaleView();

        auto getClearColor() const -> const sf::Color&;
        auto setClearColor(const sf::Color& color);

    private:
        int V_WIDTH;
        int V_HEIGHT;
        sf::Color clear_color;
        Camera ui_view;
        void setUIView(int width, int height);
    };

}
