// Created by Modar Nasser on 06/02/2021.

#include "NasNas/ecs/ComponentGroup.hpp"

using namespace ns;
using namespace ns::ecs;

ComponentGroup::ComponentGroup(std::string name) :
m_name(std::move(name))
{}

ComponentGroup::~ComponentGroup() {
    for (auto& item : m_components)
        delete item.second;

    for (auto& item : m_childs)
        delete item.second;
}

auto ComponentGroup::graphics() -> const std::vector<GraphicsComponent*>& {
    return m_graphics;
}

void ComponentGroup::addChild(const std::string& name) {
    auto* child = new ComponentGroup(name);
    child->m_parent = this;
    removeChild(name);
    m_childs[name] = child;
}

auto ComponentGroup::getChild(const std::string& name) const -> ComponentGroup* {
    if (m_childs.count(name) > 0)
        return m_childs.at(name);
    return nullptr;
}

void ComponentGroup::removeChild(const std::string& name) {
    const auto& it = m_childs.find(name);
    if (it != m_childs.end()) {
        delete it->second;
        m_childs.erase(it);
    }
}

auto ComponentGroup::getParent() const -> ComponentGroup* {
    return m_parent;
}

void ComponentGroup::update() {
    if (get<InputsComponent>())
        get<InputsComponent>()->update();
    if (get<PhysicsComponent>())
        get<PhysicsComponent>()->update();
    if (get<ColliderComponent>())
        get<ColliderComponent>()->update();
    for (auto* comp : m_graphics)
        comp->update();
}

auto ComponentGroup::getPosition() const -> sf::Vector2f {
    if (get<TransformComponent>())
        return get<TransformComponent>()->getPosition();
    return {0, 0};
}

auto ComponentGroup::getGlobalBounds() const -> ns::FloatRect {
    float left, top, right, bottom;
    ns::FloatRect result{0, 0, 0, 0};
    bool first = true;
    for (auto* graphic_comp : m_graphics) {
        auto rect = graphic_comp->getGlobalBounds();
        auto topleft = rect.topleft();
        auto topright = rect.topright();
        auto bottomleft = rect.bottomleft();
        auto bottomright = rect.bottomright();
        if (first) {
            left = std::min(topleft.x, bottomleft.x);
            top = std::min(topleft.y, topright.y);
            right = std::max(topright.x, bottomright.x);
            bottom = std::max(bottomleft.y, bottomright.y);
            first = false;
        } else {
            left = std::min(left, std::min(topleft.x, bottomleft.x));
            top = std::min(top, std::min(topleft.y, topright.y));
            right = std::max(right, std::max(topright.x, bottomright.x));
            bottom = std::max(bottom, std::max(bottomleft.y, bottomright.y));
        }
    }
    for (const auto& [name, child] : m_childs) {
        auto rect = child->getGlobalBounds();
        if (get<Transform>())
            rect = get<Transform>()->getTransform().transformRect(rect);
        auto topleft = rect.topleft();
        auto topright = rect.topright();
        auto bottomleft = rect.bottomleft();
        auto bottomright = rect.bottomright();
        if (first) {
            left = std::min(topleft.x, bottomleft.x);
            top = std::min(topleft.y, topright.y);
            right = std::max(topright.x, bottomright.x);
            bottom = std::max(bottomleft.y, bottomright.y);
            first = false;
        } else {
            left = std::min(left, std::min(topleft.x, bottomleft.x));
            top = std::min(top, std::min(topleft.y, topright.y));
            right = std::max(right, std::max(topright.x, bottomright.x));
            bottom = std::max(bottom, std::max(bottomleft.y, bottomright.y));
        }
    }
    if (!first) {
        result.left = left;
        result.top = top;
        result.width = right - left;
        result.height = bottom - top;
    }
    return result;
}


void ComponentGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (get<TransformComponent>())
        states.transform *= get<TransformComponent>()->getTransform();

    for (const auto& comp : m_graphics) {
        target.draw(*comp, states);
    }
    for (const auto& item : m_childs) {
        target.draw(*item.second, states);
    }
    if (Config::debug) {
        if (get<ColliderComponent>())
            target.draw(get<ColliderComponent>()->getCollision().getShape());
    }

}
