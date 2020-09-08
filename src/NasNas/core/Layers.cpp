/**
* Created by Modar Nasser on 15/04/2020.
**/


#include "NasNas/core/Layers.hpp"

using namespace ns;

Layer::Layer(const std::string& name) {
    m_name = name;
}

void Layer::clear() {
    m_drawables.clear();
}

void Layer::add(const LayerDrawablesTypes& drawable) {
    m_drawables.push_back(drawable);
}

void Layer::remove(const LayerDrawablesTypes& drawable) {
    auto it = std::find(m_drawables.begin(), m_drawables.end(), drawable);
    if (it != m_drawables.end())
        m_drawables.erase(it);
    else
        std::cout << "Warning : trying to remove a non existant drawable (type index "
                  << drawable.index() << ") from Layer " << m_name << ".\n";
}

void Layer::ySort() {
    std::sort(std::begin(m_drawables), std::end(m_drawables),
              [](auto const& lhs, auto const& rhs){
            return std::visit([](auto const& s) { return s->getPosition().y; }, lhs)
                   <std::visit([](auto const& s) { return s->getPosition().y; }, rhs);
        }
    );
}

auto Layer::getName() -> const std::string& {
    return m_name;
}

auto Layer::getDrawables() -> std::vector<LayerDrawablesTypes>& {
    return m_drawables;
}
