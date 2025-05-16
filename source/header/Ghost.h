#pragma once
#include "GameObject.h"
#include "GhostStrategy.h"

using namespace std;
using namespace sf;

//to avoid "circular dependency" (idk what that is)
class Pacman;
class Maze;

class Ghost : public GameObject {
private:
    CircleShape shape;
    Color originalColor;
    float speed;
    Direction currentDirection;
    WallBounceStrategy strategy;
    bool frightened;
    float frightenedTimer;
    float frightenedDuration;

public:
    Ghost(float x, float y, Color color);
    ~Ghost() = default;  

    void update(float deltaTime) override;
    void render(RenderWindow& window) override;
    
    void move(float deltaTime, const Pacman& pacman, const Maze& maze);
    Direction getCurrentDirection() const;
    void setFrightened(bool frightenedState);
    bool isFrightened() const;
    void reset(float x, float y);
}; 