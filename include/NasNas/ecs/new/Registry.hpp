// Created by Modar Nasser on 15/08/2021.
#pragma once

#include "NasNas/ecs/new/Types.hpp"
#include "NasNas/ecs/new/Storage.hpp"


namespace ns::ecs::detail {
    template<typename...>
    struct components_view;

    template<typename TEntity, typename... TComp>
    struct components_view<TEntity, TComp...> {
        std::tuple<components_pool<TEntity, TComp>*...> pools;
        components_view(components_pool<TEntity, TComp>&... components) : pools(&components...)
        {}
    };

    template <typename TEntity=Entity>
    class Registry {
        std::vector<TEntity> entities;
        std::queue<TEntity> cemetery;
        std::unordered_map<UID, sparse_set<TEntity>*> pools;

    public:
        TEntity create() {
            static TEntity ent_id = 0;
            if (!cemetery.empty()) {
                entities.emplace_back(cemetery.front());
                cemetery.pop();
            }
            else {
                entities.emplace_back(ent_id++);
            }
            return entities.back();
        }

        void destroy(TEntity ent) {
            auto it = std::find(entities.begin(), entities.end(), ent);
            if (it == entities.end())
                return;

            for (auto [id, pool] : pools) {
                pool->remove(ent);
            }

            cemetery.push(ent);
            entities[it-entities.begin()] = entities.back();
            entities.pop_back();
        }

        template <class TComp>
        auto getPool() -> components_pool<TEntity, TComp>& {
            auto comp_id = getTypeId<TComp>();

            if (pools.find(comp_id) == pools.end()) {
                pools[comp_id] = new components_pool<TEntity, TComp>;
            }
            return *static_cast<components_pool<TEntity, TComp>*>(pools.at(comp_id));
        }

        template <class TComp, typename ...Targs>
        auto attach(TEntity ent, Targs ...args) -> TComp& {
            return getPool<TComp>().add(ent, args...);
        }

        template <class TComp>
        void detach(TEntity ent) {
            if (has<TComp>(ent)) {
                getPool<TComp>().remove(ent);
            }
        }

        template <class TComp>
        auto getAll() -> std::vector<TComp>& {
            return getPool<TComp>().components;
        }

        template <class TComp>
        auto has(TEntity ent) -> bool {
            auto& pool = getPool<TComp>();
            return pool.sparse.find(ent) != pool.sparse.end();
        }

        template <class TComp>
        auto get(TEntity ent) -> TComp& {
            auto& pool = getPool<TComp>();
            if (has<TComp>(ent)) {
                return pool.components.at(pool.sparse[ent]);
            }
            else {
                throw std::runtime_error("Trying to get non existing component from entity "+std::to_string(ent));
            }
        }

        template<typename... TComp>
        components_view<TEntity, TComp...> view() {
            return { getPool<TComp>()...};
        }

    };

}

namespace ns {
    static ecs::detail::Registry<ecs::Entity> Ecs;
}