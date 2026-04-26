## Project README

### Overview
The project is a graphical user interface (GUI) for an educational tool, specifically designed to simulate the functionality of GeoGebra 2.3 using C/C++. The GUI supports cross-platform compilation and execution on Linux, Windows, Wine, and WebAssembly.

### Features
- Cross-platform support: Builds and runs on Linux, Windows, Wine, and WebAssembly.
- Advanced mathematical functions: Supports complex calculations through custom libraries.
- Graphical interface: Provides a visual environment for users to interact with mathematical expressions and equations.

### Project Structure

#### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed in specific projects:
  - Linux: `X11`, `png`, `jpeg`
  - Windows: `user32`, `gdi32`, `winmm`
  - Wine: `user32`, `gdi32`, `winmm`
  - WebAssembly: No additional libraries required

#### Build & Run
The project uses Makefiles to handle the build process for different operating systems. Below are the steps to build and run the project:

1. **Build on Linux**:
   ```sh
   cd /path/to/project
   make -f Makefile.linux all
   make -f Makefile.linux do  # Build + execute
   ```

2. **Build on Windows**:
   ```sh
   cd C:\path\to\project
   mingw32-make -f Makefile.windows all
   mingw32-make -f Makefile.windows do  # Build + execute
   ```

3. **Build for Wine (Cross-compilation for Windows)**:
   ```sh
   cd /path/to/project
   make -f Makefile.wine all
   WINEPREFIX=~/wine64 WINEARCH=win64 mingw32-make -f Makefile.wine do  # Build + execute
   ```

4. **Build for WebAssembly**:
   ```sh
   cd /path/to/project
   emmake make -f Makefile.web all
   emrun --no_browser --port 8080 build/index.html  # Start a local web server to run the application
   ```

These commands ensure that the project is compiled and executed according to the specified platform. The `do` target simplifies the process by both building and executing the project.

The Makefiles provide comprehensive control over the build process, allowing for clean builds and incremental updates without removing intermediate files.