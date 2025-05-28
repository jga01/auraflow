#include "auraflow/auraflow_core.h"
#include "ui/ui_manager.h" 
#include "scripting_interface/scripting_manager.h" 
#include "core/data_manager.h" 
#include "data_sources/generator_source.h" // Added include
#include <stdio.h>

int auraflow_core_init() {
    // Initialize all core subsystems:
    // - Logging
    // - Event System
    // - Data Management
    // - Plugin Manager
    // - Scripting Engine (Lua)
    // - UI Manager (Dear ImGui contexts, theming)
    // - Default data sources, processing nodes, visualizations
    data_manager_init(); 
    scripting_manager_init(); 
    ui_manager_init(); 
    generator_source_init(1.0, 10.0); // Added call with example params
    // printf("auraflow_core_init: Placeholder for core system initializations.\n");
    return 1; // Success
}

void auraflow_core_shutdown() {
    // Shutdown all core subsystems in reverse order of initialization.
    generator_source_shutdown(); // Added call
    ui_manager_shutdown(); 
    scripting_manager_shutdown(); 
    data_manager_shutdown(); 
    // printf("auraflow_core_shutdown: Placeholder for core system shutdown.\n");
}
