// Created by Modar Nasser on 28/08/2021.

#pragma once

#include <memory>

#include <NasNas/ecs/Registry.hpp>

namespace ns {
    class EntityObject {
        ecs::Entity id;
    protected:
        inline auto getId() const -> ecs::Entity { return id; }
    public:
        EntityObject();
        virtual ~EntityObject();

        template <class TComp, typename ...Targs>
        TComp& add(Targs ...args) {
            return Ecs.attach<TComp>(id, args...);
        }

        template <typename TComp>
        void remove() {
            Ecs.detach<TComp>(id);
        }

        template <typename TComp>
        auto has() const -> bool {
            return Ecs.has<TComp>(id);
        }

        template <typename TComp>
        auto get() const -> TComp& {
            if (has<TComp>()) {
                return Ecs.get<TComp>(id);
            }
            throw std::runtime_error("Entity " + std::to_string(id) + " does not have component " + typeid(TComp).name());
        }

    };
}
