#pragma once
#include "Dot.h"

using namespace std;
using namespace sf;

class Energizer : public Dot {
private:
    float blinkTimer;
    float blinkInterval;
    bool visible;

public:
    Energizer(float x, float y);
    ~Energizer() = default;

    void update(float deltaTime) override;
}; 