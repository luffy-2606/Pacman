#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Pacman.h"

using namespace std;
using namespace sf;

class Ghost;
class Maze;

class WallBounceStrategy {
private:
    int seed;
public:
    WallBounceStrategy();
    Direction getNextDirection(const Ghost& ghost, const Pacman& pacman, const Maze& maze);
    Direction getRandomDirection(const Vector2f& pos, const Maze& maze);
}; 