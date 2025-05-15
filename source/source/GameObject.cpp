#include "GameObject.h"

using namespace std;
using namespace sf;

GameObject::GameObject(float x, float y) : position(x, y), active(true) {
    collisionBox = FloatRect(x, y, 0, 0);
}

Vector2f GameObject::getPosition() const {
    return position;
}

void GameObject::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

FloatRect GameObject::getCollisionBox() const {
    return collisionBox;
}

bool GameObject::isActive() const {
    return active;
}

void GameObject::setActive(bool active) {
    this->active = active;
}

bool GameObject::checkCollision(const GameObject& other) const {
    return collisionBox.intersects(other.getCollisionBox());
} 