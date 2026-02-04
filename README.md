# BrickGame

A classic **Brick Breaker** game implementation in C++ using the [Raylib](https://www.raylib.com/) library. This project demonstrates a clean, object-oriented approach to game development with custom vector mathematics and collision physics.

## 🎮 Features

- **Classic Gameplay**: Control the paddle to bounce the ball and destroy bricks.
- **Physics-Based Collision**: Custom 2D vector physics for ball movement and reflection.
- **Score & Lives**: Track your progress and manage player lives (defaut: 5 lives).
- **Restart & Pause**: Pause functionality and game over states.
- **Colorful Visuals**: Dynamic brick colors and clean UI rendering.
- **Cross-Platform**: Built with CMake, supporting Windows, Linux, and macOS.

## 🛠️ Build Instructions

This project uses **CMake** for its build system and automatically manages dependencies (Raylib) using `FetchContent`. You do **not** need to manually install Raylib.

### Prerequisites

- **CMake**: Version 3.11 or higher.
- **C++ Compiler**: MSVC (Windows), GCC/Clang (Linux/macOS).
- **Git**: Required for fetching Raylib.

### Building for Desktop

1.  **Configure the project**:
    ```bash
    cmake -S . -B build
    ```
    *Note: On Windows, this defaults to Visual Studio. To use MinGW, add `-G "MinGW Makefiles"`.*

2.  **Build the executable**:
    ```bash
    cmake --build build
    ```

3.  **Run the game**:
    ```bash
    ./build/BrickGame.exe  # Windows
    ./build/BrickGame      # Linux/macOS
    ```

### Building for Web (Emscripten)

Requires the [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html).

```bash
mkdir build_web
cd build_web
emcmake cmake .. -DPLATFORM=Web -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXECUTABLE_SUFFIX=".html"
emmake make
```

## 📂 Project Structure

The project is organized into a modular structure:

```
BrickGame/
├── CMakeLists.txt       # Build configuration & Raylib dependency management
├── main.cpp             # Entry point
└── lib/                 # Game logic and classes
    ├── Game.h/.cpp      # Main game loop and state management
    ├── Board.h/.cpp     # Manages the grid of bricks
    ├── Player.h/.cpp    # Paddle logic and input handling
    ├── Ball.h/.cpp      # Ball physics and movement
    ├── Brick.h/.cpp     # Individual brick logic and collision detection
    ├── Vec2.h/.cpp      # Custom 2D Vector mathematics helper
    └── Settings.h       # Global constants (Screen size, colors, speed)
```

## 💻 Code Implementation Details

### 1. Build System (`CMakeLists.txt`)
The build system is designed for ease of use. It uses `FetchContent` to automatically download and compile a specific version of **Raylib** (v5.5) if it's not found on the system.
```cmake
include(FetchContent)
FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
)
FetchContent_MakeAvailable(raylib)
```
This ensures that anyone can clone and build the project without "DLL hell" or library path issues.

### 2. Game Loop (`Game` Class)
The `Game` class encapsulates the entire application lifecycle.
- **`UpdateGame()`**: Handles input, updates object positions, and checks for game-over conditions.
- **`DrawGame()`**: Handled rendering frame-by-frame using Raylib's `BeginDrawing()`/`EndDrawing()`.

### 3. Physics & Vectors (`Vec2`)
Instead of relying solely on Raylib's math structs, a custom `Vec2` class is implemented to handle 2D vector operations (addition, subtraction, normalization, length calculation). This allows for precise control over the ball's direction and speed.

### 4. Collision System
Collision is handled in `Brick::Update` and `Player::Update`.
- The system calculates the exact point of impact to determine bounce direction.
- It uses vector math to determine if the ball hit the **top/bottom** or **sides** of a brick/paddle to reflect the `x` or `y` velocity component accordingly.

## 🕹️ Controls

- **Left Arrow**: Move Paddle Left
- **Right Arrow**: Move Paddle Right
- **Space**: Pause / Resume Game


## 🚀 Upcoming Features / Todos

Here are some planned improvements and feature ideas for the future:

- [ ] **Refine Ball Physics**: Currently, the randomness in ball reflection is too high/odd. Needs to be smoothed out for more predictable gameplay.
- [ ] **Dynamic Difficulty**: Implement ball acceleration as the number of bricks decreases to ramp up the challenge.
- [ ] **Power-ups**: Add droppable items from destroyed bricks (e.g., Multi-ball, Wide Paddle, Sticky Paddle, Lasers).
- [ ] **Level System**: Load brick layouts from files to support multiple levels with increasing difficulty.
- [ ] **Sound Effects**: Add audio feedback for brick hits, paddle bounces, and game over states.
- [ ] **High Score System**: Save and load high scores to/from a local file.
- [ ] **Menu System**: Add a Start Screen, Pause Menu, and Difficulty Selection.

## 📝 License

This project is open source. Feel free to modify it!
