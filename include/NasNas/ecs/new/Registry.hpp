// Created by Modar Nasser on 15/08/2021.
#pragma once

#include <queue>
#include "NasNas/ecs/new/Types.hpp"
#include "NasNas/ecs/new/Storage.hpp"
#include "NasNas/ecs/new/View.hpp"

namespace ns::ecs::detail {

    template <typename TEntity=Entity>
    class Registry {
        std::vector<TEntity> m_entities;
        std::queue<TEntity> m_cemetery;
        std::unordered_map<UID, sparse_set<TEntity>*> m_pools;

        template <class TComp>
        auto getPool() -> components_pool<TEntity, TComp>& {
            auto comp_id = getTypeId<TComp>();

            if (m_pools.find(comp_id) == m_pools.end()) {
                m_pools[comp_id] = new components_pool<TEntity, TComp>;
            }
            return *static_cast<components_pool<TEntity, TComp>*>(m_pools.at(comp_id));
        }

    public:
        TEntity create() {
            static TEntity ent_id = 0;
            if (!m_cemetery.empty()) {
                m_entities.emplace_back(m_cemetery.front());
                m_cemetery.pop();
            }
            else {
                m_entities.emplace_back(ent_id++);
            }
            return m_entities.back();
        }

        void destroy(TEntity ent) {
            auto it = std::find(m_entities.begin(), m_entities.end(), ent);
            if (it == m_entities.end())
                return;

            for (auto [id, pool] : m_pools) {
                pool->remove(ent);
            }

            m_cemetery.push(ent);
            m_entities[it-m_entities.begin()] = m_entities.back();
            m_entities.pop_back();
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
        auto all() -> std::vector<TComp>& {
            return getPool<TComp>().components();
        }

        template <class TComp>
        auto has(TEntity ent) -> bool {
            auto& pool = getPool<TComp>();
            return pool.m_sparse.find(ent) != pool.m_sparse.end();
        }

        template <class TComp>
        auto get(TEntity ent) -> TComp& {
            auto& pool = getPool<TComp>();
            if (has<TComp>(ent)) {
                return pool.m_components.at(pool.m_sparse[ent]);
            }
            else {
                throw std::runtime_error("Trying to get non existing component from entity "+std::to_string(ent));
            }
        }

        auto count() const -> std::size_t {
            return m_entities.size();
        }

        template<typename... TComp>
        components_view<TEntity, TComp...> view() {
            return { getPool<TComp>()...};
        }

    };

}

namespace ns {
    inline ecs::detail::Registry<ecs::Entity> Ecs;
}