/**
* Created by Modar Nasser on 10/11/2020.
**/

#include <utility>

#include "NasNas/core/data/Utils.hpp"

using namespace ns::utils;

auto path::getStem(const std::string& path) -> std::string {
    auto f = path::getFilename(path);
    auto i = f.find_last_of('.');
    if (i == std::string::npos || i == 0)
        return f;
    return f.substr(0, i);

}

auto path::getFilename(const std::string& path) -> std::string {
    auto i = path.find_last_of("/\\");
    if (i == std::string::npos)
        return path;
    return path.substr(i+1);
}

auto path::getExtension(const std::string& path) -> std::string {
    auto f = path::getFilename(path);
    auto i = f.find_last_of('.');
    if (i == std::string::npos || i == 0)
        return "";
    return f.substr(i);
}

auto path::getPath(const std::string& path) -> std::string {
    auto i = path.find_last_of("/\\");
    if (i == std::string::npos)
        return "";
    return path.substr(0, i)+"/";
}

void path::removeFilename(std::string& path) {
    auto i = path.find_last_of("/\\");
    if (i == std::string::npos)
        path.clear();
    else
        path = std::string(path.begin(), path.begin()+i)+"/";
}


bool_switch::bool_switch(std::function<void()>  on_true, std::function<void()>  on_false) :
m_val(false),
m_on_true(std::move(on_true)),
m_on_false(std::move(on_false))
{}

auto bool_switch::operator=(bool value) -> bool_switch& {
    value ? m_on_true() : m_on_false();
    m_val = value;
    return *this;
}

auto bool_switch::operator=(const bool_switch& other) -> bool_switch& {
    other.m_val ? m_on_true() : m_on_false();
    m_val = other.m_val;
    return *this;
}

bool_switch::operator bool() const {
    return m_val;
}

auto ns::utils::getRandomFloat(float min, float max) -> float {
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX)*(max-min);
}

auto ns::utils::getRandomInt(int min, int max) -> int {
    return min + rand()%(max-min);
}

auto ns::utils::computeBounds(std::initializer_list<sf::FloatRect> rects) -> ns::FloatRect {
    return computeBounds(rects.begin(), rects.end());
}
