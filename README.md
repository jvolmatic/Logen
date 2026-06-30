# Logen

`Logen` is a small C++20 OpenGL game engine project that follows the style and ideas from [LearnOpenGL](https://learnopengl.com/).

## Dependencies

This project currently uses local vendored dependencies from `vendor/`:

- `glfw`
- `glad`
- `glm`
- `assimp`

`glad` is generated during the build from the `vendor/glad` submodule.

## Prerequisites

- CMake 3.28 or newer
- A C++20-compatible compiler
  - MinGW/MSYS2 GCC
  - MSVC
  - Clang
- Python 3
- `pip`
- Ninja (used in the example commands below)

## Clone and initialize submodules

If you are cloning the repository for the first time:

```powershell
git clone https://github.com/jvolmatic/Logen
git submodule update --init --recursive
```

If you already cloned the repository:

```powershell
git submodule update --init --recursive
```

## Python setup for `glad`

The `glad` submodule uses a Python generator and requires `jinja2`.

```powershell
python -m pip install "jinja2>=2.7,<4.0"
```

## Build (PowerShell)

From the project root:

```powershell
cmake -S . -B cmake-build -G Ninja
cmake --build cmake-build --target LogenRuntime -j 4
```

## Run

Build outputs are written to `bin/`.

```powershell
.\bin\game.exe
```

## Notes

- `glfw`, `glad`, `glm`, and `assimp` are consumed from `vendor/`.
- `assimp` is built from source by CMake and linked into the project.
- `glad` is generated during the build and currently targets `OpenGL 4.6 core`.
- The runtime target is `LogenRuntime`, which produces `bin/game.exe`.
- The core library target is `LogenCore`, which produces `bin/logen.dll` on Windows.

## Troubleshooting

### `ModuleNotFoundError: No module named 'jinja2'`

Install the missing Python package:

```powershell
python -m pip install "jinja2>=2.7,<4.0"
```

### Submodule-related configure errors

Make sure all submodules are initialized:

```powershell
git submodule update --init --recursive
```

### Generator mismatch or stale build directory

If CMake was previously configured with a different generator, remove the build directory and configure again:

```powershell
Remove-Item -Recurse -Force .\cmake-build
cmake -S . -B cmake-build -G Ninja
cmake --build cmake-build --target LogenRuntime -j 4
```

