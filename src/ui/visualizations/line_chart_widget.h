#ifndef LINE_CHART_WIDGET_H
#define LINE_CHART_WIDGET_H

#include "imgui.h"

// Function to draw a line chart for a given data stream
// data_stream_name: The name of the data stream to fetch and visualize
// chart_size: The desired size of the chart widget (width, height)
void line_chart_widget_draw(const char* data_stream_name, ImVec2 chart_size);

#endif // LINE_CHART_WIDGET_H
