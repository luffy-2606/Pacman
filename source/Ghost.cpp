#include "Ghost.h"
#include "Pacman.h"
#include "Maze.h"
#include <cmath>
#include <ctime>

using namespace std;
using namespace sf;

Ghost::Ghost(float x, float y, Color color)
    : GameObject(x, y), 
      originalColor(color), 
      speed(80.0f), 
      currentDirection(Direction::None),
      strategy(strategy),
      frightened(false),
      frightenedTimer(0.0f),
      frightenedDuration(10.0f) {
    
    srand(static_cast<unsigned int>(time(nullptr)));  //so that ghost movements are random every time program runs
    
    shape.setRadius(10.0f);
    shape.setFillColor(color);
    shape.setPosition(x, y);
    
    float radius = shape.getRadius();
    this->collisionBox = FloatRect(x, y, radius * 1.8f, radius * 1.8f);
}

void Ghost::update(float deltaTime) {
    if (frightened == true) {
        frightenedTimer += deltaTime;
        if (frightenedTimer >= frightenedDuration) {
            frightened = false;
            shape.setFillColor(originalColor);
        }
    }
    
    shape.setPosition(this->position);                                      //update ghost position
    this->collisionBox.left = this->position.x - shape.getRadius() * 0.9f;  //update ghost-collision-box position
    this->collisionBox.top = this->position.y - shape.getRadius() * 0.9f;   //update ghost-collision-box position
}

void Ghost::render(RenderWindow& window) {
    float radius = shape.getRadius();
    
    // ----Draw ghost body w/eyes and shii----

    //Head
    CircleShape ghostHead(radius);
    if (frightened) 
        ghostHead.setFillColor(Color::Blue);
    else
        ghostHead.setFillColor(originalColor);
    ghostHead.setPosition(this->position.x - radius, this->position.y - radius);

    //Body
    RectangleShape ghostBody(Vector2f(radius * 2.0f, radius * 1.2f));
    if (frightened)
        ghostBody.setFillColor(Color::Blue);
    else
        ghostBody.setFillColor(originalColor);
    ghostBody.setPosition(this->position.x - radius, this->position.y);
    
    //Bottom (wavy/zig-zag pattern)
    ConvexShape ghostBottom;
    ghostBottom.setPointCount(5);
    if (frightened)
        ghostBottom.setFillColor(Color::Blue);
    else
        ghostBottom.setFillColor(originalColor);
    ghostBottom.setPoint(0, Vector2f(0, 0));
    ghostBottom.setPoint(1, Vector2f(radius / 2.0f, radius / 2.0f));
    ghostBottom.setPoint(2, Vector2f(radius, 0));
    ghostBottom.setPoint(3, Vector2f(radius * 1.5f, radius / 2.0f));
    ghostBottom.setPoint(4, Vector2f(radius * 2.0f, 0));
    
    ghostBottom.setPosition(this->position.x - radius, this->position.y + radius * 1.2f);
    
    window.draw(ghostHead);
    window.draw(ghostBody);
    window.draw(ghostBottom);
    
    //--Eyes--
    if (!frightened) {
        //eye-balls :)
        CircleShape leftEye(3.0f);
        CircleShape rightEye(3.0f);
        leftEye.setFillColor(Color::White);
        rightEye.setFillColor(Color::White);
        
        // Position them eyes based on direction
        Vector2f eyePos(0.0f, -2.0f);
        switch (currentDirection) {
            case Direction::Up:
                eyePos = Vector2f(0.0f, -2.0f);
                break;
            case Direction::Down:
                eyePos = Vector2f(0.0f, 2.0f);
                break;
            case Direction::Left:
                eyePos = Vector2f(-4.0f, -2.0f);
                break;
            case Direction::Right:
                eyePos = Vector2f(4.0f, -2.0f);
                break;
            default:
                break;
        }

        leftEye.setPosition(this->position.x - 5.0f + eyePos.x, this->position.y - 3.0f + eyePos.y);
        rightEye.setPosition(this->position.x + 5.0f + eyePos.x, this->position.y - 3.0f + eyePos.y);

        // pupils
        CircleShape leftPupil(1.5f);
        CircleShape rightPupil(1.5f);
        leftPupil.setFillColor(Color::Black);
        rightPupil.setFillColor(Color::Black);
        
        float pupilPosX = 0.0f;
        float pupilPosY = 0.0f;
        
        switch (currentDirection) {
            case Direction::Up:
                pupilPosY = -1.0f;
                break;
            case Direction::Down:
                pupilPosY = 1.0f;
                break;
            case Direction::Left:
                pupilPosX = -1.0f;
                break;
            case Direction::Right:
                pupilPosX = 1.0f;
                break;
            default:
                break;
        }
        
        leftPupil.setPosition(leftEye.getPosition().x + 1.0f + pupilPosX, leftEye.getPosition().y + 1.0f + pupilPosY);
        rightPupil.setPosition(rightEye.getPosition().x + 1.0f + pupilPosX, rightEye.getPosition().y + 1.0f + pupilPosY);
        
        window.draw(leftEye);
        window.draw(rightEye);
        window.draw(leftPupil);
        window.draw(rightPupil);
    } 
    else {
        //--Frightened-- 
        
        // Face/Mouth:
        RectangleShape mouth1(Vector2f(8.0f, 2.0f));
        mouth1.setFillColor(Color::White);
        mouth1.setPosition(this->position.x - 4.0f, this->position.y + 3.0f);
        RectangleShape mouth2(Vector2f(2.0f, 2.0f));
        RectangleShape mouth3(Vector2f(2.0f, 2.0f));
        mouth2.setFillColor(Color::White);
        mouth3.setFillColor(Color::White);
        mouth2.setPosition(this->position.x - 4.0f, this->position.y + 1.0f);
        mouth3.setPosition(this->position.x + 2.0f, this->position.y + 1.0f);

        window.draw(mouth1);
        window.draw(mouth2);
        window.draw(mouth3);
    }
}

