#include "Pacman.h"
#include "Maze.h"

using namespace std;
using namespace sf;

Pacman::Pacman(float x, float y) 
    : GameObject(x, y), 
      currentDirection(Direction::None), 
      nextDirection(Direction::None),
      speed(100.0f),
      animationTimer(0.0f),
      animationInterval(0.2f),
      mouthOpen(true),
      powered(false),
      powerTimer(0.0f),
      powerDuration(10.0f) {
    
    shape.setRadius(10.0f);
    shape.setFillColor(Color::Yellow);
    shape.setPosition(x, y);
    
    // Set the collision box
    float radius = shape.getRadius();
    collisionBox = FloatRect(x, y, radius * 1.8f, radius * 1.8f);
}

void Pacman::update(float deltaTime) {
    // Update animation
    animationTimer += deltaTime;
    if (animationTimer >= animationInterval) {
        animationTimer = 0.0f;
        mouthOpen = !mouthOpen;
    }

    // Update energized state type shii
    if (powered) {
        powerTimer += deltaTime;
        if (powerTimer >= powerDuration) {
            powered = false;
            powerTimer = 0.0f;
        }
    }

    // Update position based on thw collision box
    shape.setPosition(position);
    collisionBox.left = position.x - shape.getRadius() * 0.9f;
    collisionBox.top = position.y - shape.getRadius() * 0.9f;
}

void Pacman::render(RenderWindow& window) {
    // Create a pacman shape with a "mouth"
    CircleShape pacman(shape.getRadius());
    pacman.setFillColor(shape.getFillColor());
    pacman.setPosition(position.x - shape.getRadius(), position.y - shape.getRadius());
    
    // Calculate the mouth angle based on direction
    // So this is basically the pacman "rotating itself" towards the moving direction
    float angle = 0.0f;
    switch (currentDirection) {
        case Direction::Right: angle = 0.0f; break;
        case Direction::Down: angle = 90.0f; break;
        case Direction::Left: angle = 180.0f; break;
        case Direction::Up: angle = 270.0f; break;
        default: angle = 0.0f; break;
    }
    
    if (mouthOpen) {
        // Draw pacman with a mouth using a pie shape
        float mouthSize = 60.0f; // Larger mouth angle
        
        CircleShape newPacman(shape.getRadius(), 30);  // 30 is something for smooth surface idk
        newPacman.setFillColor(Color::Yellow);
        newPacman.setPosition(position.x - shape.getRadius(), position.y - shape.getRadius());
        
        // triangle for the mouth
        ConvexShape mouth;
        mouth.setPointCount(3);
        
        // Center point
        mouth.setPoint(0, Vector2f(shape.getRadius(), shape.getRadius()));
        
        // Mouth edges (converting to radian as well)
        float rad1 = (angle - mouthSize/2) * 3.14159f / 180.0f;
        float rad2 = (angle + mouthSize/2) * 3.14159f / 180.0f;
        
        mouth.setPoint(1, Vector2f(shape.getRadius() + cos(rad1) * shape.getRadius() * 1.2f, shape.getRadius() + sin(rad1) * shape.getRadius() * 1.2f));
        
        mouth.setPoint(2, Vector2f(shape.getRadius() + cos(rad2) * shape.getRadius() * 1.2f, shape.getRadius() + sin(rad2) * shape.getRadius() * 1.2f));
        
        mouth.setFillColor(Color::Black);
        mouth.setPosition(position.x - shape.getRadius(), position.y - shape.getRadius());
        
        window.draw(newPacman);
        window.draw(mouth);
    } else {
        CircleShape betterPacman(shape.getRadius(), 30); 
        betterPacman.setFillColor(Color::Yellow);
        betterPacman.setPosition(position.x - shape.getRadius(), position.y - shape.getRadius());
        window.draw(betterPacman);
    }
}

void Pacman::handleInput(Keyboard::Key key) {
    switch (key) {
        case Keyboard::I:
            nextDirection = Direction::Up;
            break;
        case Keyboard::K:
            nextDirection = Direction::Down;
            break;
        case Keyboard::J:
            nextDirection = Direction::Left;
            break;
        case Keyboard::L:
            nextDirection = Direction::Right;
            break;
        default:
            break;
    }
}

