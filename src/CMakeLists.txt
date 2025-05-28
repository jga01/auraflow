# Add source files for the core application
# You might want to organize sources into subdirectories (core, ui, data_pipeline, etc.)
# and use file(GLOB_RECURSE ...) or list them explicitly.

file(GLOB_RECURSE APP_MAIN_SOURCES "*.c") # Gets main.c
file(GLOB_RECURSE APP_CORE_SOURCES "core/*.c")
file(GLOB_RECURSE APP_UI_SOURCES "ui/*.c")
file(GLOB_RECURSE APP_DATAPIPELINE_SOURCES "data_pipeline/*.c")
file(GLOB_RECURSE APP_PLUGINSYSTEM_SOURCES "plugin_system/*.c")
file(GLOB_RECURSE APP_SCRIPTING_SOURCES "scripting_interface/*.c")

add_executable(AuraFlow
    ${APP_MAIN_SOURCES}
    ${APP_CORE_SOURCES}
    ${APP_UI_SOURCES}
    ${APP_DATAPIPELINE_SOURCES}
    ${APP_PLUGINSYSTEM_SOURCES}
    ${APP_SCRIPTING_SOURCES}
)

# Link libraries (example - these need to be found/built by root CMakeLists.txt)
# target_link_libraries(AuraFlow PRIVATE raylib imgui lua cjson_utils) # cjson_utils is hypothetical

# Include directories for the executable
target_include_directories(AuraFlow PUBLIC # PUBLIC so plugins_dev can see them too
    "${CMAKE_SOURCE_DIR}/include" # Main include dir for auraflow_plugin_api.h etc.
    # Add paths to Raylib, ImGui, Lua headers if not globally available
    # Example:
    # "${raylib_SOURCE_DIR}/src"
    # "${imgui_SOURCE_DIR}"
)

message(STATUS "src/CMakeLists.txt processed for AuraFlow")
