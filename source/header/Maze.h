#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Dot.h"
#include "Energizer.h"

using namespace std;
using namespace sf;

const int maxWidth = 30;
const int maxHeight = 30;
const int maxDots = 500;
const int maxEnergizers = 1;
const int maxGhostPos = 3;
const int maxWalls = 500;

class Maze {
private:
    int grid[maxHeight][maxWidth];  // map itself
    int gridWidth;
    int gridHeight;
    
    RectangleShape walls[maxWalls];
    int wallCount;
    
    Dot* dots[maxDots];
    int dotCount;
    
    Energizer* energizers[maxEnergizers]; 
    int energizerCount;
    
    int cellSize;
    Vector2f playerStartPos;
    
    Vector2f ghostStartPositions[maxGhostPos];
    int ghostPositionCount;
    
    int totalDots;
    int remainingDots;

public:
    Maze();
    ~Maze(); 

    void loadDefaultMaze();
    void render(RenderWindow& window);

    bool isWall(int x, int y) const;
    bool isWall(Vector2f position) const;
    Vector2f getPlayerStartPosition() const;
    
    int getGhostPositionCount() const;
    Vector2f getGhostStartPosition(int index) const;
    int getCellSize() const;

    Dot** getDots();
    int getDotCount() const;
    
    Energizer** getEnergizers();
    int getEnergizerCount() const;

    int getRemainingDots() const;
    void dotEaten();
    void reset();
};