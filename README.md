<h1 style="font-size: 3em; color: #4CAF50; text-shadow: 2px 2px 4px #000000; padding: 20px; border: 2px solid #4CAF50; border-radius: 10px; background-color: #f9f9f9; display: inline-block;">
    😊 Hello coders 😊
</h1>

<h1 style:"color:red; ">Snake Game</h1>

<img src="image/gm1.png" alt="Snake Game">

<h2>Description</h2>
<p>This is a simple implementation of the classic "Snake" game using the <a href="https://www.raylib.com/">raylib</a> library. The game supports multiple difficulty levels and various game levels.</p>

<h2>Technologies</h2>
<ul>
    <li><strong>Programming Language:</strong> <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-original.svg" height="30" alt="c logo"  /> C</li>
    <li><strong>Library:</strong> <a href="https://www.raylib.com/"><img src="https://avatars.mds.yandex.net/i?id=874a304279b87fa33dd7e9506ead1e04_l-5210344-images-thumbs&n=13" height="30" alt="cmake logo"  /></a> raylib</li>
    <li><strong>Build System:</strong> <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cmake/cmake-original.svg" height="30" alt="cmake logo"  /> CMake</li>
</ul>

<h2>Installation and Running</h2>
<h3>Requirements</h3>
<ul>
    <li>CMake 3.10 or higher</li>
    <li>C Compiler (e.g., GCC or Clang)</li>
    <li>raylib (automatically downloaded and installed via CMake)</li>
</ul>

<h3>Installation Instructions</h3>
<ol>
    <li>Clone the repository:</li>
    <pre><code>git clone https://github.com/BogdanPryadko4853/snake.git
cd snake</code></pre>
    <li>Create a build directory and navigate into it:</li>
    <pre><code>mkdir build
cd build</code></pre>
    <li>Generate the build files using CMake:</li>
    <pre><code>cmake ..</code></pre>
    <li>Build the project:</li>
    <pre><code>make</code></pre>
    <li>Run the game:</li>
    <pre><code>./snake</code></pre>
</ol>

<h2>Game Examples</h2>
<div class="game-examples">
    <img src="image/gm1.png" alt="Game Example 1">
    <img src="image/gm2.png" alt="Game Example 2">
</div>
<div class="game-examples">
    <img src="image/lwl1.png" alt="Level 1">
    <img src="image/lwl2.png" alt="Level 2">
</div>

<h2>Controls</h2>
<ul>
    <li><strong>Arrow Keys</strong> or <strong>WASD</strong> to control the snake.</li>
    <li><strong>Enter</strong> to start the game or select a level.</li>
    <li><strong>R</strong> to restart the level.</li>
    <li><strong>F</strong> to restart the game after losing.</li>
</ul>

<h2>Project Structure</h2>
<pre><code>snake-game/
├── CMakeLists.txt
├── README.md
├── main.c
├── snake.c
└── snake.h</code></pre>
