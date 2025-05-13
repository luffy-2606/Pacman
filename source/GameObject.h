#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GameObject {
protected:
    Vector2f position;
    FloatRect collisionBox;
    bool active;

public:
    GameObject(float x, float y);
    virtual ~GameObject() = default;

    virtual void update(float deltaTime) = 0;
    virtual void render(RenderWindow& window) = 0;
    
    Vector2f getPosition() const;
    void setPosition(float x, float y);
    FloatRect getCollisionBox() const;
    bool isActive() const;
    void setActive(bool active);
    
    bool checkCollision(const GameObject& other) const;
}; 