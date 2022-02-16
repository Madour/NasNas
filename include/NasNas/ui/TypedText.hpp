/**
* Created by Modar Nasser on 27/08/2020.
**/


#pragma once

#include <string>
#include <vector>

#include <SFML/Window/Event.hpp>

#include <NasNas/core/graphics/BitmapText.hpp>

namespace ns::ui {
/*
    class TypedText : public BitmapText {
    public:
        explicit TypedText(std::wstring string);

        void setMaxWidth(int max_width);
        void setMaxLines(int lines_nb);

        void setTypingDelay(int delay);

        auto isWaiting() const -> bool;
        auto hasEnded() const -> bool;

        virtual void onEvent(const sf::Event& event);
        void update();

    protected:
        void nextPage();

    private:
        std::wstring m_string;
        std::vector<std::wstring> m_pages;
        int m_max_lines = 0;
        int m_counter = 0;
        int m_typing_delay = 0;
        unsigned m_current_page = 0;
        unsigned m_current_letter_index = 0;
    };
*/
}
