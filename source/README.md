# Source Files

## Project Structure

```
├── main.cpp            # Application entry point
├── Game.h/cpp          # Core game loop and coordination
├── GameObject.h/cpp    # Base class for all game objects
├── Pacman.h/cpp        # Player character implementation
├── Ghost.h/cpp         # Enemy implementation
├── GhostStrategy.h/cpp # Ghost AI behavior strategies
├── Maze.h/cpp          # Game map and collision detection
├── Dot.h/cpp           # Collectible implementation
└── Energizer.h/cpp     # Power-up implementation
```

## Customization

The game can be easily customized:
- Modify the number of ghosts by updating ghost-count values in `Game.h`, `Maze.h` and the map in `Maze.cpp`
- Adjust game difficulty by tweaking ghost speeds and AI behavior
- Change maze layouts for different levels in `Maze.cpp`
- Pacman colour can also be altered in `pacman.cpp`
