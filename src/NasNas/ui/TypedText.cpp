/**
* Created by Modar Nasser on 27/08/2020.
**/

#include <cstring>

#include "NasNas/ui/TypedText.hpp"

using namespace ns;
using namespace ns::ui;

TypedText::TypedText(const std::string& string) :
BitmapText(string) {
    m_string = string;
}

void TypedText::setMaxWidth(int max_width) {
    BitmapText::setMaxWidth(max_width);
    m_string = getProcessedString();
    setMaxLines(m_max_lines);
}

void TypedText::setMaxLines(int lines_nb) {
    m_max_lines = lines_nb;
    m_pages.clear();
    if (m_max_lines > 0) {
        int last_index = 0;
        int new_line_count = 0;
        for (int i = 0; i < m_string.size(); ++i) {
            if (m_string[i] == '\n')
                new_line_count++;
            if (new_line_count == m_max_lines) {
                m_pages.push_back(m_string.substr(last_index, i-last_index));
                last_index = i+1;
                new_line_count = 0;
            }
        }
        m_pages.push_back(m_string.substr(last_index, m_string.size()-last_index));
    }
    else
        m_pages.push_back(m_string);
}

void TypedText::setTypingDelay(int delay) {
    if (delay < 0) m_typing_delay = -1;
    else m_typing_delay = delay;
}

bool TypedText::isWaiting() {
    return m_current_letter_index == m_pages[m_current_page].size();
}

bool TypedText::hasEnded() {
    return m_current_page == m_pages.size()-1;
}

void TypedText::nextPage() {
    if (!hasEnded()) {
        m_current_page++;
        m_current_letter_index = 0;
        m_counter = 0;
    }
}

void TypedText::onEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            nextPage();
        }
    }
}

void TypedText::update() {
    if (m_current_letter_index == 0) {
        if (m_current_page == 0)
            BitmapText::setMaxWidth(0);
        if (m_typing_delay < 0)
            setString(m_pages[m_current_page]);
    }
    if (m_counter == m_typing_delay) {
        m_counter = 0;
        if (!isWaiting())
            setString(m_pages[m_current_page].substr(0, ++m_current_letter_index));
    }
    else
        m_counter++;
}
