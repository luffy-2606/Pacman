#include "Maze.h"
#include "Dot.h"
#include "Energizer.h"

using namespace std;
using namespace sf;

Maze::Maze() : cellSize(30), totalDots(0), remainingDots(0), 
              wallCount(0), dotCount(0), energizerCount(0), ghostPositionCount(0),
              gridWidth(0), gridHeight(0) {
    loadDefaultMaze();
}

Maze::~Maze() {
    // Clean up dots
    for (int i = 0; i < dotCount; i++) {
        delete dots[i];
    }
    
    // Clean up energizers
    for (int i = 0; i < energizerCount; i++) {
        delete energizers[i];
    }
}

void Maze::loadDefaultMaze() {
    // Clear existing data
    wallCount = 0;
    
    // Delete existing objects before clearing arrays
    for (int i = 0; i < dotCount; i++) {
        delete dots[i];
    }
    dotCount = 0;
    
    for (int i = 0; i < energizerCount; i++) {
        delete energizers[i];
    }
    energizerCount = 0;
    
    ghostPositionCount = 0;
    
    // Default maze layout
    // 0 = empty space, 1 = wall, 2 = dot, 3 = energizer, 4 = pacman start, 5 = ghost start
    int defaultMaze[21][19] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 2, 1, 1, 1, 0, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1},
        {0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0},
        {1, 1, 1, 1, 2, 1, 0, 1, 1, 5, 1, 1, 0, 1, 2, 1, 1, 1, 1},
        {0, 0, 0, 0, 2, 0, 0, 1, 5, 5, 5, 1, 0, 0, 2, 0, 0, 0, 0},
        {1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1},
        {0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0},
        {1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
        {1, 3, 2, 1, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 1, 2, 2, 1},
        {1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1},
        {1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    
    gridHeight = 21;
    gridWidth = 19;
    
    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            grid[y][x] = defaultMaze[y][x];
        }
    }
    
    // Process the maze
    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            float posX = static_cast<float>(x * cellSize);
            float posY = static_cast<float>(y * cellSize);
            
            switch (grid[y][x]) {
                case 1: // Wall
                {
                    if (wallCount < maxWalls) {
                        RectangleShape wall(Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
                        wall.setPosition(posX, posY);
                        wall.setFillColor(Color::Blue);
                        walls[wallCount++] = wall;
                    }
                    break;
                }
                case 2: // Dot
                {
                    if (dotCount < maxDots) {
                        Dot* dot = new Dot(posX + static_cast<float>(cellSize) / 2.0f, posY + static_cast<float>(cellSize) / 2.0f);
                        dots[dotCount++] = dot;
                        totalDots++;
                    }
                    break;
                }
                case 3: // Energizer
                {
                    if (energizerCount < maxEnergizers) {
                        Energizer* energizer = new Energizer(posX + static_cast<float>(cellSize) / 2.0f, posY + static_cast<float>(cellSize) / 2.0f);
                        energizers[energizerCount++] = energizer;
                    }
                    break;
                }
                case 4: // Pacman start
                {
                    playerStartPos = Vector2f(posX + static_cast<float>(cellSize) / 2.0f, posY + static_cast<float>(cellSize) / 2.0f);
                    break;
                }
                case 5: // Ghost start
                {
                    if (ghostPositionCount < maxGhostPos) {
                        ghostStartPositions[ghostPositionCount++] = Vector2f(posX + static_cast<float>(cellSize) / 2.0f, posY + static_cast<float>(cellSize) / 2.0f);
                    }
                    break;
                }
            }
        }
    }
    
    remainingDots = totalDots;
}

void Maze::render(RenderWindow& window) {
    // Draw walls
    for (int i = 0; i < wallCount; i++) {
        window.draw(walls[i]);
    }
    
    // Draw dots
    for (int i = 0; i < dotCount; i++) {
        if (dots[i]->isActive()) {
            dots[i]->render(window);
        }
    }
    
    // Draw energizers
    for (int i = 0; i < energizerCount; i++) {
        if (energizers[i]->isActive()) {
            energizers[i]->render(window);
        }
    }
}

bool Maze::isWall(int x, int y) const {
    // Convert pixel coordinates to grid coordinates
    int gridX = x / cellSize;
    int gridY = y / cellSize;
    
    // Check if the coordinates are within bounds
    if (gridX < 0 || gridX >= gridWidth || gridY < 0 || gridY >= gridHeight) {
        return true; // Out of bounds is considered a wall
    }
    
    return grid[gridY][gridX] == 1;
}

bool Maze::isWall(Vector2f position) const {
    return isWall(static_cast<int>(position.x), static_cast<int>(position.y));
}

Vector2f Maze::getPlayerStartPosition() const {
    return playerStartPos;
}

int Maze::getGhostPositionCount() const {
    return ghostPositionCount;
}

Vector2f Maze::getGhostStartPosition(int index) const {
    if (index >= 0 && index < ghostPositionCount) {
        return ghostStartPositions[index];
    }
    // Return default position if index is out of bounds
    return Vector2f(0, 0);
}

int Maze::getCellSize() const {
    return cellSize;
}

Dot** Maze::getDots() {
    return dots;
}

int Maze::getDotCount() const {
    return dotCount;
}

Energizer** Maze::getEnergizers() {
    return energizers;
}

int Maze::getEnergizerCount() const {
    return energizerCount;
}

int Maze::getRemainingDots() const {
    return remainingDots;
}

void Maze::dotEaten() {
    if (remainingDots > 0) {
        remainingDots--;
    }
}

void Maze::reset() {
    // Reset all dots
    for (int i = 0; i < dotCount; i++) {
        dots[i]->setActive(true);
    }
    
    // Reset all energizers
    for (int i = 0; i < energizerCount; i++) {
        energizers[i]->setActive(true);
    }
    
    remainingDots = totalDots;
} 