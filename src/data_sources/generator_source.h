#ifndef GENERATOR_SOURCE_H
#define GENERATOR_SOURCE_H

#include "core/data_manager.h" // For DataStream, DataPoint

void generator_source_init(double initial_frequency, double initial_amplitude);
void generator_source_shutdown();
void generator_source_start();
void generator_source_stop();
void generator_source_update(double current_time);
void generator_source_set_frequency(double frequency);
void generator_source_set_amplitude(double amplitude);
const char* generator_source_get_stream_name();

#endif // GENERATOR_SOURCE_H
