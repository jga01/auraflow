#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <stdint.h>
#include <stdbool.h>

// Define DataPoint structure
typedef struct {
    double timestamp; // Or use a more precise time type if available
    double value;     // Assuming single double value for now, can be union/flexible later
} DataPoint;

// Define DataStream structure
#define DATA_STREAM_BUFFER_SIZE 1024 // Example size, make configurable later if needed
typedef struct {
    char name[256]; // Name of the data stream
    DataPoint buffer[DATA_STREAM_BUFFER_SIZE];
    int head;        // Index of the last inserted element
    int count;       // Number of elements currently in the buffer
    // Add mutex for thread safety later if needed
} DataStream;

// Declare Data Manager functions
void data_manager_init();
void data_manager_shutdown();
DataStream* data_manager_create_stream(const char* stream_name);
DataStream* data_manager_get_stream(const char* stream_name);
bool data_stream_add_point(DataStream* stream, DataPoint point);
int data_stream_get_points(DataStream* stream, DataPoint* out_buffer, int max_points);

#endif // DATA_MANAGER_H
