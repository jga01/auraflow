cmake_minimum_required(VERSION 3.15)
project(ExampleCSVReaderPlugin C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} SHARED
    src/example_csv_reader.c
)

# Standard name for AuraFlow plugins (e.g., myplugin.afpds)
# This might vary by OS for the base shared library name.
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "") # Usually not needed for .so/.dll
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".afpds") # Custom extension

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/include" # For auraflow_plugin_api.h
    # Add other necessary include paths
)

# Ensure this plugin is built into the main project's plugin directory for easy testing
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/plugins # For local build testing
    # LIBRARY DESTINATION lib/AuraFlow/plugins # For system-wide install
)

message(STATUS "Configured ExampleCSVReaderPlugin (output: ${CMAKE_BINARY_DIR}/plugins/${PROJECT_NAME}.afpds)")
