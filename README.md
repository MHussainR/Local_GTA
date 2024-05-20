# Local GTA

## Overview
This project is a simplified 2D version of Grand Theft Auto (GTA) implemented using Object-Oriented Programming (OOP) techniques in C++. The game features various elements such as AI, missions, different character interactions, and a dynamic environment. Techniques like ray casting and sprite stacking are utilized to create 3D effects, enhancing the visual experience.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)

## Features
- **AI and NPCs**: Complex AI controlling Non-Player Characters (NPCs) with varied behaviors.
- **Missions**: Includes different missions like Ambulance and Taxi missions.
- **Weapons**: Multiple weapons with distinct behaviors such as AR, Handgun, and Shotgun.
- **Dynamic Environment**: Features like circular menus, health management, and a coordinate system.
- **Graphics**: Implements ray casting and sprite stacking for 3D effects.
- **Audio**: Managed by MusicManager for in-game sounds and music.

## Installation
To compile and run this project, you need to have a C++ compiler and the SDL2 library installed on your system.

### Steps:
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Local_GTA.git
   cd Local_GTA

2. Install the required libraries:
    sudo apt-get install libsdl2-dev

3. Compile the project using the provided Makefile:
    make

4. Run the game:
    ./Local_GTA

## Usage
-Controls:
    -Movement: Use arrow keys to navigate.
    -Action: Spacebar for interactions.
    -Missions: Follow on-screen instructions for mission-specific controls.
-Cheat Codes: Implemented in 'cheat_codes.cpp', can be activated during gameplay.

## Project Structure
-Main Files:
    -'main.cpp': Entry point of the game.
    -'game.cpp', game.hpp: Core game logic.
    -'AI.cpp', 'AI.hpp': AI logic for NPCs.

-Missions:

    -'AmbulanceMission.cpp', 'AmbulanceMission.hpp'
    -'TaxiMission.cpp', 'TaxiMission.hpp'

-Weapons:

    -'ARBullets.cpp', 'ARBullets.hpp'
    -'HandGunBullets.cpp', 'HandGunBullets.hpp'
    -'ShotgunBullets.cpp', 'ShotgunBullets.hpp'

-Graphics:

    -'RayCaster.cpp', 'RayCaster.hpp': Implements ray casting.
    -'stacked_sprites.cpp', 'stacked_sprites.hpp': Implements sprite stacking.

-Utilities:

    -'FontManager.cpp', 'FontManager.hpp'
    -'TextureManager.cpp', 'TextureManager.hpp'
    -'MusicManager.cpp', 'MusicManager.hpp'

-Assets:

    -'assets/': Contains images and textures.
    -'fonts/': Contains font files.
    -'Music/': Contains audio files.

-Documentation:

    'UML.pdf', 'UML.png': UML diagrams for the project structure.