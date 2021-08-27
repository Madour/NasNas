// Created by Modar Nasser on 17/08/2021.

#pragma once

#include <array>
#include <algorithm>
#include <functional>

#include "NasNas/ecs/new/Storage.hpp"

namespace ns::ecs::detail {
    // template<typename...>
    // struct components_view;

    template<typename TEntity, typename... TComps>
    struct components_view {
        using components_pool_super = typename components_pool<TEntity>::super;
        const components_pool_super* ref_set;
        const std::tuple<components_pool<TEntity, TComps>*...> pools;

        components_view(components_pool<TEntity, TComps>&... components) : pools(&components...) {
            std::array<components_pool_super*, sizeof...(TComps)> pools_vec = {
                    static_cast<components_pool_super*>(std::get<components_pool<TEntity, TComps>*>(pools))...
            };
            std::sort(pools_vec.begin(), pools_vec.end(), [] (auto* lhs, auto* rhs) {return lhs->size() < rhs->size();});
            ref_set = pools_vec[0];
        }

        template<typename... Comps>
        auto get(const TEntity ent) const -> decltype(auto) {
            if constexpr(sizeof...(Comps) == 0) {
                return std::tuple_cat(std::forward_as_tuple(std::get<components_pool<TEntity, TComps>*>(pools)->get(ent))...);
            } else if constexpr(sizeof...(Comps) == 1) {
                return (std::get<components_pool<TEntity, Comps> *>(pools)->get(ent), ...);
            } else {
                return std::tuple_cat(std::forward_as_tuple(std::get<components_pool<TEntity, Comps>*>(pools)->get(ent))...);
            }
        }

        auto for_each(std::function<void(Entity, TComps&...)> fn) {
            for (auto& ent : ref_set->data()) {
                if ((std::get<components_pool<TEntity, TComps>*>(pools)->contains(ent) && ...)) {
                    auto&& comps_tuple = std::forward_as_tuple((std::get<components_pool<TEntity, TComps>*>(pools)->get(ent))...);
                    std::apply(fn, std::tuple_cat(std::make_tuple(ent), comps_tuple));
                }
            }
        }

        auto for_each(std::function<void(Entity)> fn) {
            for (auto& ent : ref_set->data()) {
                if ((std::get<components_pool<TEntity, TComps>*>(pools)->contains(ent) && ...)) {
                    std::apply(fn, std::make_tuple(ent));
                }
            }
        }

        auto for_each(std::function<void(TComps&...)> fn) {
            for (auto& ent : ref_set->data()) {
                if ((std::get<components_pool<TEntity, TComps>*>(pools)->contains(ent) && ...)) {
                    auto&& comps_tuple = std::forward_as_tuple((std::get<components_pool<TEntity, TComps>*>(pools)->get(ent))...);
                    std::apply(fn, comps_tuple);
                }
            }
        }

        auto for_each_pair(std::function<void(Entity, Entity)> fn) {
            for (auto it1 = ref_set->data().begin(); it1 != ref_set->data().end(); ++it1) {
                if ((std::get<components_pool<TEntity, TComps>*>(pools)->contains(*it1) && ...)) {
                    for (auto it2 = it1+1; it2 != ref_set->data().end(); ++it2) {
                        if ((std::get<components_pool<TEntity, TComps>*>(pools)->contains(*it2) && ...))
                            std::apply(fn, std::make_tuple(*it1, *it2));
                    }
                }
            }
        }
    };
}
