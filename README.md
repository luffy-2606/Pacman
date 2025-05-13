PAC-MAN GAME

## Core Game Files
- main.cpp: 
	- Entry point of the application that initializes and runs the game.
	- Nothing else here tbh
- Game.h/Game.cpp: 
	- Main game class that coordinates most of the game together, handles game loop and collisions.
	- Initilaizes Lives and Score
	- Initializes the Window
- GameObject.h/GameObject.cpp: 
	- Base class for all game objects with common properties like position and collision detection.

## Game Elements
- Pacman.h/Pacman.cpp: 
	- The player-controlled character with movement, power-up handling, and animation.
- Ghost.h/Ghost.cpp: 
	- Enemy characters that chase the player using various movement strategies.
- GhostStrategy.h/GhostStrategy.cpp: 
	- Contains the WallBounceStrategy class for ghost movement based on wall collisions.
- Maze.h/Maze.cpp: 
	- Manages the game level layout, walls, tunnels, and collectible items.
- Dot.h/Dot.cpp: 
	- Small collectible items that Pac-Man eats for points.
- Energizer.h/Energizer.cpp: 
	- Special collectibles that temporarily allow Pac-Man to eat ghosts.

## GAME FEATURES
- Classic Pac-Man gameplay with dots, one energizer, and 3 ghosts
- Ghost AI using the WallBounceStrategy (it randomly changes direction based on direction)
- Wall collision detection and tunnel warping
- Score tracking and lives tracking
- Game over screen with replay option & exit option

## CONTROLS
- I, J, K, L: Move Pac-Man
- Escape: Pause/unpause the game
- Enter: Restart game after Game Over
- Escape: Exit after Game Over