// Created by Modar Nasser on 11/07/2021.

#pragma once

#include "NasNas/core/data/Logger.hpp"

namespace ns::ecs {
    class ComponentGroup;

    class World {
        std::vector<ns::ecs::ComponentGroup*> m_objects;

    public:
        static auto get() -> World& {
            static World instance;
            return instance;
        }

        void add(ns::ecs::ComponentGroup* obj);
        void step() ;
    };
}
