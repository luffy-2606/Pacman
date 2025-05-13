#pragma once
#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;
using namespace sf;

const int MAX_GHOSTS = 3;

extern bool exitedMain;
extern bool closed;

class Game {
private:
    RenderWindow window;
    Clock clock;   //searched this up on internet, this is part of SFML
    Maze* maze;
    Pacman* pacman;
    Ghost* ghosts[MAX_GHOSTS];
    int score;
    int lives;
    bool gameOver;
    bool paused;

public:
    Game();
    ~Game();  

    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void checkCollisions();
    void resetLevel();
    void gameOverScreen();
}; 