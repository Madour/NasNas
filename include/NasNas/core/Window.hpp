/**
* Created by Modar Nasser on 22/04/2020.
**/


#pragma once

#include "NasNas/core/Camera.hpp"

namespace ns {

    class AppWindow : public sf::RenderWindow {
    public:
        /**
         * \brief Get App View defined by user
         *
         * \return App view
         */
        auto getAppView() const -> const sf::View&;

        /**
         * \brief Get Screen View, has same size as the current window size
         *
         * \return Screen View
         */
        auto getScreenView() const -> const sf::View&;

        /**
         * \brief Get clear color of the window
         *
         * \return Clear color
         */
        auto getClearColor() const -> const sf::Color&;

        /**
         * \brief Set clear color of the window
         *
         * \param color Clear color
         */
        void setClearColor(const sf::Color& color);

    private:
        sf::Color m_clear_color;        ///< Window clear color
        sf::View m_app_view;            ///< App view defined by use
        sf::View m_screen_view;         ///< Screen view, same size as the window

        void onCreate() override;
        void onResize() override;

        /**
         * \brief Scales AppView on window resize to keep aspect ratio defined by user
         */
        void scaleView();
    };

}
