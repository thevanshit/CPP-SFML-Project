# C++ SFML Projects

[![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat-square&logo=cplusplus&logoColor=white)](https://isocpp.org)
[![SFML](https://img.shields.io/badge/SFML-2.5+-8F8F8F?style=flat-square&logo=sfml&logoColor=white)](https://www.sfml-dev.org)
[![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)](LICENSE)

A collection of C++ projects built with SFML (Simple and Fast Multimedia Library) for college assignments. Includes an endless-runner game and a GUI calculator.

## Projects

### DinoRun

A 2D endless-runner game inspired by the classic Chrome dinosaur game. The objective is to survive as long as possible by jumping over obstacles while the game speed gradually increases.

**Features:**
- Endless runner gameplay with increasing difficulty
- Jump mechanics with gravity simulation
- Obstacle spawning and collision detection
- Score tracking with high score persistence
- Game over screen with restart option

**Controls:**

| Key   | Action              |
|-------|---------------------|
| Space | Jump / Restart game |
| Esc   | Exit game           |

### Calculator

A desktop GUI calculator built with SFML. Supports basic arithmetic operations with a clean on-screen button interface.

**Features:**
- Left-to-right expression evaluation
- On-screen number pad and operator buttons
- Keyboard input support
- Clear display functionality
- Real-time input display

## Project Structure

```
CPP-SFML-Project/
├── DinoRun/              # Endless runner game
│   ├── main.cpp          # Entry point
│   ├── Game.cpp / .h     # Game loop and state management
│   ├── Player.cpp / .h   # Player character logic
│   └── Obstacle.cpp / .h # Obstacle behavior
├── Calculator.cpp        # GUI calculator application
├── Poppins-Regular.ttf   # UI font
├── Poppins-Bold.ttf      # UI font
└── README.md
```

## Requirements

- C++17 or newer
- SFML 2.5 or later
- A compiler supporting modern C++ (g++, clang, MSVC)

## Build Instructions

### macOS / Linux

```bash
# Install SFML
brew install sfml
# or: sudo apt install libsfml-dev

# Clone and build
git clone https://github.com/thevanshit/CPP-SFML-Project.git
cd CPP-SFML-Project

# Build DinoRun
g++ -std=c++17 DinoRun/*.cpp -o DinoRun -lsfml-graphics -lsfml-window -lsfml-system

# Build Calculator
g++ -std=c++17 Calculator.cpp -o Calculator -lsfml-graphics -lsfml-window -lsfml-system
```

### Windows (MinGW)

```cmd
g++ -std=c++17 DinoRun/*.cpp -o DinoRun.exe ^
    -lsfml-graphics -lsfml-window -lsfml-system
```

## Learning Goals

- Game loops and frame timing
- Event handling with SFML
- Basic physics (jump + gravity)
- Object-oriented design in C++
- Collision detection
- GUI layout and event-driven programming

## License

MIT License
