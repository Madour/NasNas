/**
* Created by Modar Nasser on 20/04/2020.
**/


#include <cmath>
#include "NasNas/data/Config.hpp"
#include "NasNas/core/Camera.hpp"

using namespace ns;

Camera::Camera()
: Camera("", 0)
{}

Camera::Camera(const std::string& name, int render_order) {
    m_name = name;
    m_render_order = render_order;
    m_reference = nullptr;
    m_frames_delay = 0;
    m_visible = true;
    m_scene = nullptr;
    m_base_view = ns::IntRect(0, 0, 1000, 1000);
    m_base_viewport = ns::FloatRect(0, 0, 1, 1);

    if (ns::Config::Window::view_width && ns::Config::Window::view_height)
        m_render_texture.create(ns::Config::Window::view_width, ns::Config::Window::view_height);

}

void Camera::setName(const std::string& name) {
    m_name = name;
}

void Camera::reset(int x, int y, int w, int h) {
    reset(ns::FloatRect((float)x, (float)y, (float)w, (float)h));
}
void Camera::reset(sf::Vector2i position, sf::Vector2i size) {
    reset(ns::FloatRect((float)position.x, (float)position.y, (float)size.x, (float)size.y));
}
void Camera::reset(const ns::FloatRect& rectangle) {
    m_base_view = ns::IntRect((int)rectangle.left, (int)rectangle.top, (int)rectangle.width, (int)rectangle.height);
    sf::View::reset(rectangle);
}

void Camera::resetViewport(float x, float y, float w, float h) {
    m_base_viewport = ns::FloatRect(x, y, w, h);
    setViewport(ns::FloatRect(x, y, w, h));
}
void Camera::resetViewport(sf::Vector2f position, sf::Vector2f size) {
    m_base_viewport = ns::FloatRect(position, size);
    setViewport(ns::FloatRect(position, size));
}

auto Camera::getScene() -> Scene& {
    return *m_scene;
}

auto Camera::hasScene() -> bool { return m_scene != nullptr; }
void Camera::setVisible(bool value) { m_visible = value; }
auto Camera::isVisible() const -> bool { return m_visible; }

void Camera::lookAt(Scene* target_scene) {
    m_scene = target_scene;
}

void Camera::follow(Drawable& entity) {
    m_reference = &entity;
}

auto Camera::getRenderOrder() const -> int {
    return m_render_order;
}

auto Camera::getFramesDelay() const -> unsigned int {
    return m_frames_delay;
}
void Camera::setFramesDelay(unsigned int value) { m_frames_delay = value; }

void Camera::setLimitsRectangle(const ns::IntRect& rectangle) {
    m_limits = rectangle;
}

auto Camera::getPosition() const -> sf::Vector2f {
    return sf::Vector2f(getLeft(), getTop());
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
    return ns::FloatRect(getPosition(), getSize());
}

void Camera::update() {
    if (m_reference != nullptr) {
        if (m_frames_delay == 0) {
            setCenter({(float)(round(m_reference->getPosition().x)), (float)(round(m_reference->getPosition().y))});
        }
        else {
            sf::Vector2f diff = m_reference->getPosition() - getCenter();
            auto offset = diff/(float)m_frames_delay;
            move({(float)round(offset.x), (float)round(offset.y)});
        }

        if (m_limits != ns::IntRect(0, 0, 0, 0)) {
            if (getLeft() < (float)m_limits.left) setLeft((float)m_limits.left);
            if (getTop() < (float)m_limits.top) setTop((float)m_limits.top);
            if (getRight() > (float)m_limits.right()) setRight((float)m_limits.right());
            if (getBottom() > (float)m_limits.bottom()) setBottom((float)m_limits.bottom());
        }
    }
}

void Camera::render(sf::RenderTarget& target) {
    m_render_texture.setView(*this);
    m_render_texture.clear(sf::Color::Transparent);

    m_scene->temporaryLinkCamera(this);
    m_render_texture.draw(*m_scene);

    m_render_texture.display();
    m_sprite.setTexture(m_render_texture.getTexture());

    target.draw(m_sprite, getShader());
}
