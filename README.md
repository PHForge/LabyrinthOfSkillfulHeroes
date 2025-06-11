# Labyrinth of Skillful Heroes 🎮

**Labyrinth of Skillful Heroes** is a text-based RPG developed in C, designed to showcase advanced programming concepts through an engaging game experience. Players control a hero navigating a dynamically generated 2D maze, collecting skills, battling enemies, and solving challenges to reach the exit. The game features a modular architecture, multilingual support (English/French), save/load functionality, and customizable gameplay settings, making it both a technical achievement and a tribute to classic RPG adventures.

![Language](https://img.shields.io/badge/language-C-green.svg) ![License](https://img.shields.io/badge/license-MIT-blue.svg)
![GameVersion](https://img.shields.io/badge/GameVersion-0.1-white)

<br>

## Features 📋
- **Interactive Menu**: Choose from New Game, Load Game, Settings (language and difficulty), Credits, or Quit.
- **Dynamic Maze Generation**: Procedurally generated 2D mazes using a recursive backtracking algorithm, ensuring solvability.
- **Skill System**: Skills (e.g., attack, heal) managed via a linked list, with actions implemented through function pointers and variable parameters stored in unions.
- **Multilingual Support**: Seamless switching between English and French, with translations loaded from external `.lang` files.
- **Save/Load System**: Persist game state (maze, player position, skills, settings) to a `.save` file for resuming gameplay.
- **Customizable Gameplay**: Adjust difficulty to scale maze size and challenge intensity.
- **Personalized Credits**: A heartfelt dedication to the developer's family for their support and inspiration.
- **Retro ASCII Art**: Enjoy a nostalgic interface with an ASCII art banner displayed at startup, evoking classic text-based RPGs.

<br>

## Technical Highlights 🔦

- **Dynamic Memory Management**: Extensive use of `malloc` and `free` for maze grids, linked lists, and string handling.
- **Data Structures**: Implementation of a linked list for skill management, with function pointers for flexible action execution.
- **File I/O**: Robust save/load system for persisting game state and multilingual support via external translation files.
- **Pointer Arithmetic**: Optimized maze navigation using pointer-based access to 2D grid cells.
- **Modular Design**: Clean separation of concerns across multiple source and header files, enhancing maintainability.
- **Algorithm Design**: Recursive backtracking algorithm for generating solvable mazes.

<br>

## System Requirements ⚙️

The following components are required to build, run, or contribute to this project:

| Component          | Requirement                              | Notes                                      |
|--------------------|------------------------------------------|--------------------------------------------|
| Language | C                                      | Core language used for the project         |
| Compiler       | GCC                                      | Ensure GCC is installed (e.g., MinGW for Windows) |
| Libraries      | Standard C Libraries (stdio.h, string.h, stdlib.h, time.h, locale.h, windows.h) | Included with standard C installations      |
| IDE/Editor     | VS Code or any C-compatible IDE/terminal | Other IDEs like Code::Block or CLion can be used |
| Version Control | Git                                     | Required to clone the repository           |

> [!TIP]
> For optimal setup, install GCC via [MinGW](https://www.mingw-w64.org/) on Windows or use a package manager like `apt` or `brew` on Linux/macOS to install Git and GCC.

<br>

## Installation </>

1. **Clone the Repository**:
	```bash
	git clone https://github.com/PHForge/LabyrinthOfSkillfulHeroes.git
	cd LabyrinthOfSkillfulHeroes
	```

2. **Compile the Project**:
	- Windows: Use MinGW and run:
		```bash
		gcc src/*.c -o labyrinth -I include
		```
	- Linux/macOS: Ensure GCC is installed (`sudo apt install gcc` or `brew install gcc`) and run:
		```bash
		gcc src/*.c -o labyrinth -I include
		```

4. **Run the Game**:
	```bash
	./labyrinth
	```

<br>

## Project Structure 🗂️
```bash
LabyrinthOfSkillfulHeroes/
├── include/
│   ├── maze.h           // Maze-related structures and function declarations
│   ├── game.h           // Game state, skill system, and action function declarations
│   ├── utils.h          // Utility functions for translations, save/load, and more
├── src/
│   ├── main.c          // Main entry point and game loop
│   ├── maze.c          // Maze generation and navigation logic
│   ├── game.c          // Core game mechanics and skill management
│   ├── utils.c         // Utility function implementations
├── data/
│   ├── translations/
│   │   ├── en.lang     // English translation strings
│   │   ├── fr.lang     // French translation strings
│   ├── saves/
│   │   ├── game_slot1.save   // Saved game state
├── .gitignore           // Git ignore configuration
├── LICENSE             // MIT License
└── README.md           // Project documentation
```

<br>

## License 🧾

This project is licensed under the **MIT License** - see the LICENSE file for details.

<br>

## Crédits ☕

> Developed by PHForge. 
> Feel free to reach out via [GitHub](https://github.com/PHForge) for feedback or collaboration ideas!

> Special thanks ❤️ to my wife and son for their patience and love.

<br>

## Example Output 💻

```c

 88888888888888888888888888888888888888888888888888888888888888888888888
 88.._|      | `-.  | `.  -_-_ _-_  _-  _- -_ -  .'|   |.'|     |  _..88
 88   `-.._  |    |`!  |`.  -_ -__ -_ _- _-_-  .'  |.;'   |   _.!-'|  88
 88      | `-!._  |  `;!  ;. _______________ ,'| .-' |   _!.i'     |  88
 88..__  |     |`-|._ | `.| |_______________||.''|  _|.:'   |     _|..88
 88   |'''..__ |    |'':.|  |_|MMMMMMMMMMM|_|'| _!-|   |   _|..-|'    88
 88   |      |``--..|_ | `;!|@|MMMMMMMMMMM|@|.'|   |_..!-'|     |     88
 88   |      |    |   |`-,!_|_|MMMMP'YMMMM|_||.!-;'  |    |     |     88
 88___|______|____!.,.!,.!,!|@|MMMM * MMMM|@|,!,.!.,.!..__|_____|_____88
 88      |     |    |  |  | |_|MMMMb,dMMMM|_|| |   |   |    |      |  88
 88      |     |    |..!-;' |@|MMMMMMMMMMM|@| |`-..|   |    |      |  88
 88      |    _!.-j'  | _!,'|_|MMMMMMMMMMM|_||!._|  `--!.._ |      |  88
 88     _!.-'|    | _.'|  !;|@|MMMMMMMMMMM|@|`.| `-._|    |``-.._  |  88
 88..-i'     |  _.''|  !-| !|_|MMMMMMMMMMM|_|.|`-. | ``._ |     |``'..88
 88   |      |.|    |.|  !| |@|MMMMMMMMMMM|@||`. |`!   | `'.    |     88
 88   |  _.-'  |  .'  |.' |/|_|MMMMMMMMMMM|_|! |`!  `,.|    |-._|     88
 88  _!''|     !.'|  .'| .'|[@]MMMMMMMMMMM[@] \|  `. | `._  |   `-._  88
 88-'    |   .'   |.|  |/| /                 \|`.  |`!    |.|      |`-88
 88      |_.'|   .' | .' |/                   \  \ |  `.  | `._-   |  88
 88     .'   | .'   |/|  /                     \ |`!   |`.|    `.  |  88
 88  _.'     !'|   .' | /                       \|  `  |  `.    |`.|  88
 88888888888888888888888888888888888888888888888888888888888888888888888
 888888888888888888888 Labyrinth of Skillful Heroes 88888888888888888888
 88888888888888888888888888888888888888888888888888888888888888888888888

                                                             by PHForge

 === Welcome - Main menu ===

1. New Game
2. Load Game
3. Settings
4. Credits
5. Quit

Enter your choice:
```