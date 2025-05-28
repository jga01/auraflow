#ifndef AURAFLOW_PLUGIN_API_H
#define AURAFLOW_PLUGIN_API_H

// =================================================================================================
// AuraFlow Plugin API v1.0 (Conceptual)
// =================================================================================================
// This file defines the C interface for creating plugins for AuraFlow.
// It should be the primary header that plugin developers include.

#include <stddef.h> // For size_t
#include <stdint.h> // For fixed-width integer types

// --- Forward Declarations ---
typedef struct AuraFlowCoreAPI AuraFlowCoreAPI; // Opaque struct providing core functions to plugins
typedef struct AuraFlowPlugin AuraFlowPlugin;   // Represents a loaded plugin instance

// --- Plugin Types ---
typedef enum {
    AURAFLOW_PLUGIN_TYPE_DATA_SOURCE,
    AURAFLOW_PLUGIN_TYPE_VISUALIZATION,
    AURAFLOW_PLUGIN_TYPE_PROCESSING_NODE,
    // AURAFLOW_PLUGIN_TYPE_GENERAL, // For plugins that don't fit neatly
} AuraFlowPluginType;

// --- Plugin Information Structure ---
// Each plugin must provide this information.
typedef struct AuraFlowPluginInfo {
    const char* name;           // e.g., "My Awesome CSV Reader"
    const char* version;        // e.g., "1.0.2"
    const char* author;         // e.g., "Jane Doe"
    const char* description;    // A brief description of the plugin
    AuraFlowPluginType type;    // The primary type of this plugin
    uint32_t api_version_major; // Major version of AuraFlow API this plugin targets (e.g., 1)
    uint32_t api_version_minor; // Minor version of AuraFlow API this plugin targets (e.g., 0)
} AuraFlowPluginInfo;

// --- Core API Functions (Example - to be expanded significantly) ---
// This struct will be filled by AuraFlow and passed to the plugin's init function.
// Plugins should NOT modify this struct.
struct AuraFlowCoreAPI {
    // Logging
    void (*log_message)(AuraFlowPlugin* plugin_instance, int level, const char* message_format, ...);

    // Data Stream Management
    // void* (*create_data_stream)(AuraFlowPlugin* plugin_instance, const char* name, /* stream properties */);
    // int (*write_to_stream)(void* stream_handle, long long timestamp, const void* data, size_t data_size);
    // void* (*get_data_stream)(const char* name);

    // Lua Scripting Interface
    // void (*register_lua_function)(AuraFlowPlugin* plugin_instance, const char* lua_namespace, const char* func_name, void* c_function_ptr);
    
    // UI Integration (e.g., for visualization plugins to get rendering context or register ImGui windows)
    // void* (*get_imgui_context)();

    // Add more functions as needed for events, configuration, etc.
    const void* reserved[32]; // For future expansion without breaking ABI for a while
};

// --- Mandatory Plugin Exported Functions ---
// Every AuraFlow plugin (shared library) MUST export these functions.
// Use `extern "C"` if compiling plugin as C++.
// Use appropriate compiler directives for exporting symbols (e.g., __declspec(dllexport) on Windows).

#if defined(_WIN32) || defined(_WIN64)
    #define AF_PLUGIN_EXPORT __declspec(dllexport)
#elif defined(__GNUC__) || defined(__clang__)
    #define AF_PLUGIN_EXPORT __attribute__((visibility("default")))
#else
    #define AF_PLUGIN_EXPORT
    #warning "AF_PLUGIN_EXPORT not defined for this compiler. Manual export configuration may be needed."
#endif

// Function to get plugin information.
// AuraFlow will call this first when discovering plugins.
AF_PLUGIN_EXPORT AuraFlowPluginInfo* af_plugin_get_info();

// Called when the plugin is loaded.
// `core_api` provides functions to interact with AuraFlow.
// `plugin_handle_out` should be set by the plugin to its internal instance/state structure.
// Return 0 on success, non-zero on failure.
AF_PLUGIN_EXPORT int af_plugin_init(const AuraFlowCoreAPI* core_api, AuraFlowPlugin** plugin_instance_out);

// Called when the plugin is about to be unloaded.
// `plugin_instance` is the handle returned by `af_plugin_init`.
// Plugin should clean up all its resources.
AF_PLUGIN_EXPORT void af_plugin_shutdown(AuraFlowPlugin* plugin_instance);

// Optional: Called periodically if the plugin needs regular updates (e.g., for animations, polling).
// AF_PLUGIN_EXPORT void af_plugin_update(AuraFlowPlugin* plugin_instance, float delta_time);


// --- Specific Plugin Type Structures & Functions (Examples - to be defined per type) ---

// For DATA_SOURCE plugins:
// typedef struct AuraFlowDataSourceVTable {
//    int (*connect)(AuraFlowPlugin* plugin_instance, const char* connection_string, void* config);
//    void (*disconnect)(AuraFlowPlugin* plugin_instance);
//    int (*read_data)(AuraFlowPlugin* plugin_instance, /* ... */); // Pushes data to core via API
//    // ...
// } AuraFlowDataSourceVTable;
// AF_PLUGIN_EXPORT const AuraFlowDataSourceVTable* af_plugin_get_data_source_vtable();

// For VISUALIZATION plugins:
// typedef struct AuraFlowVisualizationVTable {
//    void (*render)(AuraFlowPlugin* plugin_instance, void* render_target_info, const void* data_stream_accessor);
//    void (*configure_ui)(AuraFlowPlugin* plugin_instance); // For ImGui properties panel
//    // ...
// } AuraFlowVisualizationVTable;
// AF_PLUGIN_EXPORT const AuraFlowVisualizationVTable* af_plugin_get_visualization_vtable();

// For PROCESSING_NODE plugins:
// typedef struct AuraFlowProcessingNodeVTable {
//    void (*define_ports)(AuraFlowPlugin* plugin_instance, /* port registration API */);
//    int (*process)(AuraFlowPlugin* plugin_instance, /* input data, output data buffers */);
//    // ...
// } AuraFlowProcessingNodeVTable;
// AF_PLUGIN_EXPORT const AuraFlowProcessingNodeVTable* af_plugin_get_processing_node_vtable();

#endif // AURAFLOW_PLUGIN_API_H
