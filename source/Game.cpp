#include "Game.h"
#include <sstream>

using namespace std;
using namespace sf;

bool exitedMain = false;
bool closed = false;

// Constants
const int maxGhosts = 3;

Game::Game() 
    : window(VideoMode(570, 700), "Pacman"),
      score(0),
      lives(1),
      gameOver(false),
      paused(false) {
    
    // Initialize all ghost pointers to NULL
    for (int i = 0; i < maxGhosts; i++) {
        ghosts[i] = 0;
    }

    maze = new Maze();
    
    // Create pacman
    Vector2f pacmanStartPos = maze->getPlayerStartPosition();
    pacman = new Pacman(pacmanStartPos.x, pacmanStartPos.y);
    
    // Create ghosts
    int ghostCount = maze->getGhostPositionCount();
    for (int i = 0; i < ghostCount && i < maxGhosts; i++) {
        Vector2f ghostPos = maze->getGhostStartPosition(i);
        
        Color ghostColor;
        switch (i) {
            case 0:
                ghostColor = Color::Red;
                break;
            case 1:
                ghostColor = Color(255, 192, 203); // Pink
                break;
            case 2:
                ghostColor = Color::Cyan;
                break;
            default:
                ghostColor = Color::Magenta;
                break;
        }
        
        ghosts[i] = new Ghost(
            ghostPos.x, 
            ghostPos.y, 
            ghostColor
        );
    }
    
    // to set up window
    window.setFramerateLimit(60);
}

Game::~Game() {
    delete maze;
    delete pacman;
    
    for (int i = 0; i < maxGhosts; i++) {
        if (ghosts[i] != NULL) {
            delete ghosts[i];
            ghosts[i] = NULL;
        }
    }
}

void Game::run() {
    // Main game loop
    while (window.isOpen() && !gameOver) {
        float deltaTime = clock.restart().asSeconds();
        
        processEvents();
        
        if (!paused) {
            update(deltaTime);
            checkCollisions();
        }
        
        render();
    }
    
    if (gameOver) {
        gameOverScreen();
    }
}

void Game::processEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        
        if (event.type == Event::KeyPressed) {
            // Handle game control keys
            if (event.key.code == Keyboard::Escape) {
                paused = !paused;
            }
            
            // Handle pacman movement
            if (!paused) {
                pacman->handleInput(event.key.code);
            }
            
            // Restart the game if game over and Enter is pressed
            if (gameOver && event.key.code == Keyboard::Return) {
                resetLevel();
                gameOver = false;
            }
        }
    }
}

void Game::update(float deltaTime) {
    // Update pacman
    pacman->update(deltaTime);
    pacman->move(deltaTime, *maze);
    
    // Update ghosts
    for (int i = 0; i < maxGhosts; i++) {
        if (ghosts[i] != 0) {
            ghosts[i]->update(deltaTime);
            ghosts[i]->move(deltaTime, *pacman, *maze);
        }
    }
    
    // Update dots and energizers
    Dot** dots = maze->getDots();
    int dotCount = maze->getDotCount();
    for (int i = 0; i < dotCount; i++) {
        dots[i]->update(deltaTime);
    }
    
    Energizer** energizers = maze->getEnergizers();
    int energizerCount = maze->getEnergizerCount();
    for (int i = 0; i < energizerCount; i++) {
        energizers[i]->update(deltaTime);
    }
    
    // Check if all dots are eaten
    if (maze->getRemainingDots() == 0) {
        resetLevel();
    }
}

void Game::render() {
    window.clear(Color::Black);
    
    // Draw the maze and its contents
    maze->render(window);
    
    // Draw pacman
    pacman->render(window);
    
    // Draw ghosts
    for (int i = 0; i < maxGhosts; i++) {
        if (ghosts[i] != NULL) {
            ghosts[i]->render(window);
        }
    }
    
    // Draw UI (score and lives) - Moving below the maze
    Font font;
    if (font.loadFromFile("arial.ttf")) {
        // Get the maze height to position text below it
        float mazeHeight = static_cast<float>(maze->getCellSize() * 21); // 21 rows in the maze
        
        // Score text
        Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(Color::Green);
        
        stringstream ss;
        ss << "Score: " << score;
        scoreText.setString(ss.str());
        scoreText.setPosition(10.0f, mazeHeight + 10.0f); // Position below the maze
        
        window.draw(scoreText);
        
        // Lives text
        Text livesText;
        livesText.setFont(font);
        livesText.setCharacterSize(24);
        livesText.setFillColor(Color::Green);
        
        ss.str("");
        ss << "Lives: " << lives;
        livesText.setString(ss.str());
        livesText.setPosition(static_cast<float>(window.getSize().x - 100), mazeHeight + 10.0f); // Position below the maze, right side
        
        window.draw(livesText);
        
        // Paused text
        if (paused) {
            Text pausedText;
            pausedText.setFont(font);
            pausedText.setCharacterSize(36);
            pausedText.setFillColor(Color::Yellow);
            pausedText.setString("PAUSED");
            
            // Center the text
            FloatRect textBounds = pausedText.getLocalBounds();
            pausedText.setPosition(
                (window.getSize().x - textBounds.width) / 2,
                (window.getSize().y - textBounds.height) / 2 - 50
            );
            
            window.draw(pausedText);
        }
    }
    
    window.display();
}

