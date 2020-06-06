/**
* Created by Modar Nasser on 20/04/2020.
**/

#include "NasNas/core/Camera.hpp"

#include <NasNas/core/App.hpp>

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
    m_base_view = IntRect(0, 0, 1000, 1000);
    m_base_viewport = FloatRect(0, 0, 1, 1);
}

void Camera::reset(int x, int y, int w, int h) {
    reset(FloatRect(x, y, w, h));
}
void Camera::reset(sf::Vector2i position, sf::Vector2i size) {
    reset(FloatRect(position.x, position.y, size.x, size.y));
}
void Camera::reset(const FloatRect &rectangle) {
    m_base_view = IntRect(rectangle.left, rectangle.top, rectangle.width, rectangle.height);
    sf::View::reset(rectangle);
}

void Camera::resetViewport(float x, float y, float w, float h) {
    m_base_viewport = FloatRect(x, y, w, h);
    setViewport(FloatRect(x, y, w, h));
}
void Camera::resetViewport(sf::Vector2f position, sf::Vector2f size) {
    m_base_viewport = FloatRect(position, size);
    setViewport(FloatRect(position, size));
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

void Camera::follow(BaseEntity& entity) {
    m_reference = &entity;
}

auto Camera::getRenderOrder() const -> int {
    return m_render_order;
}

auto Camera::getFramesDelay() const -> unsigned int {
    return m_frames_delay;
}
void Camera::setFramesDelay(unsigned int value) { m_frames_delay = value; }

auto Camera::getPosition() const -> sf::Vector2f {
    return sf::Vector2f(getLeft(), getTop());
}

auto Camera::getLeft() const -> double{
    return getCenter().x - getSize().x/2.0;
}
void Camera::setLeft(float value) {
    setCenter(value + getSize().x/2, getCenter().y);
}

auto Camera::getRight() const -> double {
    return getCenter().x + getSize().x/2.0;
}
void Camera::setRight(float value) {
    setCenter(value - getSize().x/2, getCenter().y);
}

auto Camera::getTop() const -> double {
    return getCenter().y - getSize().y/2.0;
}
void Camera::setTop(float value) {
    setCenter(getCenter().x, value + getSize().y/2);
}

auto Camera::getBottom() const -> double {
    return getCenter().y + getSize().y/2.0;
}
void Camera::setBottom(float value) {
    setCenter(getCenter().x, value - getSize().y/2);
}

auto Camera::getBounds() const -> FloatRect {
    return FloatRect(getPosition(), getSize());
}

void Camera::update() {
    if (m_reference != nullptr) {
        if (m_frames_delay == 0) {
            setCenter(m_reference->getPosition());
        }
        else {
            sf::Vector2f diff = m_reference->getPosition() - getCenter();
            move(diff/(float)m_frames_delay);
        }
        if (getLeft() < 0) setLeft(0);
        if (getTop() < 0) setTop(0);
        if (getRight() > m_scene->getWidth()) setRight((float)m_scene->getWidth());
        if (getBottom() > m_scene->getHeight()) setBottom((float)m_scene->getHeight());
    }
}

