cmake_minimum_required(VERSION 3.28)
project(Logen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Keep Debug/Release outputs separated to avoid mixing artifacts in one folder.
foreach(cfg IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
	string(TOUPPER "${cfg}" cfg_upper)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${cfg_upper} "${CMAKE_CURRENT_SOURCE_DIR}/bin/${cfg}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${cfg_upper} "${CMAKE_CURRENT_SOURCE_DIR}/bin/${cfg}")
endforeach()

# Use the same target names across configs (no automatic "d" postfix in Debug).
set(CMAKE_DEBUG_POSTFIX "" CACHE STRING "" FORCE)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
add_subdirectory("vendor/glfw" "${CMAKE_CURRENT_BINARY_DIR}/glfw" EXCLUDE_FROM_ALL)

# Glad
add_subdirectory("vendor/glad/cmake" "${CMAKE_CURRENT_BINARY_DIR}/glad" EXCLUDE_FROM_ALL)
glad_add_library(glad REPRODUCIBLE API gl:core=4.6)

# GLM
add_subdirectory("vendor/glm" "${CMAKE_CURRENT_BINARY_DIR}/glm" EXCLUDE_FROM_ALL)

# Assimp (build from source, suitable for a git submodule or vendored copy)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
add_subdirectory("vendor/assimp" "${CMAKE_CURRENT_BINARY_DIR}/assimp" EXCLUDE_FROM_ALL)

add_subdirectory("src/core")
add_subdirectory("src/runtime")
