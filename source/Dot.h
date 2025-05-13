#pragma once
#include "GameObject.h"

using namespace std;
using namespace sf;

class Dot : public GameObject {
protected:
    CircleShape shape;
    int pointValue;

public:
    Dot(float x, float y);
    virtual ~Dot() = default;

    void update(float deltaTime) override;
    void render(RenderWindow& window) override;
    
    int getPointValue() const;
}; 