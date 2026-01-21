# The Traitor
A 5-player multiplayer strategy party game.

## Demo
[Demo video](https://drive.google.com/file/d/1e18D3aSvErqhNpVGPptM73z1QTmkKOoB/view?usp=drivesdk)

## Credits
Muhammed Enes Karaca \
Enes Can Bozkurt \
Muhammed Yıldız \
Ahmet Yasin Çetinkaya

To triangulate map parts, we used earcut.hpp from https://github.com/mapbox/earcut.hpp. \
Icons by https://icons8.com/.

## How to Build

### On Linux
Because this project uses static linking, this command needs to run to install dependencies of SFML: \
`sudo apt-get update && sudo apt-get install libxrandr-dev libxcursor-dev libxi-dev libudev-dev libflac-dev libvorbis-dev libogg-dev libopus-dev libopusfile-dev libgl1-mesa-dev libegl1-mesa-dev libfreetype-dev`

#### If you are using VS Code
Just install C/C++ Extension Pack and CMake Tools. \
When you open the project folder with VS Code, CMake Tools extension will automatically config the build system for you. \
Press Ctrl + Shift + P, write CMake:Debug and you are ready.
#### If you are not using VS Code
Open a terminal in the projects root directory. \
Run `mkdir build`. \
Run `cd build`. \
Run `cmake ..`.

### On Windows
Open the project folder in Visual Studio and it will configure everything for you.
