# MySFML Trash

This repository is a playground for experimenting with SFML functionalities, such as texture generation, noise manipulation, and procedural generation using L-systems.

## Features

- **Texture Generation**: Procedural generation of textures using SFML.
- **Noise Viewer**: Tools for Perlin and Simplex noise manipulation and visualization.
- **L-System Trees**: Implementation of L-systems for generating tree-like structures.
- **SFML Integration**: Experiments with the SFML (2.x or 3.0, depending on the branch).

## Requirements

- **SFML Version**: 3.0 (or compatible version).
- **Compiler**: GCC 9+, Clang 9+, MSVC 16+ (with C++17 support).
- **CMake**: Version 3.15 or higher.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Novarior/mySFML_trash.git
   cd mySFML_trash
   ```

2. Configure the project using CMake:
   ```bash
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   ```

3. Build the project:
   ```bash
   cmake --build .
   ```

4. Run the executable (adjust the path if needed):
   ```bash
   ./mySFML_trash
   ```

## Structure

- `source/`: Contains all source files.
- `states/`: Contains states of applications files.
- `source/source`: Contains custom parser for save/load data.
- `math/`: Contain math part of code
- `res/`: Placeholder for textures, shaders, and other assets.
- `Localisation/` ...
- `GUI/`: some stuff Buttons, sliders, ect..
- `entity/`: have a core of entity, some (bad) logic, useles,
- `code/`: main.cpp be short, with system functional
- `content/`: have a core of map, item, inventory add more later ^__^
- `metadata`: some files for OSX bundles
- `build/`: Build directory (created during installation).

## Usage

- **L-System Trees**: Generates procedural trees using L-systems. Modify rules in the `TileMap` method to experiment with different structures.
- **Noise Viewer**: Visualize and manipulate Perlin and Simplex noise. Integrated into the `NoiseViewer` class.


## Known Issues

- Certain features may rely on SFML 2.x APIs. If using SFML 3.0, ensure compatibility by updating methods and classes.
- Performance optimization for larger textures and noise visualizations is ongoing.

## Future Plans

- Full migration to SFML 3.0 with updated APIs.
- Improved UI for noise and texture editing.
- Additional procedural generation tools (e.g., terrain generation).
- Performance optimizations for real-time rendering.

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

- tested on MacOS