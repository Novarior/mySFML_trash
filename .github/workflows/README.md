# Ekzeckt a game

This repository contains the game project "Ekzeckt"
in it I learn the c++ language and its capabilities
the SFML and Nolhmann-json libraries are included
also minimal work with MacOS frameworks

## Features

- **Texture Generation**: Procedural generation of textures using SFML.
- **Noise Viewer**: Tools for Perlin and Simplex noise manipulation and visualization.
- **L-System Trees**: Implementation of L-systems for generating tree-like structures.
- **SFML Integration**: work with  the SFML (2.x >> 3.0, depending on the commit).

## Requirements

- **SFML Version**: 3.0 (or compatible version).
- **Compiler**: GCC 9+, Clang 9+, MSVC 16+ (with C++17 support).
- **CMake**: Version 3.10 or higher.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Novarior/Ekzeckt.git
   cd mySFML_trash
   ```

2. Configure the project using CMake:
   ```bash
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   ```
   or for Debug:
   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Debug
   ```

3. Build the project:
   ```bash
   cmake --build .
   ```

4. After build, u can find applications in `build/bin/` directory.

## Structure

- `source/`: Contains all source files.
- `states/`: Contains files with application states, be it settings, editor or gameplay
- `source/source`: Contains my parser for saving/loading data, based on Nolnmann-json
- `math/`: Contains the mathematical part of the code
- `res/`: Contains texts, fonts, style files and other resources.
- `Localisation/` contains implementation files for working with localisation (will add documentation in the future)
- `GUI/`: some stuff Buttons, sliders, etc.
- `entity/`: entity logic, some logic, useless for the current behaviour
- `core/`: main functionality for initialising the application, contains code for calling some MacOS functions
- `content/`: contains the map, items, and game entities
- `metadata`: some files for building on OSX
- `build/`: Build directory (created during installation).



## Known Issues

- Continued performance optimizations for large textures and noise rendering.
- Continued search for keyboard input issue
(keyboard is not handled correctly when app is launched directly instead of via VSCode)
- Fix texture loading and its dependencies
- Fix current entity behavior code
- there is no correct initialization of text variables from/for localization

## Future Plans

- Work with GUI part, also with custom variabless view
- Improve GUI for noise and texture editing. 
- Improve GUI for gameplay part
- Improve save/load system something part of game, for uniform view 
- Additional procedural generation tools (e.g., terrain generation, impot/export textures, map data).
- Performance optimizations for real-time rendering.
- Split debug and realize builds
- Work with AI/Bot system (entity logic)
- Add suport audio (for now its in test, first trying)

## Contributing

Feel free to fork the repository and submit pull requests with new ideas or fixes. Make sure to document any changes and follow the existing coding style.

## License

This repository is distributed under the MIT License. See `LICENSE` for details.

## Contact

For questions or feedback, open an issue or contact me via GitHub.



## using libs:
- SFML 3.0.0 (https://github.com/SFML/SFML)
- nlohmann/JSON (https://github.com/nlohmann/json)

usind frameworks:
- CoreFoundation
- CoreServices

Fonts was taken from:
- https://www.1001fonts.com

The FontStruction “7:12 Serif”
(http://fontstruct.com/fontstructions/show/243645) by “CMunk” is licensed
under a Creative Commons Attribution Share Alike license
(http://creativecommons.org/licenses/by-sa/3.0/).

## Test was sucsessfully compiled and run on:
-  MacOS 13 and higher
