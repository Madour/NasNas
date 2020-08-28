/**
* Created by Modar Nasser on 27/08/2020.
**/


#pragma once

#include "NasNas/data/Drawable.hpp"
#include "NasNas/core/BitmapText.hpp"

namespace ns::ui {
    class TypedText : public BitmapText {
    public:
        explicit TypedText(const std::string& string);

        void setMaxWidth(int max_width) override;
        void setMaxLines(int lines_nb);

        void setTypingDelay(int delay);

        bool isWaiting();
        bool hasEnded();

        virtual void onEvent(const sf::Event& event);
        void update();

    protected:
        void nextPage();

    private:
        std::string m_string;
        std::vector<std::string> m_pages;
        int m_max_lines = 0;
        int m_counter = 0;
        int m_typing_delay = 0;
        int m_current_page = 0;
        int m_current_letter_index = 0;
    };

}
