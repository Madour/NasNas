/**
* Created by Modar Nasser on 26/08/2020.
**/

#include <NasNas/core/Transition.hpp>

#include <cmath>

#include <SFML/Graphics/Sprite.hpp>

#include <NasNas/core/data/Config.hpp>
#include <NasNas/core/data/Maths.hpp>
#include <NasNas/core/App.hpp>

using namespace ns;

Transition::Transition() :
m_end_callback([](){})
{
    auto texture_size = sf::Vector2u(ns::Settings::getConfig().getViewSize());
    m_render_texture.create(texture_size.x, texture_size.y);
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

void Transition::onEnd(const std::function<void()>& fn) {
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
    target.draw(sf::Sprite(m_render_texture.getTexture()), states);
}

using namespace ns::transition;

CircleOpen::CircleOpen(int duration_ms) :
m_duration_ms(duration_ms),
m_scale_factor(1.f) {
    const auto& c = app().getWindow().getAppView().getCenter();
    const auto& s = app().getWindow().getAppView().getSize();

    m_rectangle.setSize(s);
    m_rectangle.setFillColor(sf::Color::Black);
    addShape(m_rectangle);

    m_circle.setRadius(1);
    m_circle.setOrigin(1, 1);
    m_circle.setPosition(c.x, c.y);
    m_circle.setFillColor(sf::Color::Transparent);
    addShape(m_circle);

    m_limit = distance(c, sf::Vector2f(c.x - s.x/2, c.y + s.y/2));

    setDuration(m_duration_ms);
}

void CircleOpen::setDuration(int duration_ms) {
    m_duration_ms = duration_ms;
    m_scale_factor = (float)std::pow(m_limit, 1./(Settings::getConfig().update_rate * m_duration_ms / 1000.));
}

void CircleOpen::onUpdate() {
    m_circle.scale(m_scale_factor, m_scale_factor);
    if (m_circle.getScale().x > m_limit)
        end();
}


CircleClose::CircleClose(int duration_ms) :
m_duration_ms(duration_ms),
m_scale_factor(1.f) {
    const auto& c = app().getWindow().getAppView().getCenter();
    const auto& s = app().getWindow().getAppView().getSize();

    m_rectangle.setSize(s);
    m_rectangle.setFillColor(sf::Color::Black);
    addShape(m_rectangle);

    m_circle.setRadius(1);
    m_circle.setOrigin(1, 1);
    m_circle.setScale({distance(c, sf::Vector2f(c.x - s.x/2, c.y + s.y/2)),
                       distance(c, sf::Vector2f(c.x - s.x/2, c.y + s.y/2))});
    m_circle.setPosition(c.x, c.y);
    m_circle.setFillColor(sf::Color::Transparent);
    addShape(m_circle);

    setDuration(m_duration_ms);
}

void CircleClose::setDuration(int duration_ms) {
    m_duration_ms = duration_ms;
    m_scale_factor = 2.f - (float)std::pow(m_circle.getScale().x, 1./(Settings::getConfig().update_rate * m_duration_ms / 1000.));
}

void CircleClose::onUpdate() {
    m_circle.scale(m_scale_factor, m_scale_factor);
    if (m_circle.getGlobalBounds().width <= 1)
        end();
}
