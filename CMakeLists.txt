cmake_minimum_required(VERSION 3.28)
project(Logen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include(FetchContent)

# GLFW & Glad
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG master)
FetchContent_Declare(glad GIT_REPOSITORY https://github.com/SasLuca/MyGlad.git GIT_TAG master)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glad)

# GLM
FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	8d1fd52e5ab5590e2c81768ace50c72bae28f2ed #refs/tags/1.0.3
)
FetchContent_MakeAvailable(glm)

# Assimp
set(ASSIMP_ROOT_DIR "${CMAKE_HOME_DIRECTORY}/vendor/assimp")
add_library(assimp SHARED IMPORTED
        ../core/graphics/Renderer.cpp
        ../core/graphics/Renderer.h
        ../core/io/Input.cpp
        ../core/io/Input.h
        ../core/graphics/Mesh.cpp
        ../core/graphics/Mesh.h
        ../core/graphics/Model.cpp
        ../core/graphics/Model.h
        ../core/graphics/Shader.cpp
        ../core/graphics/Shader.h
        ../core/graphics/Camera.cpp
        ../core/graphics/Camera.h)
set_target_properties(assimp PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_ROOT_DIR}/include"
        IMPORTED_IMPLIB             "${ASSIMP_ROOT_DIR}/lib/Release/assimp-vc145-mt.lib" # Path to your .lib file
        IMPORTED_LOCATION           "${ASSIMP_ROOT_DIR}/bin/Release/assimp-vc145-mt.dll" # Path to your .dll file
)

add_subdirectory("src/core")
add_subdirectory("src/runtime")
