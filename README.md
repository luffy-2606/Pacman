### PAC-MAN GAME

## Core Game Files
- main.cpp: 
	- Entry point of the application that initializes and runs the game.
	- Nothing else here tbh
- Game.h/Game.cpp: 
	- Main game class that coordinates most of the game together, handles game loop and collisions.
	- Initilaizes Lives and Score
	- Initializes the Window
- GameObject.h/GameObject.cpp: 
	- Base class for all game objects.
	- Manages position
	- Collision detection (dots & pacman, energizer & pacman, ghosts & pacman)

## Game Elements
- Pacman.h/Pacman.cpp: 
	- Mr Pacman himslef 
	- User Input is handled here (I, J, K, L)
	- Pacman power-up (energizer)
	- Pacman animation
	- [Also has has an enumerated class Direction]
- Ghost.h/Ghost.cpp: 
	- Ghost Animation/Render
	- Ghost strategy implementation
	- Ghost frightened mide implementation
- GhostStrategy.h/GhostStrategy.cpp: 
	- Contains the WallBounceStrategy class
	- This is used for Ghosts to change direction once they hit a wall
- Maze.h/Maze.cpp: 
	- Manages the game map
	- Manages the number of energizers and dots
	- Manage Ghost/Pacman initialization
	- Detects walls
	- Keeps track of positions, and remaining items
- Dot.h/Dot.cpp: 
	- Simple implementation of a white dot
- Energizer.h/Energizer.cpp: 
	- Simple implementation of a white blinking dot

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
