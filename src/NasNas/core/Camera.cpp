/**
* Created by Modar Nasser on 20/04/2020.
**/

#include <NasNas/core/Camera.hpp>

#include <cmath>

#include <SFML/Graphics/RenderTarget.hpp>

#include <NasNas/core/data/Config.hpp>
#include <NasNas/core/Scene.hpp>

using namespace ns;

Camera::Camera(std::string name, int render_order) :
m_name(std::move(name)),
m_render_order(render_order),
m_visible(true),
m_scene(nullptr),
m_followee(std::nullopt),
m_frames_delay(0)
{
    m_base_view = ns::IntRect(0, 0, 1000, 1000);
    m_base_viewport = ns::FloatRect(0, 0, 1, 1);
    m_render_texture = std::make_unique<sf::RenderTexture>();
    m_render_texture->setRepeated(true);
}

void Camera::reset(int x, int y, int w, int h) {
    reset(ns::IntRect(x, y, w, h));
}
void Camera::reset(const sf::Vector2i& position, const sf::Vector2i& size) {
    reset(ns::IntRect(position.x, position.y, size.x, size.y));
}
void Camera::reset(const ns::IntRect& rectangle) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = ns::Settings::getConfig().antialiasing_level;
    m_base_view = rectangle;
    m_render_texture->create(static_cast<unsigned>(rectangle.width), static_cast<unsigned>(rectangle.height), settings);
    sf::View::reset(sf::FloatRect(rectangle));
}

void Camera::resetViewport(float x, float y, float w, float h) {
    m_base_viewport = {x, y, w, h};
}
void Camera::resetViewport(const sf::Vector2f& position, const sf::Vector2f& size) {
    m_base_viewport = {position, size};
}
void Camera::resetViewport(const sf::FloatRect& rect) {
    m_base_viewport = rect;
}

auto Camera::getViewport() const -> const ns::FloatRect& {
    return m_base_viewport;
}

auto Camera::hasScene() -> bool { return m_scene != nullptr; }
void Camera::setVisible(bool value) { m_visible = value; }
auto Camera::isVisible() const -> bool { return m_visible; }

void Camera::lookAt(Scene& target_scene) {
    m_scene = &target_scene;
}

void Camera::follow(sf::Transformable& transformable) {
    m_followee = &transformable;
}

void Camera::unfollow() {
    m_followee.reset();
}

auto Camera::getRenderOrder() const -> int {
    return m_render_order;
}

auto Camera::getFramesDelay() const -> unsigned int {
    return m_frames_delay;
}
void Camera::setFramesDelay(unsigned int value) { m_frames_delay = value; }

void Camera::setLimitsRect(const ns::IntRect& rectangle) {
    m_limits = rectangle;
}

auto Camera::getPosition() const -> sf::Vector2f {
    return {getLeft(), getTop()};
}

auto Camera::getFolloweePosition() const -> const sf::Vector2f& {
    if (m_followee.has_value())
        return m_followee.value()->getPosition();
    else
        return getCenter();
}

auto Camera::getLeft() const -> float{
    return getCenter().x - getSize().x/2.f;
}
void Camera::setLeft(float value) {
    setCenter(value + getSize().x/2, getCenter().y);
}

auto Camera::getRight() const -> float {
    return getCenter().x + getSize().x/2.f;
}
void Camera::setRight(float value) {
    setCenter(value - getSize().x/2, getCenter().y);
}

auto Camera::getTop() const -> float {
    return getCenter().y - getSize().y/2.f;
}
void Camera::setTop(float value) {
    setCenter(getCenter().x, value + getSize().y/2);
}

auto Camera::getBottom() const -> float {
    return getCenter().y + getSize().y/2.f;
}
void Camera::setBottom(float value) {
    setCenter(getCenter().x, value - getSize().y/2);
}

auto Camera::getGlobalBounds() const -> ns::FloatRect {
    return {getPosition(), getSize()};
}

void Camera::update() {
    if (m_followee) {
        auto& followee_pos = m_followee.value()->getPosition();
        if (m_frames_delay == 0) {
            setCenter(followee_pos.x, followee_pos.y);
        }
        else {
            sf::Vector2f diff = followee_pos - getCenter();
            auto offset = diff/(float)m_frames_delay;
            offset.x = std::abs(offset.x) < 0.25f ? 0.f : offset.x;
            offset.y = std::abs(offset.y) < 0.25f ? 0.f : offset.y;
            move(offset.x, offset.y);
        }
    }
    if (m_limits != ns::IntRect(0, 0, 0, 0)) {
        if (getLeft() < (float)m_limits.left) setLeft((float)m_limits.left);
        if (getTop() < (float)m_limits.top) setTop((float)m_limits.top);
        if (getRight() > (float)m_limits.right()) setRight((float)m_limits.right());
        if (getBottom() > (float)m_limits.bottom()) setBottom((float)m_limits.bottom());
    }
}

void Camera::render(sf::RenderTarget& target) {
    m_render_texture->setView(*this);
    m_render_texture->clear(sf::Color::Transparent);

    m_scene->temporaryLinkCamera(this);
    m_render_texture->draw(*m_scene);

    m_render_texture->display();
    m_sprite.setTexture(m_render_texture->getTexture());
    m_sprite.setScale(
        Settings::getConfig().getViewSize().x*m_base_viewport.width / m_render_texture->getSize().x,
        Settings::getConfig().getViewSize().y*m_base_viewport.height / m_render_texture->getSize().y
    );
    m_sprite.setPosition(m_base_viewport.left*Settings::getConfig().getViewSize().x, m_base_viewport.top*Settings::getConfig().getViewSize().y);
    target.draw(m_sprite, getShader());
}

auto Camera::getSprite() const -> const sf::Sprite& {
    return m_sprite;
}
