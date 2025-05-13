#pragma once
#include "GameObject.h"

using namespace std;
using namespace sf;

enum class Direction {
    None,
    Up,
    Down,
    Left,
    Right
};

class Pacman : public GameObject {
private:
    CircleShape shape;
    Direction currentDirection;
    Direction nextDirection;
    float speed;
    float animationTimer;
    float animationInterval;
    bool mouthOpen;
    bool powered;
    float powerTimer;
    float powerDuration;

public:
    Pacman(float x, float y);
    ~Pacman() = default;

    void update(float deltaTime) override;
    void render(RenderWindow& window) override;
    
    void handleInput(Keyboard::Key key);
    void move(float deltaTime, const class Maze& maze);
    
    Direction getCurrentDirection() const;
    bool isPowered() const;
    void powerUp();
    void reset(float x, float y);
}; 