/**
* Created by Modar Nasser on 27/08/2020.
**/


#pragma once

#include "NasNas/data/Drawable.hpp"
#include "NasNas/core/BitmapText.hpp"

namespace ns {
    class TextBox : public BitmapText {
    public:
        explicit TextBox(const std::string& string);
        void setMaxWidth(int width);
        void setMaxLines(int lines_nb);

        void update();

    private:
        std::string m_string;
        std::string m_processed_string;
        int m_current_letter_index = 0;
        int m_counter = 0;
        int m_max_width = 0;
        int m_max_lines = 0;
    };

}
