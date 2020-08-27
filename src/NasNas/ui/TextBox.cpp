/**
* Created by Modar Nasser on 27/08/2020.
**/

#include <cstring>

#include "NasNas/ui/TextBox.hpp"

using namespace ns;

TextBox::TextBox(const std::string& string) :
BitmapText("") {
    m_string = string;
    m_processed_string = string;
}

void TextBox::setMaxWidth(int width) {
    m_max_width = width;
    std::vector<std::string> words_list;
    auto str = m_string;
    auto word = std::strtok(str.data(), " ");
    while (word != nullptr) {
        words_list.emplace_back(word);
        word = std::strtok(nullptr, " ");
    }
    int current_width = 0;
    for (auto& w : words_list) {
        if (current_width + getFont()->computeStringSize(w).x > m_max_width) {
            current_width = getFont()->computeStringSize(w).x;
            w = std::string("\n").append(w);
        }
        else
            current_width += getFont()->computeStringSize(w).x;
    }
    m_processed_string = "";
    for (const auto& w : words_list){
        m_processed_string += w + " ";
    }
}

void TextBox::setMaxLines(int lines_nb) {
    m_max_lines = lines_nb;
}

void TextBox::update() {
    m_counter ++;
    if (m_counter == 5 && m_current_letter_index < m_processed_string.size()) {
        m_current_letter_index++;
        m_counter = 0;
        setString(m_processed_string.substr(0, m_current_letter_index));
    }
}