void Pacman::move(float deltaTime, const Maze& maze) {
    // Try to change direction if requested
    if (nextDirection != currentDirection) {
        Vector2f testPos = position;
        float radius = shape.getRadius();
        bool canChangeDirection = false;
        
        switch (nextDirection) {
            case Direction::Up:
                testPos.y -= radius;
                canChangeDirection = !maze.isWall(static_cast<int>(testPos.x - radius), static_cast<int>(testPos.y)) && 
                                    !maze.isWall(static_cast<int>(testPos.x + radius), static_cast<int>(testPos.y));
                break;
            case Direction::Down:
                testPos.y += radius;
                canChangeDirection = !maze.isWall(static_cast<int>(testPos.x - radius), static_cast<int>(testPos.y)) && 
                                    !maze.isWall(static_cast<int>(testPos.x + radius), static_cast<int>(testPos.y));
                break;
            case Direction::Left:
                testPos.x -= radius;
                canChangeDirection = !maze.isWall(static_cast<int>(testPos.x), static_cast<int>(testPos.y - radius)) && 
                                    !maze.isWall(static_cast<int>(testPos.x), static_cast<int>(testPos.y + radius));
                break;
            case Direction::Right:
                testPos.x += radius;
                canChangeDirection = !maze.isWall(static_cast<int>(testPos.x), static_cast<int>(testPos.y - radius)) && 
                                    !maze.isWall(static_cast<int>(testPos.x), static_cast<int>(testPos.y + radius));
                break;
            default:
                break;
        }
        
        if (canChangeDirection) {
            currentDirection = nextDirection;
        }
    }
    
    // Move in the current direction if possible
    Vector2f newPos = position;
    float radius = shape.getRadius();
    bool canMove = true;
    
    float mazeWidth = static_cast<float>(maze.getCellSize() * 19);
    float moveAmount = speed * deltaTime;
    
    // Get grid row and column for current position
    int gridY = static_cast<int>(position.y / maze.getCellSize());
    int gridX = static_cast<int>(position.x / maze.getCellSize());
    
    // for teleporting through tunnel
    bool inTunnel = gridY == 9;
    
    switch (currentDirection) {
        case Direction::Up:
            newPos.y -= moveAmount;
            canMove = !maze.isWall(static_cast<int>(newPos.x - radius), static_cast<int>(newPos.y - radius)) && 
                      !maze.isWall(static_cast<int>(newPos.x + radius), static_cast<int>(newPos.y - radius));
            break;
        case Direction::Down:
            newPos.y += moveAmount;
            canMove = !maze.isWall(static_cast<int>(newPos.x - radius), static_cast<int>(newPos.y + radius)) && 
                      !maze.isWall(static_cast<int>(newPos.x + radius), static_cast<int>(newPos.y + radius));
            break;
        case Direction::Left:
            newPos.x -= moveAmount;
            if (inTunnel && newPos.x < 0) {
                // left -> right
                newPos.x = mazeWidth;
                canMove = true;
            } else {
                canMove = !maze.isWall(static_cast<int>(newPos.x - radius), static_cast<int>(newPos.y - radius)) && 
                          !maze.isWall(static_cast<int>(newPos.x - radius), static_cast<int>(newPos.y + radius));
            }
            break;
        case Direction::Right:
            newPos.x += moveAmount;
            if (inTunnel && newPos.x >= mazeWidth - 10) {
                // right -> left
                newPos.x = 0;
                canMove = true;
            } else {
                canMove = !maze.isWall(static_cast<int>(newPos.x + radius), static_cast<int>(newPos.y - radius)) && 
                          !maze.isWall(static_cast<int>(newPos.x + radius), static_cast<int>(newPos.y + radius));
            }
            break;
        default:
            break;
    }
    
    if (canMove) {
        position = newPos;
    }
}

Direction Pacman::getCurrentDirection() const {
    return currentDirection;
}

bool Pacman::isPowered() const {
    return powered;
}

void Pacman::powerUp() {
    powered = true;
    powerTimer = 0.0f;
}

void Pacman::reset(float x, float y) {
    position = Vector2f(x, y);
    currentDirection = Direction::None;
    nextDirection = Direction::None;
    powered = false;
    powerTimer = 0.0f;
    
    // Reset the collision box
    float radius = shape.getRadius();
    collisionBox = FloatRect(x, y, radius * 1.8f, radius * 1.8f);
} 