# 🕹️ Basic Tetris Game Project (C++ & Web Frontend)

A classic **Tetris** implementation featuring both a custom C++ console game engine and a modern, zero-setup HTML5/JavaScript web frontend. This project explores fundamental game development concepts such as 2D array matrix manipulation, collision detection, and real-time event handling.

🧩 Tetris Project Overview: Dual Implementation
1. The C++ Console Version (Tet.ris.cpp)
What it is: A terminal-based implementation of Tetris built in C++.

Core Logic: Uses a 2D matrix array (10x20 board) to manage game coordinates, collision detection, and piece merging.

Controls & Rendering: Utilizes Windows console APIs (windows.h) for smooth cursor handling (gotoxy) and real-time keyboard polling (_kbhit / _getch).

Personal Experience Note: While C++ is not my most familiar territory, building this project was a smooth, fun, and rewarding entry point into handling game loops, state tracking, and matrix algorithms.

2. The Interactive Web Version (index.html)
What it is: A zero-setup, modern graphical browser version built using HTML5 Canvas and JavaScript.

Core Logic: Implements classic tetromino rotations, automated drop timers (requestAnimationFrame), and complete line-sweep algorithms (arenaSweep) right in the browser.

Rendering & Experience: Features a sleek dark-theme arcade interface with vivid colored blocks, real-time score tracking, and smooth responsive gameplay using keyboard event listeners.

## 💡 Developer Reflection & Journey
While C++ isn't my most familiar territory, tackling this Tetris implementation proved to be a smooth, fun, and rewarding entry point into systems programming and game loop design. Transitioning from the core logic to an interactive browser frontend made it a fantastic learning experience for handling state management, grids, and rendering.

---

## 📂 Project Structure

```text
├── Tet.ris.cpp      # Core console-based C++ game logic and loop
├── index.html       # Modern, interactive browser-based frontend (HTML5 Canvas / JS)
└── README.md        # Project documentation
