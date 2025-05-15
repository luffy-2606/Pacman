#include "Energizer.h"

using namespace std;
using namespace sf;

Energizer::Energizer(float x, float y) : Dot(x, y), blinkTimer(0.0f), blinkInterval(0.5f), visible(true) {
    shape.setRadius(6.0f);
    pointValue = 50;
    
    float radius = shape.getRadius();
    this->collisionBox = FloatRect(x, y, radius * 2, radius * 2);
}

void Energizer::update(float deltaTime) {
    // Make the energizer blink
    blinkTimer += deltaTime;
    if (blinkTimer >= blinkInterval) {
        blinkTimer = 0.0f;
        visible = !visible;
        
        if (visible) {
            shape.setFillColor(Color::White);
        } else {
            shape.setFillColor(Color(100, 100, 100)); //greyish
        }
    }
} 