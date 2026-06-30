add_executable(LogenRuntime "game.cpp")
set_target_properties(LogenRuntime PROPERTIES OUTPUT_NAME "game")

# Link with the core library
target_link_libraries(LogenRuntime PRIVATE LogenCore)

# Include directories for runtime-specific headers if needed
target_include_directories(LogenRuntime PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")