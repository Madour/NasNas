/**
* Created by Modar Nasser on 20/04/2020.
**/

#include "NasNas/core/Camera.hpp"

#include <NasNas/core/App.hpp>

using namespace ns;

Camera::Camera() = default;

Camera::Camera(const std::string& name, int render_order) {
    this->name = name;
    this->render_order = render_order;
    this->reference = nullptr;
    this->frames_delay = 0;
    this->visible = true;
    this->scene = nullptr;
    this->base_view = IntRect(0, 0, 1000, 1000);
    this->base_viewport = FloatRect(0, 0, 1, 1);
}

void Camera::reset(int x, int y, int w, int h) {
    this->base_view = IntRect(x, y, w, h);
    this->reset(FloatRect(x, y, w, h));
}
void Camera::reset(sf::Vector2i position, sf::Vector2i size) {
    this->base_view = IntRect(position, size);
    this->reset(FloatRect(position.x, position.y, size.x, size.y));
}

void Camera::resetViewport(float x, float y, float w, float h) {
    this->base_viewport = FloatRect(x, y, w, h);
    this->setViewport(FloatRect(x, y, w, h));
}
void Camera::resetViewport(sf::Vector2f position, sf::Vector2f size) {
    this->base_viewport = FloatRect(position, size);
    this->setViewport(FloatRect(position, size));
}

auto Camera::getScene() -> Scene& {
    return *this->scene;
}

auto Camera::hasScene() -> bool { return this->scene != nullptr; }
void Camera::setVisible(bool value) { this->visible = value; }
auto Camera::isVisible() const -> bool { return this->visible; }

void Camera::reset(const FloatRect &rectangle) {
    sf::View::reset(rectangle);
}

void Camera::lookAt(Scene* target_scene) {
    this->scene = target_scene;
}

void Camera::follow(BaseEntity& entity) {
    this->reference = &entity;
}

auto Camera::getRenderOrder() const -> int {
    return this->render_order;
}

auto Camera::getFramesDelay() const -> unsigned int {
    return this->frames_delay;
}
void Camera::setFramesDelay(unsigned int value) { this->frames_delay = value; }

auto Camera::getPosition() const -> sf::Vector2f {
    return sf::Vector2f(this->getLeft(), this->getTop());
}

/*auto Camera::getSize() const -> sf::Vector2f {
    return sf::Vector2f(this->base_view.width, this->base_view.height);
}*/

auto Camera::getLeft() const -> double{
    return this->getCenter().x - this->getSize().x/2.0;
}
void Camera::setLeft(float value) {
    this->setCenter(value + this->getSize().x/2, this->getCenter().y);
}

auto Camera::getRight() const -> double {
    return this->getCenter().x + this->getSize().x/2.0;
}
void Camera::setRight(float value) {
    this->setCenter(value - this->getSize().x/2, this->getCenter().y);
}

auto Camera::getTop() const -> double {
    return this->getCenter().y - this->getSize().y/2.0;
}
void Camera::setTop(float value) {
    this->setCenter(this->getCenter().x, value + this->getSize().y/2);
}

auto Camera::getBottom() const -> double {
    return this->getCenter().y + this->getSize().y/2.0;
}
void Camera::setBottom(float value) {
    this->setCenter(this->getCenter().x, value - this->getSize().y/2);
}

auto Camera::getBounds() const -> FloatRect {
    return FloatRect(this->getPosition(), this->getSize());
}


void Camera::update() {
    if (this->reference != nullptr) {
        if (this->frames_delay == 0) {
            this->setCenter(this->reference->getPosition());
        }
        else {
            sf::Vector2f diff = this->reference->getPosition() - this->getCenter();
            this->move(diff/(float)this->frames_delay);
        }
        if (this->getLeft() < 0) this->setLeft(0);
        if (this->getTop() < 0) this->setTop(0);
        if (this->getRight() > this->scene->getWidth()) this->setRight((float)this->scene->getWidth());
        if (this->getBottom() > this->scene->getHeight()) this->setBottom((float)this->scene->getHeight());
    }
}

