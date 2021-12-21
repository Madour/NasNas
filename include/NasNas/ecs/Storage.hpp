// Created by Modar Nasser on 15/08/2021.

#pragma once

#include <map>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace ns::ecs {
    using Entity = unsigned long;
}

namespace ns::ecs::detail {
    using UID = unsigned long;
    inline UID get_next_id() {
        static UID counter = 0;
        return counter++;
    }

    template <class T>
    auto getTypeId() -> decltype(auto) {
        static auto id = get_next_id();
        return id;
    }

    template <typename T, typename = std::enable_if<std::is_integral_v<T>>>
    struct sparse_set {
        ~sparse_set() = default;
        auto data() const -> const std::vector<T>& {
            return m_packed;
        }

        void append(T elmnt) {
            m_packed.emplace_back(elmnt);
            m_sparse[elmnt] = m_packed.size() - 1;
        }

        virtual void remove(T elmnt) {
            const auto index = m_sparse[elmnt];

            if (index != m_packed.size() - 1) {
                m_packed[index] = m_packed[m_packed.size() - 1];
                m_sparse[m_packed[index]] = index;
            }

            m_packed.pop_back();
            m_sparse.erase(elmnt);
        }

        auto size() const -> std::size_t {
            return m_packed.size();
        }

        auto contains(T elmnt) const -> bool {
            return m_sparse.find(elmnt) != m_sparse.end();
        }

        auto index(T elmnt) const -> std::size_t {
            return m_sparse.at(elmnt);
        }

    private:
        std::map<T, size_t> m_sparse; // map[elmnt] = index
        std::vector<T> m_packed;      // vec[index] = elmnt
    };

    template <typename TEntity, typename...>
    struct components_pool : sparse_set<TEntity>{
        using super = sparse_set<TEntity>;
    };

    template <typename TEntity, typename TComp>
    struct components_pool<TEntity, TComp> :  components_pool<TEntity> {
        using super = components_pool<TEntity>;

        auto components() -> std::vector<TComp>& {
            return m_components;
        }

        template <typename ...Targs>
        auto add(TEntity ent, Targs&& ...args) -> TComp& {
            if (this->contains(ent))
                return get(ent);

            super::append(ent);
            if constexpr(sizeof...(args) == 0)
                return m_components.emplace_back();
            else if constexpr(std::is_aggregate_v<TComp>) {
                m_components.push_back({std::forward<Targs>(args)...});
                return m_components.back();
            }
            else
                return m_components.emplace_back(std::forward<Targs>(args)...);
        }

        void remove(TEntity ent) override {
            if (!this->contains(ent))
                return;

            const auto i = this->index(ent);

            if (i != m_components.size() - 1) {
                m_components[i] = std::move(m_components[m_components.size() - 1]);
            }
            m_components.pop_back();

            super::remove(ent);
        }

        auto get(TEntity ent) -> TComp& {
            if (this->contains(ent))
                return m_components[this->index(ent)];
            throw std::runtime_error("Trying to get unexisting entity " + std::to_string(ent)
                                    + " from pool of type " + typeid(TComp).name());
        }

    private:
        std::vector<TComp> m_components;    // vec[index] = comp
    };
}
