#include "GhostStrategy.h"
#include "Ghost.h"
#include "Maze.h"
#include <cmath>
#include <ctime>

using namespace std;
using namespace sf;

WallBounceStrategy::WallBounceStrategy() {
    seed = static_cast<int>(time(nullptr));
}

Direction WallBounceStrategy::getNextDirection(const Ghost& ghost, const Pacman& pacman, const Maze& maze) {

    Vector2f ghostPos = ghost.getPosition();
    Direction currentDirection = ghost.getCurrentDirection();
    
    // If no current direction:
    if (currentDirection == Direction::None) {
        return getRandomDirection(ghostPos, maze);
    }
    
    // Check if we hit a wall in our current direction
    Vector2f nextPos = ghostPos;
    float testDistance = 10.0f;
    
    switch (currentDirection) {
        case Direction::Up: nextPos.y -= testDistance; break;
        case Direction::Down: nextPos.y += testDistance; break;
        case Direction::Left: nextPos.x -= testDistance; break;
        case Direction::Right: nextPos.x += testDistance; break;
        default: break;
    }
    
    // If we hit a wall, choose a new random direction
    if (maze.isWall(nextPos)) {
        return getRandomDirection(ghostPos, maze);
    }
    
    // Continue in the same direction if no wall was hit
    return currentDirection;
}

Direction WallBounceStrategy::getRandomDirection(const Vector2f& pos, const Maze& maze) {
    // Store valid directions
    const int MAX_DIRECTIONS = 4;
    Direction possibleDirections[MAX_DIRECTIONS];
    int directionCount = 0;
    
    // Check which directions are not walls
    Vector2f testPos;
    float testDistance = 5.0f;
    
    // Test Up
    testPos = pos;
    testPos.y -= testDistance;
    if (!maze.isWall(testPos)) {
        possibleDirections[directionCount++] = Direction::Up;
    }
    
    // Test Down
    testPos = pos;
    testPos.y += testDistance;
    if (!maze.isWall(testPos)) {
        possibleDirections[directionCount++] = Direction::Down;
    }
    
    // Test Left
    testPos = pos;
    testPos.x -= testDistance;
    if (!maze.isWall(testPos)) {
        possibleDirections[directionCount++] = Direction::Left;
    }
    
    // Test Right
    testPos = pos;
    testPos.x += testDistance;
    if (!maze.isWall(testPos)) {
        possibleDirections[directionCount++] = Direction::Right;
    }
    
    // If we have valid directions, choose one using simple randomization
    if (directionCount > 0) {
        // Use a simple method for randomization
        seed = (seed * 1103515245 + 12345) % 2147483647;
        int index = seed % directionCount;
        return possibleDirections[index];
    }
    
    // If no valid directions, stay still
    return Direction::None;
} 