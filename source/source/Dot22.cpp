#include "Dot.h"

using namespace std;
using namespace sf;

Dot::Dot(float x, float y) : GameObject(x, y), pointValue(10) {
    shape.setRadius(2.0f);
    shape.setFillColor(Color::White);
    shape.setPosition(x, y);
    
    // Set the collision box
    float radius = shape.getRadius();
    this->collisionBox = FloatRect(x, y, radius * 2, radius * 2);
}

void Dot::update(float deltaTime) {
    // not required
}

void Dot::render(RenderWindow& window) {
    if (this->active) {
        window.draw(shape);
    }
}

int Dot::getPointValue() const {
    return pointValue;
} 
