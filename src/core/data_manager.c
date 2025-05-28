#include "core/data_manager.h" // Corrected path
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For NULL

#define MAX_DATA_STREAMS 16
static DataStream streams[MAX_DATA_STREAMS];
static int num_streams = 0;
// Mutex for streams array and num_streams would be added here for thread safety

void data_manager_init() {
    num_streams = 0;
    memset(streams, 0, sizeof(streams)); // Clear the streams array
    printf("Data Manager Initialized.\n");
}

void data_manager_shutdown() {
    printf("Data Manager Shutdown.\n");
    // Potentially free any dynamically allocated resources within streams if any were added
}

DataStream* data_manager_create_stream(const char* stream_name) {
    if (num_streams >= MAX_DATA_STREAMS) {
        fprintf(stderr, "Error: Maximum number of data streams reached (%d).\n", MAX_DATA_STREAMS);
        return NULL;
    }

    for (int i = 0; i < num_streams; ++i) {
        if (strcmp(streams[i].name, stream_name) == 0) {
            fprintf(stderr, "Error: Data stream with name '%s' already exists.\n", stream_name);
            return &streams[i]; // Return existing stream if name matches
        }
    }

    DataStream* new_stream = &streams[num_streams];
    strncpy(new_stream->name, stream_name, sizeof(new_stream->name) - 1);
    new_stream->name[sizeof(new_stream->name) - 1] = '\0'; // Ensure null termination
    new_stream->head = -1; 
    new_stream->count = 0;
    
    num_streams++;
    printf("Data stream '%s' created.\n", stream_name);
    return new_stream;
}

DataStream* data_manager_get_stream(const char* stream_name) {
    for (int i = 0; i < num_streams; ++i) {
        if (strcmp(streams[i].name, stream_name) == 0) {
            return &streams[i];
        }
    }
    // fprintf(stderr, "Warning: Data stream with name '%s' not found.\n", stream_name);
    return NULL;
}

bool data_stream_add_point(DataStream* stream, DataPoint point) {
    if (stream == NULL) {
        fprintf(stderr, "Error: Attempted to add point to a NULL stream.\n");
        return false;
    }

    stream->head = (stream->head + 1) % DATA_STREAM_BUFFER_SIZE;
    stream->buffer[stream->head] = point;

    if (stream->count < DATA_STREAM_BUFFER_SIZE) {
        stream->count++;
    }
    // Optional: printf for debugging
    // printf("Added point to stream '%s': T=%.2f, V=%.2f (Head: %d, Count: %d)\n", 
    //        stream->name, point.timestamp, point.value, stream->head, stream->count);
    return true;
}

// Gets the N latest points from the stream.
int data_stream_get_points(DataStream* stream, DataPoint* out_buffer, int max_points_to_get) {
    if (stream == NULL || out_buffer == NULL || max_points_to_get <= 0) {
        return 0;
    }

    int points_available = stream->count;
    int points_to_copy = (max_points_to_get < points_available) ? max_points_to_get : points_available;

    if (points_to_copy == 0) {
        return 0;
    }

    // Copy the latest 'points_to_copy' points.
    // The latest point is at stream->head.
    // The Nth latest point is at (stream->head - N + 1 + DATA_STREAM_BUFFER_SIZE) % DATA_STREAM_BUFFER_SIZE
    for (int i = 0; i < points_to_copy; ++i) {
        int source_idx = (stream->head - (points_to_copy - 1) + i + DATA_STREAM_BUFFER_SIZE) % DATA_STREAM_BUFFER_SIZE;
        out_buffer[i] = stream->buffer[source_idx];
    }
    
    return points_to_copy;
}
