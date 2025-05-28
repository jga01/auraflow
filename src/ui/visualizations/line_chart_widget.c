#include "ui/visualizations/line_chart_widget.h"
#include "core/data_manager.h" // For DataStream, DataPoint, data_manager_get_stream, data_stream_get_points
#include "imgui.h"
#include <stdio.h>  // For fprintf (errors), snprintf (labels)
#include <math.h>   // For fabsf, isnan, isinf if needed
#include <float.h>  // For FLT_MAX, FLT_MIN

// If DATA_STREAM_BUFFER_SIZE is not accessible directly from data_manager.h (e.g. it's in .c)
// we might need to redefine a local maximum or pass it. For now, assume it's a known constant or define one.
#ifndef DATA_STREAM_BUFFER_SIZE 
#define LOCAL_LINE_CHART_BUFFER_SIZE 1024 
#else
#define LOCAL_LINE_CHART_BUFFER_SIZE DATA_STREAM_BUFFER_SIZE
#endif


void line_chart_widget_draw(const char* data_stream_name, ImVec2 chart_size) {
    DataStream* stream = data_manager_get_stream(data_stream_name);

    if (stream == NULL) {
        char no_stream_msg[128];
        snprintf(no_stream_msg, sizeof(no_stream_msg), "LineChart: Stream '%s' not found.", data_stream_name);
        ImGui::TextUnformatted(no_stream_msg);
        ImGui::Dummy(chart_size); // Occupy space
        return;
    }

    DataPoint points_buffer[LOCAL_LINE_CHART_BUFFER_SIZE];
    int num_points = data_stream_get_points(stream, points_buffer, LOCAL_LINE_CHART_BUFFER_SIZE);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + chart_size.x, canvas_p0.y + chart_size.y);

    // Draw background and border
    draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(30, 30, 30, 255)); // Darker background
    draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(150, 150, 150, 255)); // Lighter border

    if (num_points == 0) {
        ImGui::SetCursorScreenPos(ImVec2(canvas_p0.x + 5, canvas_p0.y + 5)); // Small padding for text
        ImGui::TextUnformatted("LineChart: No data in stream.");
        ImGui::Dummy(chart_size); // Occupy space
        return;
    }
    
    float padding = 15.0f; // Increased padding
    // Ensure chart area is not smaller than padding
    if (chart_size.x <= 2 * padding || chart_size.y <= 2 * padding) {
        ImGui::TextUnformatted("LineChart: Chart size too small.");
        ImGui::Dummy(chart_size);
        return;
    }


    // Find data range
    double min_val = FLT_MAX, max_val = -FLT_MAX;
    double min_ts = points_buffer[0].timestamp, max_ts = points_buffer[0].timestamp;

    for (int i = 0; i < num_points; ++i) {
        if (points_buffer[i].value < min_val) min_val = points_buffer[i].value;
        if (points_buffer[i].value > max_val) max_val = points_buffer[i].value;
        if (points_buffer[i].timestamp < min_ts) min_ts = points_buffer[i].timestamp;
        if (points_buffer[i].timestamp > max_ts) max_ts = points_buffer[i].timestamp;
    }

    if (min_val == max_val) { // Handle flat data for Y-axis
        min_val -= 0.5;
        max_val += 0.5;
    }
    if (max_ts == min_ts) { // Handle single point or all points at same TS for X-axis
        min_ts -= 0.5; // Display a small range around the single timestamp
        max_ts += 0.5;
    }
    
    double y_range = max_val - min_val;
    double ts_range = max_ts - min_ts;

    // Define plot area (inside padding)
    ImVec2 plot_origin = ImVec2(canvas_p0.x + padding, canvas_p0.y + padding);
    float plot_width = chart_size.x - 2 * padding;
    float plot_height = chart_size.y - 2 * padding;
    ImVec2 plot_br = ImVec2(plot_origin.x + plot_width, plot_origin.y + plot_height); // Bottom-right of plot area

    // Draw Axes
    // Y-axis line
    draw_list->AddLine(ImVec2(plot_origin.x, plot_origin.y), ImVec2(plot_origin.x, plot_br.y), IM_COL32(200, 200, 200, 255), 1.0f);
    // X-axis line
    draw_list->AddLine(ImVec2(plot_origin.x, plot_br.y), ImVec2(plot_br.x, plot_br.y), IM_COL32(200, 200, 200, 255), 1.0f);

    // Plot data points
    ImVec2 prev_screen_pos;
    for (int i = 0; i < num_points; ++i) {
        float x_ratio = (ts_range == 0) ? 0.5f : (float)((points_buffer[i].timestamp - min_ts) / ts_range);
        float y_ratio = (y_range == 0) ? 0.5f : (float)((points_buffer[i].value - min_val) / y_range);

        ImVec2 current_screen_pos = ImVec2(
            plot_origin.x + x_ratio * plot_width,
            plot_origin.y + plot_height - y_ratio * plot_height // Y is inverted in screen coords
        );
        
        // Clip points to be within the plot area
        current_screen_pos.x = ImClamp(current_screen_pos.x, plot_origin.x, plot_br.x);
        current_screen_pos.y = ImClamp(current_screen_pos.y, plot_origin.y, plot_br.y);

        if (i > 0) {
            draw_list->AddLine(prev_screen_pos, current_screen_pos, IM_COL32(0, 255, 0, 255), 1.5f);
        }
        prev_screen_pos = current_screen_pos;
        // Optionally draw a small circle at each point
        // draw_list->AddCircleFilled(current_screen_pos, 2.0f, IM_COL32(0, 255, 0, 255));
    }

    // Optional: Add labels for min/max values on axes
    char label_buffer[64];
    snprintf(label_buffer, sizeof(label_buffer), "%.2f", max_val);
    draw_list->AddText(ImVec2(plot_origin.x + 5, plot_origin.y), IM_COL32(200, 200, 200, 255), label_buffer);
    snprintf(label_buffer, sizeof(label_buffer), "%.2f", min_val);
    draw_list->AddText(ImVec2(plot_origin.x + 5, plot_br.y - ImGui::GetTextLineHeight()), IM_COL32(200, 200, 200, 255), label_buffer);

    snprintf(label_buffer, sizeof(label_buffer), "%.1fs", min_ts);
    draw_list->AddText(ImVec2(plot_origin.x, plot_br.y + 5), IM_COL32(200, 200, 200, 255), label_buffer);
    snprintf(label_buffer, sizeof(label_buffer), "%.1fs", max_ts);
    ImVec2 max_ts_label_size = ImGui::CalcTextSize(label_buffer);
    draw_list->AddText(ImVec2(plot_br.x - max_ts_label_size.x, plot_br.y + 5), IM_COL32(200, 200, 200, 255), label_buffer);

    // Advance cursor
    ImGui::Dummy(chart_size);
}
