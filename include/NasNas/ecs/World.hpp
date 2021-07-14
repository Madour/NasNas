// Created by Modar Nasser on 11/07/2021.

#pragma once

#include "NasNas/core/data/Logger.hpp"
#include "NasNas/core/graphics/Shapes.hpp"

namespace ns::ecs {
    class ComponentGroup;

    class World {
        std::vector<ns::ecs::ComponentGroup*> m_objects;

    public:
        std::vector<ns::LineShape> lines;
        static auto get() -> World& {
            static World instance;
            return instance;
        }

        void add(ns::ecs::ComponentGroup* obj);
        void step() ;
    };
}
