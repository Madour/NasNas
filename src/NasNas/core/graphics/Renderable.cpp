// Created by Modar Nasser on 21/04/2021.

#include "NasNas/core/graphics/Renderable.hpp"

using namespace ns;

std::vector<Renderable*> Renderable::list;

Renderable::Renderable() {
    list.push_back(this);
}

Renderable::~Renderable() {
    Renderable::list.erase(std::find(Renderable::list.begin(), Renderable::list.end(), this));
}
