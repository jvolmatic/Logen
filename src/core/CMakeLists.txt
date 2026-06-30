# Collect all core source files
file(GLOB_RECURSE LOGEN_CORE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/graphics/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/graphics/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/io/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/io/*.h"
)

add_library(LogenCore SHARED ${LOGEN_CORE_SOURCES}
        Camera.cpp
        Camera.h)

# Set the output name to "logen" (produces logen.dll on Windows)
set_target_properties(LogenCore PROPERTIES
        OUTPUT_NAME "logen"
        PREFIX ""  # Removes the "lib" prefix on MinGW/Linux
)

# Define export macro for DLL symbol visibility
target_compile_definitions(LogenCore PRIVATE LOGEN_CORE_EXPORTS)
target_compile_definitions(LogenCore PUBLIC LOGEN_CORE_DLL)

# Include directories - make core headers available
target_include_directories(LogenCore
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.."  # So consumers can use #include "core/..."
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Link dependencies
target_link_libraries(LogenCore
        PUBLIC
        glm::glm
        glad
        glfw
        PRIVATE
        assimp
)

# Copy the built Assimp runtime library next to the engine output when Assimp
# is built as a shared library.
add_custom_command(TARGET LogenCore POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:assimp>"
        "$<TARGET_FILE_DIR:LogenCore>"
)