void Ghost::move(float deltaTime, const Pacman& pacman, const Maze& maze) {
    Direction nextDirection;
    
    bool forceMovementOut = false;
    Vector2f ghostPos = this->position;
    
    int gridX = static_cast<int>(ghostPos.x / maze.getCellSize());
    int gridY = static_cast<int>(ghostPos.y / maze.getCellSize());
    
    bool inGhostBox = (gridX >= 8 && gridX <= 11 && gridY >= 8 && gridY <= 10);
    
    if (inGhostBox) {
        // Force movement upward to get out of ghost box
        nextDirection = Direction::Up;
        forceMovementOut = true;
        
        // Increase speed temporarily to ensure ghosts exit the box
        float exitSpeed = speed * 1.5f;
        float moveStep = exitSpeed * deltaTime;
        this->position.y -= moveStep;
        
        // If close to the top of the box, force a jump out
        if (gridY == 8 && this->position.y <= (8 * maze.getCellSize() + maze.getCellSize() * 0.5f)) {
            this->position.y = 8 * maze.getCellSize() - maze.getCellSize() * 0.5f;
            currentDirection = Direction::Left; 
            return;
        }
        return; 
    } 
    else {
        WallBounceStrategy wallBounce;
        nextDirection = wallBounce.getNextDirection(*this, pacman, maze);
    } 
    
    currentDirection = nextDirection;
    
    
    Vector2f newPos = this->position;
    float moveStep = speed * deltaTime;
    float radius = 10.0f; 
    
    float mazeWidth = static_cast<float>(maze.getCellSize() * 19); 
    
    //To go pass through the tunnels
    bool inTunnel = (gridY == 7 || gridY == 9 || gridY == 11);
    
    switch (currentDirection) {
        case Direction::Up:
            newPos.y -= moveStep;
            break;
        case Direction::Down:
            newPos.y += moveStep;
            break;
        case Direction::Left:
            newPos.x -= moveStep;
            // left -> right
            if (inTunnel && newPos.x < 0) {
                newPos.x = mazeWidth;
            }
            break;
        case Direction::Right:
            newPos.x += moveStep;
            // right-> left
            if (inTunnel && newPos.x > mazeWidth) {
                newPos.x = 0;
            }
            break;
        default:
            //pivk a random direction
            Direction randomDirs[4] = {Direction::Up, Direction::Down, Direction::Left, Direction::Right};
            int randomIndex = rand() % 4;
            currentDirection = randomDirs[randomIndex];
            break;
    }
    
    // --------Wall collision--------
    bool collision = false;
    
    //checks if any poiny of ghost is touching the wallsssss
    if (!forceMovementOut) {
        collision = maze.isWall(static_cast<int>(newPos.x), static_cast<int>(newPos.y)) ||              //center point
                    maze.isWall(static_cast<int>(newPos.x - radius), static_cast<int>(newPos.y)) ||     //left point
                    maze.isWall(static_cast<int>(newPos.x + radius), static_cast<int>(newPos.y)) ||     //right point
                    maze.isWall(static_cast<int>(newPos.x), static_cast<int>(newPos.y - radius)) ||     //top point
                    maze.isWall(static_cast<int>(newPos.x), static_cast<int>(newPos.y + radius));       //bottom point
    }
    
    if (!collision) {
        this->position = newPos;
    } else {
        currentDirection = Direction::None;
    }
}

Direction Ghost::getCurrentDirection() const {
    return currentDirection;
}

void Ghost::setFrightened(bool frightenedState) {
    frightened = frightenedState;
    
    if (frightened) {
        frightenedTimer = 0.0f;
        shape.setFillColor(Color::Blue);
    } else {
        shape.setFillColor(originalColor);
    }
}

bool Ghost::isFrightened() const {
    return frightened;
}

void Ghost::reset(float x, float y) {
    this->position = Vector2f(x, y);
    currentDirection = Direction::None;
    frightened = false;
    shape.setFillColor(originalColor);
    
    // Reset the collision box
    float radius = shape.getRadius();
    this->collisionBox = FloatRect(x, y, radius * 1.8f, radius * 1.8f);
} 