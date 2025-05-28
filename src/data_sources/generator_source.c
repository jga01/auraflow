#define _USE_MATH_DEFINES // For M_PI on MSVC, or ensure it's available
#include "data_sources/generator_source.h" // Corrected path
#include "core/data_manager.h"
#include <stdio.h>
#include <math.h> // For sin and M_PI
#include <stdbool.h> // For bool type

// Define static variables for generator state
static bool is_active = false;
static double frequency = 1.0; // Hz
static double amplitude = 1.0;
static DataStream* data_stream = NULL;
static const char* stream_name = "generated_sine_wave";
// static double internal_time_accumulator = 0.0; // Not used if current_time is passed in update

void generator_source_init(double initial_frequency, double initial_amplitude) {
    frequency = initial_frequency;
    amplitude = initial_amplitude;
    
    data_stream = data_manager_create_stream(stream_name);
    if (data_stream == NULL) {
        fprintf(stderr, "Error: Failed to create data stream for generator source '%s'.\n", stream_name);
        // Depending on error policy, could set a flag or handle more robustly
    }
    
    is_active = false; // Default to not active until started
    printf("Data Generator Initialized (Frequency: %.2f Hz, Amplitude: %.2f).\n", frequency, amplitude);
}

void generator_source_shutdown() {
    printf("Data Generator Shutdown.\n");
    // data_stream is owned and managed by data_manager, so no explicit cleanup here
    // is_active = false; // Reset state if necessary
}

void generator_source_start() {
    if (data_stream == NULL) {
        fprintf(stderr, "Cannot start generator: data stream '%s' is not available.\n", stream_name);
        return;
    }
    is_active = true;
    printf("Data Generator Started for stream '%s'.\n", stream_name);
}

void generator_source_stop() {
    is_active = false;
    printf("Data Generator Stopped for stream '%s'.\n", stream_name);
}

void generator_source_update(double current_time) {
    if (!is_active || data_stream == NULL) {
        return;
    }

    DataPoint point;
    point.timestamp = current_time;
    point.value = amplitude * sin(2.0 * M_PI * frequency * current_time);
    
    if (!data_stream_add_point(data_stream, point)) {
        fprintf(stderr, "Error adding point to stream '%s' from generator.\n", stream_name);
    }
    // printf("Generated point for stream '%s': T=%.2f, V=%.2f\n", stream_name, point.timestamp, point.value);
}

void generator_source_set_frequency(double new_frequency) {
    if (new_frequency > 0) { // Basic validation
        frequency = new_frequency;
        printf("Generator frequency set to %.2f Hz.\n", frequency);
    } else {
        fprintf(stderr, "Warning: Invalid frequency %.2f Hz. Must be positive.\n", new_frequency);
    }
}

void generator_source_set_amplitude(double new_amplitude) {
    amplitude = new_amplitude;
    printf("Generator amplitude set to %.2f.\n", amplitude);
}

const char* generator_source_get_stream_name() {
    return stream_name;
}
