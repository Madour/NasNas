/**
* Created by Modar Nasser on 27/08/2020.
**/


#pragma once

#include "NasNas/data/Drawable.hpp"
#include "NasNas/core/BitmapText.hpp"

namespace ns {
    class TextBox : public Drawable{
        TextBox(const std::string& string, const BitmapFont& font);
    };

}
