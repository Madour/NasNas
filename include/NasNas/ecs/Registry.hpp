// Created by Modar Nasser on 15/08/2021.

#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <string>

#include <NasNas/ecs/System.hpp>
#include <NasNas/ecs/Storage.hpp>
#include <NasNas/ecs/View.hpp>

namespace ns::ecs::detail {
    template <typename TEntity=Entity>
    class Registry {
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

            for (auto& [id, pool] : m_pools) {
                pool->remove(ent);
            }

            m_cemetery.push(ent);
            m_entities[it-m_entities.begin()] = m_entities.back();
            m_entities.pop_back();
        }

        template <typename TComp, typename ...Targs>
        auto attach(TEntity ent, Targs&& ...args) -> TComp& {
            return getPool<TComp>().add(ent, std::forward<Targs>(args)...);
        }

        template <typename TComp>
        void detach(TEntity ent) {
            if (has<TComp>(ent)) {
                getPool<TComp>().remove(ent);
            }
        }

        template <typename TComp>
        auto all() -> std::vector<TComp>& {
            return getPool<TComp>().components();
        }

        template <typename TComp>
        auto has(TEntity ent) -> bool {
            return getPool<TComp>().contains(ent);
        }

        template <typename TComp>
        auto get(TEntity ent) -> TComp& {
            auto& pool = getPool<TComp>();
            if (has<TComp>(ent)) {
                return pool.components().at(pool.index(ent));
            } else {
                throw std::runtime_error("Trying to get non existing component from entity "+std::to_string(ent));
            }
        }

        auto count() const -> std::size_t {
            return m_entities.size();
        }

        template <typename... TComps>
        auto view() const -> components_view<TEntity, TComps...> {
            return { getPool<TComps>()...};
        }

        template <typename... TComps, typename Func>
        auto run(Func fn) {
            view<TComps...>().for_each(std::move(fn));
        }

        template <typename... TComps>
        auto run(System<TComps...>& system) {
            view<TComps...>().for_each(system.m_function);
        }

    private:
        template <typename TComp>
        auto getPool() const -> components_pool<TEntity, TComp>& {
            auto comp_id = getTypeId<TComp>();

            if (m_pools.find(comp_id) == m_pools.end()) {
                m_pools[comp_id] = std::make_unique<components_pool<TEntity, TComp>>();
            }
            return *static_cast<components_pool<TEntity, TComp>*>(m_pools.at(comp_id).get());
        }

        std::vector<TEntity> m_entities;
        std::queue<TEntity> m_cemetery;
        mutable std::map<UID, std::unique_ptr<sparse_set<TEntity>>> m_pools;
    };

}

namespace ns {
    // can't use inline because of VS2017 bug (https://developercommunity.visualstudio.com/t/inline-static-destructors-are-called-multiple-time/1157794)
    extern ecs::detail::Registry<ecs::Entity> Ecs;
}
