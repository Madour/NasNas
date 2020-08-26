/**
* Created by Modar Nasser on 26/08/2020.
**/

#include "NasNas/core/Transition.hpp"

using namespace ns;

std::vector<std::unique_ptr<Transition>> Transition::list;

Transition::Transition(AppWindow& window) :
m_window(&window),
m_end_callback([](){}) {
    Transition::list.push_back(std::unique_ptr<Transition>(this));
    m_render_texture.create(
        (unsigned int)m_window->getAppView().getSize().x,
        (unsigned int)m_window->getAppView().getSize().y
    );
}

void Transition::start() {
    m_started = true;
}

void Transition::end() {
    m_ended = true;
}

auto Transition::hasStarted() const -> bool {
    return m_started;
}

auto Transition::hasEnded() const -> bool {
    return m_ended;
}

void Transition::addShape(const sf::Shape& shape) {
    m_drawables.push_back(&shape);
}

void Transition::setOnEndCallback(const std::function<void()>& fn) {
    m_end_callback = fn;
}

void Transition::update() {
    onUpdate();
    if (m_ended)
        m_end_callback();

    m_render_texture.clear(sf::Color::Transparent);
    for (const auto& drawable : m_drawables)
        m_render_texture.draw(*drawable, sf::BlendNone);
    m_render_texture.display();
}

void Transition::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sf::Sprite(m_render_texture.getTexture()));
}


CircleOpenTransition::CircleOpenTransition(AppWindow& window) : Transition(window) {
    m_circle.setRadius(1);
    m_circle.setOrigin(1, 1);
    m_circle.setPosition(window.getAppView().getCenter().x, window.getAppView().getCenter().y);
    m_circle.setFillColor(sf::Color::Black);
    addShape(m_circle);
}

void CircleOpenTransition::onUpdate() {
    if (m_circle.getGlobalBounds().left < -50 && m_circle.getGlobalBounds().top < -50)
        end();
    else
        m_circle.scale(1.1f, 1.1f);
}
