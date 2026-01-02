# DinoRun – C++ SFML Game

DinoRun is a simple 2D endless-runner game written in **C++** using the **SFML (Simple and Fast Multimedia Library)**.
The game is inspired by the classic offline dinosaur runner, with a minimal visual style and core gameplay mechanics implemented from scratch.

The objective is straightforward: survive as long as possible by jumping over obstacles while the game speed gradually increases.


## Features

* Endless runner gameplay
* Player jump mechanics with gravity
* Obstacle spawning and movement
* Collision detection
* Score tracking
* High score persistence during runtime
* Game over screen with restart option
* Clean and minimal UI


## Gameplay Overview

* The player controls a dinosaur character.
* Obstacles move from right to left across the screen.
* Press **SPACE** to jump over obstacles.
* Each obstacle passed increases the score.
* Collision with an obstacle ends the game.
* After game over, press **SPACE** to restart.


## Controls

| Key          | Action              |
| ------------ | ------------------- |
| Space        | Jump / Restart game |
| Close Window | Exit game           |


## Project Structure

```
CPP-SFML-Project/
│
├── DinoRun/
│   ├── main.cpp
│   ├── Game.cpp
│   ├── Game.h
│   ├── Player.cpp
│   ├── Player.h
│   ├── Obstacle.cpp
│   ├── Obstacle.h
│
├── assets/
│   └── fonts/
│
└── README.md
```


## Requirements

* C++17 or newer
* SFML 2.5 or later
* A compiler supporting modern C++ (g++, clang, MSVC)


## Build Instructions

### macOS / Linux

1. Install SFML:

   ```
   brew install sfml
   ```

   or

   ```
   sudo apt install libsfml-dev
   ```

2. Clone the repository:

   ```
   git clone https://github.com/thevanshit/CPP-SFML-Project.git
   ```

3. Build the project:

   ```
   g++ -std=c++17 DinoRun/*.cpp -o DinoRun \
       -lsfml-graphics -lsfml-window -lsfml-system
   ```

4. Run:

   ```
   ./DinoRun
   ```

---

### Windows (MinGW)

1. Install SFML and set up environment variables.
2. Compile using:

   ```
   g++ -std=c++17 DinoRun/*.cpp -o DinoRun.exe ^
       -lsfml-graphics -lsfml-window -lsfml-system
   ```

---

## Learning Goals

This project focuses on:

* Game loops and frame timing
* Event handling with SFML
* Basic physics (jump + gravity)
* Object-oriented design in C++
* Collision detection
* Resource management

---

## Future Improvements

* Animated sprites
* Sound effects and background music
* Difficulty scaling
* Pause functionality
* Persistent high score saving
* Better obstacle variety

