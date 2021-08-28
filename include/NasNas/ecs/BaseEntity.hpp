/**
* Created by Modar Nasser on 15/04/2020.
**/


#pragma once

#include <memory>
#include "NasNas/ecs/new/Registry.hpp"
#include "NasNas/ecs/ComponentGroup.hpp"

namespace ns {
    namespace ecs::old {
        class BaseEntity : public ecs::ComponentGroup {
        public:
            explicit BaseEntity(const std::string& name);

            auto transform() const -> ecs::Transform*;
            auto inputs() const -> ecs::old::Inputs*;
            auto physics() const -> ecs::Physics*;
            auto collider() const -> ecs::Collider*;

        };
    }

    class BaseEntity {
        ecs::Entity id;
    public:
        BaseEntity() {
            id = Ecs.create();
        }

        ~BaseEntity() {
            Ecs.destroy(id);
        }

        template <class TComp, typename ...Targs>
        TComp& add(Targs ...args) {
            return Ecs.attach<TComp>(id, args...);
        }

        template <typename TComp>
        auto get() const -> TComp& {
            if (Ecs.has<TComp>(id)) {
                return Ecs.get<TComp>(id);
            }
            throw std::runtime_error("Entity " + std::to_string(id) + " does not have component " + typeid(TComp).name());
        }

        template <typename TComp>
        void remove() {
            Ecs.detach<TComp>(id);
        }

    };

}
