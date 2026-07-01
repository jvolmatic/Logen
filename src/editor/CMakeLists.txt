add_executable(LogenRuntime "editor.cpp"
		EditorInput.cpp
		EditorInput.h)
set_target_properties(LogenRuntime PROPERTIES OUTPUT_NAME "game")

add_custom_command(TARGET LogenRuntime POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_SOURCE_DIR}/resources"
		"$<TARGET_FILE_DIR:LogenRuntime>/resources"
)

# Link with the core library
target_link_libraries(LogenRuntime PRIVATE LogenCore)

# Include directories for runtime-specific headers if needed
target_include_directories(LogenRuntime PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")