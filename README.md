# Logen

A very barebones game engine using opengl and closely follows the implementations in https://learnopengl.com/.

## Prerequisites

- CMake 3.28+
- A C++20 compiler (MinGW/MSYS2 GCC, MSVC, or Clang)
- Python 3 (required by `vendor/glad` code generation)
- Ninja (optional, used in examples below)

## Clone and initialize submodules

```powershell
git clone <your-repo-url>
Set-Location Logen
git submodule update --init --recursive
```

## Build (PowerShell)

`glad` is generated during the build and requires `jinja2`.

```powershell
python -m pip install "jinja2>=2.7,<4.0"
cmake -S . -B cmake-build -G Ninja
cmake --build cmake-build --target LogenRuntime -j 4
```

Output binaries are placed in `bin/`.

## Run

```powershell
.\bin\game.exe
```

## Notes

- `glfw` and `assimp` are used as submodules from `vendor/`.
- `glad` is also used from `vendor/` and generated at build time.
- `glm` is currently fetched with CMake `FetchContent`.

