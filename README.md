<div align="center">
  
  <img width="100%" src="https://capsule-render.vercel.app/api?type=waving&color=FFD700&height=190&section=header&text=PAC-MAN&fontSize=60&fontColor=000000&animation=fadeIn&fontAlignY=38&desc=C%2B%2B%20Implementation%20of%20the%20Classic%20Arcade%20Game&descAlignY=60&descAlign=50" />
  
  <br>
  
  <p>
    <img src="https://img.shields.io/badge/C++-Solutions-yellow.svg?style=for-the-badge&logo=c%2B%2B" alt="C++ solutions"/>
    <img src="https://img.shields.io/badge/Game-Arcade-blue.svg?style=for-the-badge&logo=gamejolt" alt="Arcade Game"/>
    <img src="https://img.shields.io/badge/SFML-2.5.1-red.svg?style=for-the-badge" alt="SFML 2.5.1"/>
    <img src="https://img.shields.io/badge/Version-1.0-success.svg?style=for-the-badge" alt="Version 1.6"/>
  </p>
  
  <br>
  
  ![Pac-Man Animation](https://readme-typing-svg.herokuapp.com?font=Press+Start+2P&size=30&duration=3000&color=FFFF00&center=true&vCenter=true&width=800&height=150&lines=PAC-MAN+GAME;FAST-NUCES;C%2B%2B+%26+SFML+2.5.1;GAME+OVER)
  
  <img src="https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png" alt="line break">
  
</div>

## 📖 About

A modern C++ implementation of the classic Pac-Man arcade game. Navigate through the maze, collect dots, avoid ghosts, and use power-ups to turn the tables on your pursuers!

## 🎯 Features

- 👾 Classic Pac-Man gameplay mechanics
- 👻 Multiple ghosts with AI behavior
- 🍒 Dots and energizers collection
- 🧱 Wall collision detection and tunnel warping
- 📊 Score tracking and multiple lives
- 🔄 Game over screen with replay option

## 🎮 Controls

| Key | Action |
|-----|--------|
| I | Move Up |
| K | Move Down |
| J | Move Left |
| L | Move Right |
| ESC | Pause/Unpause |
| ENTER | Restart (after Game Over) |
| ESC | Exit (after Game Over) |

## 🏗️ Project Structure

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

## 🖥️ Implementation Details

- **Pacman**: Handles user input, power-up states, and character animation
- **Ghosts**: Implements AI movement and state transitions between normal and frightened modes
- **Maze**: Manages game map layout, walls, tunnels, and item placement
- **Game**: Orchestrates object interactions, collisions, and game state

## 🛠️ Customization

The game can be easily customized:
- Modify the number of ghosts by updating values in `Game.h`, `Maze.h` and the map in `Maze.cpp`
- Adjust game difficulty by tweaking ghost speeds and AI behavior
- Change maze layouts for different levels

## 📸 Screenshots

<div align="center">
  <img src="screenshot1.png" width="400" />
  <img src="screenshot2.png" width="400" />
</div>

## 🧩 Dependencies

- C++ compiler (built on Visual Studio Code 2022)
- [SFML 2.5.1](https://www.youtube.com/watch?v=lFzpkvrscs4) - Click for setup guide

## 🚀 Building and Running

```bash
git clone https://github.com/yourusername/pacman-clone.git
cd pacman-clone
make
./pacman
```

## 📜 License

This project is released under the MIT License.