void Game::checkCollisions() {
    // Check collisions with dots
    Dot** dots = maze->getDots();
    int dotCount = maze->getDotCount();
    for (int i = 0; i < dotCount; i++) {
        if (dots[i]->isActive() && pacman->checkCollision(*dots[i])) {
            dots[i]->setActive(false);
            score += dots[i]->getPointValue();
            maze->dotEaten();
        }
    }
    
    // Check collisions with energizers
    Energizer** energizers = maze->getEnergizers();
    int energizerCount = maze->getEnergizerCount();
    for (int i = 0; i < energizerCount; i++) {
        if (energizers[i]->isActive() && pacman->checkCollision(*energizers[i])) {
            energizers[i]->setActive(false);
            score += energizers[i]->getPointValue();
            
            // Power up pacman
            pacman->powerUp();
            
            // Make all ghosts frightened
            for (int j = 0; j < maxGhosts; j++) {
                if (ghosts[j] != NULL) {
                    ghosts[j]->setFrightened(true);
                }
            }
        }
    }
    
    // Check collisions with ghosts
    for (int i = 0; i < maxGhosts; i++) {
        if (ghosts[i] != NULL && pacman->checkCollision(*ghosts[i])) {
            if (pacman->isPowered() && ghosts[i]->isFrightened()) {
                // Eat the ghost
                ghosts[i]->reset(maze->getGhostStartPosition(0).x, maze->getGhostStartPosition(0).y);
                score += 200;
            } else if (!ghosts[i]->isFrightened()) {
                // Pacman dies
                lives--;
                
                if (lives <= 0) {
                    gameOver = true;
                } else {
                    // Reset positions
                    Vector2f pacmanStartPos = maze->getPlayerStartPosition();
                    pacman->reset(pacmanStartPos.x, pacmanStartPos.y);
                    
                    // Reset ghosts
                    for (int j = 0; j < maxGhosts; j++) {
                        if (ghosts[j] != NULL) {
                            ghosts[j]->reset(maze->getGhostStartPosition(j).x, maze->getGhostStartPosition(j).y);
                        }
                    }
                }
            }
        }
    }
}

void Game::resetLevel() {
    // Reset pacman
    Vector2f pacmanStartPos = maze->getPlayerStartPosition();
    pacman->reset(pacmanStartPos.x, pacmanStartPos.y);
    
    // Reset ghosts
    for (int i = 0; i < maxGhosts; i++) {
        if (ghosts[i] != NULL) {
            ghosts[i]->reset(maze->getGhostStartPosition(i).x, maze->getGhostStartPosition(i).y);
        }
    }
    
    // Reset maze (dots and energizers)
    maze->reset();
}

void Game::gameOverScreen() {
    Font font;
    if (font.loadFromFile("arial.ttf")) {
        window.clear(Color::Black);
        
        Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(48);
        gameOverText.setFillColor(Color::Red);
        gameOverText.setString("GAME OVER");
        
        // Center the text
        FloatRect textBounds = gameOverText.getLocalBounds();
        gameOverText.setPosition(
            (window.getSize().x - textBounds.width) / 2,
            (window.getSize().y - textBounds.height) / 2 - 50
        );
        
        window.draw(gameOverText);
        
        // Score text
        Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(Color::Green);
        
        stringstream ss;
        ss << "Final Score: " << score;
        scoreText.setString(ss.str());
        
        // Center the text
        textBounds = scoreText.getLocalBounds();
        scoreText.setPosition(
            (window.getSize().x - textBounds.width) / 2,
            (window.getSize().y - textBounds.height) / 2
        );
        
        window.draw(scoreText);
        
        // Play again text
        Text playAgainText;
        playAgainText.setFont(font);
        playAgainText.setCharacterSize(24);
        playAgainText.setFillColor(Color::White);
        playAgainText.setString("Press Enter to Play Again\n     Press ESC to Exit");
        
        // Center the text
        textBounds = playAgainText.getLocalBounds();
        playAgainText.setPosition(
            (window.getSize().x - textBounds.width) / 2,
            (window.getSize().y - textBounds.height) / 2 + 50
        );
        
        window.draw(playAgainText);
        
        window.display();
        
        bool enterPressed = false;
        bool escPressed = false;
        while (window.isOpen() && !enterPressed && !escPressed) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    closed = true;
                    window.close();
                }
                
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return) {
                    enterPressed = true;
                    gameOver = false;
                    resetLevel();
                    score = 0;
                    lives = 3;
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape){
                    exitedMain = true;
                    escPressed = true;
                }
            }
        }
    }
} 