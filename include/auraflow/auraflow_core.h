#ifndef AURAFLOW_CORE_H
#define AURAFLOW_CORE_H

// This is an internal header for AuraFlow's core components.
// It might include common types, enums, or forward declarations used across the core.

// Example: Log levels
typedef enum {
    AURAFLOW_LOG_DEBUG,
    AURAFLOW_LOG_INFO,
    AURAFLOW_LOG_WARNING,
    AURAFLOW_LOG_ERROR,
    AURAFLOW_LOG_CRITICAL
} AuraFlowLogLevel;

// --- Core Lifecycle Functions (implemented in src/core/auraflow_core.c) ---
// These would be called by main.c

/**
 * @brief Initializes all core AuraFlow subsystems.
 * @return 1 on success, 0 on failure.
 */
int auraflow_core_init();

/**
 * @brief Shuts down all core AuraFlow subsystems and releases resources.
 */
void auraflow_core_shutdown();


// Add other core-specific declarations here.
// For example, handles to core systems if needed by other core modules.

#endif // AURAFLOW_CORE_H
