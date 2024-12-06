# Snake Game

![Snake Game](image/gm1.png)

## Description

This is a simple implementation of the classic "Snake" game using the [raylib](https://www.raylib.com/) library. The game supports multiple difficulty levels and various game levels.

## Technologies

<ul>
    <li><strong>Programming Language:</strong> <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-original.svg" height="30" alt="c logo"  /></li>
    <li><strong>Library:</strong> <a href="https://www.raylib.com/"><img src="https://avatars.mds.yandex.net/i?id=874a304279b87fa33dd7e9506ead1e04_l-5210344-images-thumbs&n=13" height="30" alt="cmake logo"  /></a></li>
    <li><strong>Build System:</strong> <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cmake/cmake-original.svg" height="30" alt="cmake logo"  /></li>
</ul>

## Installation and Running

### Requirements

- CMake 3.10 or higher
- C Compiler (e.g., GCC or Clang)
- raylib (automatically downloaded and installed via CMake)

### Installation Instructions

1. Clone the repository:

   ```bash
   git clone https://github.com/BogdanPryadko4853/snake.git
   cd snake
Create a build directory and navigate into it:

bash
Copy
mkdir build
cd build
Generate the build files using CMake:

bash
Copy
cmake ..
Build the project:

bash
Copy
make
Run the game:

bash
Copy
./snake
Game Examples
<div style="display: flex; justify-content: space-between; margin-bottom: 20px;"> <img src="image/gm1.png" alt="Game Example 1" style="width: 48%;"> <img src="image/gm2.png" alt="Game Example 2" style="width: 48%;"> </div><div style="display: flex; justify-content: space-between;"> <img src="image/lwl1.png" alt="Level 1" style="width: 48%;"> <img src="image/lwl2.png" alt="Level 2" style="width: 48%;"> </div>
Controls
Arrow Keys or WASD to control the snake.

Enter to start the game or select a level.

R to restart the level.

F to restart the game after losing.

Project Structure
Copy
snake-game/
├── CMakeLists.txt
├── README.md
├── main.c
├── snake.c
└── snake.h
