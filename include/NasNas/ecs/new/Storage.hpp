// Created by Modar Nasser on 15/08/2021.
#pragma once

#include <type_traits>

namespace ns::ecs::detail {

    template <typename T, typename = std::enable_if<std::is_integral_v<T>>>
    struct sparse_set {
        std::unordered_map<T, size_t> sparse;  // map[elmnt] = index
        std::vector<T> packed;                 // vec[index] = elmnt

        virtual void push(T elmnt) {
            packed.emplace_back(elmnt);
            sparse[elmnt] = packed.size() - 1;
        }

        virtual void remove(T elmnt) {
            const auto index = sparse[elmnt];

            if (index != packed.size() - 1) {
                packed[index] = packed[packed.size() - 1];
                sparse[packed[index]] = index;
            }

            packed.pop_back();
            sparse.erase(elmnt);
        }

        virtual auto contains(T elmnt) -> bool {
            return sparse.find(elmnt) == sparse.end();
        }

        virtual auto index(T elmnt) -> std::size_t {
            return sparse[elmnt];
        }
    };

    template <typename TEntity, class TComp>
    struct components_pool : sparse_set<TEntity> {
        using parent = sparse_set<TEntity>;
        std::vector<TComp> components;               // vec[index] = comp

        template <typename ...Targs>
        TComp& add(TEntity ent, Targs ...args) {
            parent::push(ent);
            return components.emplace_back(args...);
        }

        void remove(TEntity ent) override {
            if (!contains(ent))
                return;

            const auto i = index(ent);

            if (i != components.size() - 1) {
                components[i] = std::move(components[components.size() - 1]);
            }
            components.pop_back();

            parent::remove(ent);
        }
    };
}
