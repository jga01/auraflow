#include "imgui.h"
#include "ui_manager.h"
#include "data_sources/generator_source.h" // Added include
#include "ui/visualizations/line_chart_widget.h" // Added include
#include <stdio.h> // For printf
#include <stdlib.h> // For exit

// Static variables for UI state if needed, or can query generator directly
// static float current_frequency = 1.0f; 
// static float current_amplitude = 10.0f;


void ui_manager_init() {
    printf("UI Manager Initialized.\n");
}

void ui_manager_shutdown() {
    printf("UI Manager Shutdown.\n");
}

void ui_manager_draw_main_ui() {
    // Main Menu Bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Quit")) {
                printf("Quit menu item clicked. Exiting...\n");
                // For now, we'll exit directly. A more robust solution would be an event system.
                exit(0); 
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Dashboard Area Placeholder
    ImGui::Begin("Dashboard");
    // Dashboard Area
    ImGui::Begin("Dashboard");
    // ImGui::Text("Dashboard Area - Visualizations will go here.");
    const char* stream_name = generator_source_get_stream_name();
    ImVec2 chart_size = ImGui::GetContentRegionAvail();
    if (chart_size.x < 50) chart_size.x = 50;
    if (chart_size.y < 50) chart_size.y = 50;
    line_chart_widget_draw(stream_name, chart_size);
    ImGui::End();

    // Properties Panel Placeholder
    ImGui::Begin("Properties");
    ImGui::Text("Properties Panel - Contextual information.");
    ImGui::End();

    // Call the new data controls panel
    ui_manager_draw_data_controls_panel();
}

void ui_manager_draw_data_controls_panel() {
    ImGui::Begin("Data Controls");

    // Generator Controls
    if (ImGui::Button("Start Generator")) {
        generator_source_start();
    }
    ImGui::SameLine();
    if (ImGui::Button("Stop Generator")) {
        generator_source_stop();
    }

    // Using static here to hold the value for InputDouble,
    // otherwise, it would reset every frame.
    // Ideally, these should be initialized by querying the generator_source current values.
    // For now, we'll use default values and assume they match generator_source_init.
    static double viz_frequency = 1.0; 
    if (ImGui::InputDouble("Frequency (Hz)", &viz_frequency, 0.1, 1.0, "%.2f")) {
        if (viz_frequency <= 0.0) viz_frequency = 0.01; // Prevent non-positive values if problematic
        generator_source_set_frequency(viz_frequency);
    }

    static double viz_amplitude = 10.0; 
    if (ImGui::InputDouble("Amplitude", &viz_amplitude, 0.1, 1.0, "%.2f")) {
        generator_source_set_amplitude(viz_amplitude);
    }

    ImGui::End();
}
