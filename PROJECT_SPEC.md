# AuraFlow: Project Specification
**Version:** 1.0
**Date:** May 27, 2025
**Author/Lead:** Tiago Goossen de Andrade

## 1. Introduction & Vision

### 1.1. Project Name
AuraFlow

### 1.2. Tagline/Mission
**AuraFlow: Illuminate Your Data.**
To provide a highly performant, visually elegant, and deeply extensible C-based application for real-time data visualization and complex analysis, empowering users to effortlessly derive insights from dynamic datasets.

### 1.3. Core Problem Addressed
Existing data visualization and analysis tools often present a trade-off:
*   **High Performance vs. Ease of Use/Customization:** Tools offering raw speed might lack user-friendly interfaces or deep extensibility.
*   **Off-the-Shelf vs. Specific Needs:** Generic tools may not cater to specialized data sources, unique visualization requirements, or complex domain-specific processing logic.
*   **Bloat vs. Lightweight:** Many comprehensive tools come with significant overhead, while lightweight tools may lack advanced features.

AuraFlow aims to bridge these gaps by offering a C-powered core for efficiency, combined with modular plugins and a flexible scripting layer for unparalleled customization and adaptability.

### 1.4. Target Audience
*   **Scientists & Researchers:** For visualizing experimental data, sensor outputs, and simulation results.
*   **Engineers (Software, Hardware, Industrial):** For monitoring system performance, analyzing logs, and visualizing IoT data streams.
*   **Data Analysts & Financial Professionals:** For tracking market data, exploring trends, and building custom dashboards.
*   **Hobbyists & Makers:** For personal projects involving data acquisition and visualization.
*   **Educators & Students:** As a tool for learning data analysis and visualization principles.

### 1.5. Guiding Principles
AuraFlow will be designed and developed adhering to the following principles:
*   **Beautiful & Elegant:** Aesthetically pleasing, intuitive, and uncluttered user interface that enhances the user's focus on data.
*   **Complex & Powerful:** Capable of handling sophisticated data processing tasks and diverse visualization needs.
*   **Modular:** Core functionality extendable through a well-defined plugin architecture.
*   **Scriptable:** Deep integration with Lua for automation, customization, and rapid prototyping.
*   **Efficient:** Leveraging C and optimized graphics rendering for high performance and low latency, even with large or high-frequency datasets.

## 2. Core Functionality

### 2.1. Data Ingestion & Sources
The system must be able to ingest data from various origins.

*   **2.1.1. Built-in Data Sources:**
    *   CSV/TSV file reader (static and watching for updates).
    *   Basic TCP/UDP socket listener (for simple streaming data).
    *   Data generator (e.g., sine wave, random noise for testing).
*   **2.1.2. Plugin-based Data Source Extension:**
    *   A defined C API allowing developers to create plugins for new data sources (e.g., specific database connectors, message queues like MQTT/Kafka, hardware interfaces, web APIs).
    *   Plugins will handle connection, data parsing, and streaming data into AuraFlow's internal data bus.

### 2.2. Data Visualization
The system must provide rich and interactive ways to visualize data.

*   **2.2.1. Built-in Visualization Widgets:**
    *   **Line Chart:** Time series, X-Y plots. Multiple series, configurable axes, legends.
    *   **Scatter Plot:** Correlation analysis, point distributions.
    *   **Bar Chart:** Categorical data comparison.
    *   **Heatmap/Spectrogram:** 2D density plots, frequency-time analysis.
    *   **Numeric Display:** Single value, gauges.
    *   **Text Log/Table:** Display raw or processed textual/tabular data.
*   **2.2.2. Interactive Features:**
    *   Zooming (mouse wheel, pinch-to-zoom where applicable).
    *   Panning (mouse drag).
    *   Data point selection and tooltips displaying detailed information.
    *   Dynamic filtering controls linked to visualizations.
    *   Time-window selection for time-series data.
*   **2.2.3. Plugin-based Visualization Extension:**
    *   A defined C API for creating custom visualization widgets. Plugins will receive data streams and use Raylib/OpenGL for custom rendering within their allocated UI space.
    *   Examples: 3D point clouds, custom scientific plots, network graphs.
*   **2.2.4. Custom 2D/3D Rendering Capabilities:**
    *   The underlying graphics engine (Raylib/OpenGL) should be accessible for advanced custom visualizations, either directly or through the plugin API.

### 2.3. Data Processing Pipeline
The system must allow users to transform, analyze, and derive new data streams from existing ones.

*   **2.3.1. Node-based Editor for Pipeline Construction:**
    *   A visual interface (similar to Blender's shader nodes or Unreal Engine's Blueprints) where users can drag, drop, and connect processing nodes.
    *   Nodes represent individual processing steps (inputs, outputs, parameters).
    *   Connections represent data flow between nodes.
*   **2.3.2. Built-in Processing Nodes:**
    *   **Filters:** Moving Average, Low-pass, High-pass, Kalman (basic).
    *   **Mathematical Operations:** Scale, Offset, Abs, Log, Pow, Trigonometric functions, Vector math.
    *   **Statistical Analysis:** Min, Max, Mean, Standard Deviation, Variance, Histogram.
    *   **Transformations:** FFT, IFFT.
    *   **Logic:** Thresholding, Comparison, Boolean operators.
    *   **Data Manipulation:** Resampling, Decimation, Channel Splitter/Merger.
*   **2.3.3. Plugin-based Processing Node Extension:**
    *   A defined C API for creating new processing nodes. Plugins will define inputs, outputs, parameters, and a C function to execute the processing logic.
*   **2.3.4. Real-time Execution and Feedback:**
    *   The pipeline should execute in real-time (or near real-time) as new data arrives.
    *   Visual feedback on data flowing through nodes (e.g., animated connections, mini-previews on nodes).

### 2.4. Project Management
*   **2.4.1. Saving/Loading Workspaces:**
    *   Save and load entire AuraFlow sessions, including dashboard layouts, active data sources, configured processing pipelines, and script states.
    *   Format: Likely JSON or a custom structured text format.
*   **2.4.2. Import/Export Configurations:**
    *   Allow exporting/importing individual component configurations (e.g., a specific data source setup, a processing pipeline).

## 3. Architectural Design

### 3.1. Core Engine (C)
The heart of AuraFlow, written in C for performance and control.

*   **3.1.1. Main Application Loop:** Manages timing, input processing, UI updates, data processing, and rendering.
*   **3.1.2. Event System:** A lightweight event bus for inter-module communication (e.g., new data available, UI interaction, plugin events).
*   **3.1.3. Data Management Structures:**
    *   Efficient data buffers for time-series data (e.g., ring buffers).
    *   Central data bus or registry for named data streams.
    *   Mechanisms for data type handling and conversion.
*   **3.1.4. Performance Considerations:**
    *   Minimize memory allocations/deallocations in critical paths.
    *   Optimize data copying.
    *   Potential for multi-threading for data acquisition and processing (carefully managed to avoid race conditions).

### 3.2. UI Layer
Responsible for presenting information to and interacting with the user.

*   **3.2.1. Technology:**
    *   **Raylib:** For window creation, input handling, OpenGL context management, and custom 2D/3D rendering for visualizations.
    *   **Dear ImGui:** For building the majority of the UI widgets (panels, buttons, menus, node editor). Runs on top of Raylib's backend.
*   **3.2.2. UI Design Philosophy:**
    *   **Clean & Uncluttered:** Prioritize data visibility and ease of use.
    *   **Intuitive:** Consistent interaction patterns, clear visual hierarchy.
    *   **Responsive:** Fast feedback to user actions.
    *   **Dockable & Resizable Panels:** Allow users to customize their workspace layout.
*   **3.2.3. Theming System:**
    *   Allow users to customize colors, fonts, and widget styles.
    *   Themes definable via configuration files (e.g., JSON) or potentially scriptable.

### 3.3. Modularity: Plugin System
Extends AuraFlow's core capabilities.

*   **3.3.1. Plugin Types:**
    *   **Data Source Plugins (`.afpds`):** For new data input methods.
    *   **Visualization Plugins (`.afpvz`):** For new chart types or custom graphical displays.
    *   **Processing Node Plugins (`.afppn`):** For new data transformation/analysis algorithms.
*   **3.3.2. Plugin API (C-based):**
    *   Well-defined C header files (`auraflow_plugin_api.h` or similar per type).
    *   API will provide functions for plugins to register themselves, define their properties, receive data/events, and interact with the core system (e.g., drawing, accessing data streams).
    *   API will also include functions for plugins to expose their own functionalities to the scripting layer.
*   **3.3.3. Plugin Loading and Management:**
    *   Dynamic loading of shared libraries (`.dll`, `.so`, `.dylib`) from a designated `plugins/` directory.
    *   Core system manages plugin discovery, loading, initialization, and unloading.
*   **3.3.4. Plugin Lifecycle:**
    *   `init()`: Called when the plugin is loaded. Registers functionality, sets up resources, exposes functions to Lua.
    *   `update()`/`process()`: Called per frame or per data event, as appropriate for the plugin type.
    *   `shutdown()`: Called when the plugin is unloaded. Cleans up resources.

### 3.4. Scriptability: Lua Integration
Provides flexibility, automation, and user customization.

*   **3.4.1. Embedded Lua Engine:**
    *   A standard Lua (e.g., 5.4) interpreter will be embedded within AuraFlow.
*   **3.4.2. Lua API Design (`auraflow.` namespace):**
    *   **Access to Core Application Functions:**
        *   `auraflow.core.log(message, level)`
        *   `auraflow.core.get_data_stream(name)`
        *   `auraflow.core.create_data_stream(name)`
        *   `auraflow.core.sleep(seconds)`
    *   **Access to Plugin-Exposed Functions:** Plugins will register their functions under their own Lua tables (e.g., `auraflow.plugins.my_csv_reader.open_file()`).
    *   **UI Manipulation Capabilities:**
        *   `auraflow.ui.create_widget(type, properties)`
        *   `auraflow.ui.get_widget_by_name(name)`
        *   `auraflow.ui.set_property(widget_id, property_name, value)`
        *   `auraflow.ui.register_event_handler(widget_id, event_name, lua_function)`
        *   `auraflow.ui.show_notification(title, message, type)`
    *   **Data Stream Interaction:**
        *   `stream:write(timestamp, value_or_table)`
        *   `stream:on_new_data(lua_function(timestamp, value_or_table))`
    *   **Event Handling:**
        *   `auraflow.events.subscribe(event_name, lua_function)`
        *   `auraflow.events.publish(event_name, event_data_table)`
*   **3.4.3. Script Management:**
    *   Ability to load and run Lua scripts from files.
    *   An integrated simple text editor/console for writing and testing scripts.
    *   Scripts can be configured to run at startup or triggered by events/UI actions.

### 3.5. Layered Interaction (Core <-> Plugins <-> Scripting)
A synergistic relationship:
1.  **Core Engine** provides fundamental services and manages plugins and the scripting engine.
2.  **Plugins (C/C++)** extend core functionalities, offering specialized, high-performance modules.
    *   Plugins register their capabilities with the Core.
    *   Plugins **also expose a C API that is then bound to the Lua scripting environment** by the plugin itself or by the core's plugin manager during plugin initialization.
3.  **Scripting Layer (Lua)** acts as a flexible "glue" and customization layer.
    *   Scripts can call Core API functions.
    *   Scripts can call functions exposed by C Plugins.
    *   Scripts can orchestrate interactions between different plugins and core features.
    *   Scripts can define custom UI elements or behaviors that leverage both core and plugin functionalities.

## 4. Technical Specifications

### 4.1. Programming Language
*   Core Application & Plugins: **C (C11/C17 standard)**. Focus on clarity, performance, and portability.
*   Scripting: **Lua (e.g., 5.4)**.

### 4.2. Key Libraries
*   **Windowing, Input, Graphics Backend:** [Raylib](https://www.raylib.com/) (primary choice).
    *   *(Alternative for consideration: SDL2 for windowing/input, with direct OpenGL for rendering)*
*   **Immediate Mode GUI:** [Dear ImGui](https://github.com/ocornut/imgui).
*   **Scripting Engine:** Lua official distribution or a variant like LuaJIT if extreme script performance is needed (evaluate later).
*   **Configuration/Serialization:** A lightweight JSON library for C (e.g., cJSON, JSMN).
*   **Utility:** Standard C libraries, potentially stb_image for basic image loading (e.g., for UI icons, texture-based visualizations).

### 4.3. Build System
*   **CMake (version 3.15 or higher):** For cross-platform build configuration.

### 4.4. Target Platforms
*   **Primary:** Windows 10/11 (64-bit), Linux (e.g., Ubuntu 20.04+ LTS, 64-bit).
*   **Secondary/Future:** macOS (64-bit).
    Initial development may focus on one platform, with portability tested regularly.

### 4.5. Version Control
*   **Git.** Hosted on a platform like GitHub, GitLab, or self-hosted.

## 5. User Experience (UX) and Interface (UI) Design

### 5.1. Overall Aesthetics
*   **Elegant & Modern:** Clean lines, good typography, thoughtful use of color. Avoid visual clutter.
*   **Professional:** Suitable for scientific and engineering contexts.
*   **Dark Theme as Default:** Common in developer/technical tools, often easier on the eyes for long sessions. Light theme option available.

### 5.2. Key UI Components (Conceptual Layout)
*   **Main Menu Bar:** File, Edit, View, Tools, Plugins, Scripts, Help.
*   **Toolbar:** Quick access to common actions (e.g., New Project, Open, Save, Add Widget).
*   **Dashboard Area:** Main workspace where visualization widgets are placed.
    *   Support for grid-based or free-form draggable/resizable widget placement.
    *   Multiple tabs or pages for different dashboard layouts.
*   **Data Source Panel:** Lists available and active data sources. Allows configuration and management.
*   **Visualization Palette/Library Panel:** Lists available built-in and plugin visualization widgets for drag-and-drop onto the dashboard.
*   **Processing Node Editor Panel:** A dedicated canvas for constructing and editing data processing pipelines.
*   **Properties/Configuration Panel:** Context-sensitive, displays and allows editing of properties for the selected item (widget, data source, processing node).
*   **Script Editor/Console Panel:**
    *   Simple text editor with Lua syntax highlighting.
    *   Console for output (print statements, errors) and interactive Lua commands.
*   **Status Bar:** Displays application status messages, current data rates, warnings.

### 5.3. Interaction Design
*   **Drag-and-Drop:** For adding widgets to the dashboard, connecting nodes in the pipeline.
*   **Context Menus (Right-Click):** For quick access to actions relevant to the clicked item.
*   **Keyboard Shortcuts:** For common actions.
*   **Undo/Redo:** For critical actions like widget placement/deletion, node graph changes.

### 5.4. Responsiveness and Feedback
*   UI should remain responsive even when processing large amounts of data (achieved by offloading heavy work from the UI thread where possible).
*   Clear visual feedback for user actions (e.g., hover states, selection highlights, progress indicators).

## 6. Non-Functional Requirements

### 6.1. Performance
*   **Low Latency:** Aim for sub-100ms updates for visualizations from incoming data for "real-time" feel. Lower for high-frequency data.
*   **Efficient Rendering:** Smooth animations and interactions, targeting 60 FPS for the UI.
*   **Memory Management:** Minimize footprint, avoid memory leaks. Efficient handling of large data buffers.
*   **Scalability:** Should handle a reasonable number of data streams, visualizations, and processing nodes concurrently without significant degradation. (Define "reasonable" with benchmarks later).

### 6.2. Stability
*   Robust error handling for core systems, plugins, and scripts.
*   Graceful degradation if a non-critical component fails (e.g., a script error shouldn't crash the app).
*   Crash reporting/logging mechanisms (optional, for later stages).

### 6.3. Extensibility
*   Plugin and Scripting APIs should be well-documented and easy to use for third-party developers.
*   Design for future expansion of core features.

### 6.4. Maintainability
*   Clean, well-commented C code.
*   Modular architecture with clear separation of concerns.
*   Comprehensive internal documentation for developers.
*   Unit tests and integration tests for critical components.

### 6.5. Usability
*   Easy to learn for basic data visualization tasks.
*   Steeper learning curve acceptable for advanced features (processing pipeline, scripting), but with good documentation and examples.
*   Comprehensive user documentation (manuals, tutorials).

### 6.6. Security (Basic Considerations)
*   **Scripting Sandbox:** Lua's sandboxing capabilities should be explored to limit script access to sensitive system resources (e.g., arbitrary file system access outside designated areas).
*   **Plugin Validation:** Basic checks on plugin metadata. (Full code signing/sandboxing for C plugins is complex and likely out of scope for initial versions but consider for future).

## 7. Development Roadmap & Milestones (High-Level)

*   **Phase 0: Foundation & Prototyping (1-2 Months)**
    *   Setup project structure, build system (CMake), version control.
    *   Integrate Raylib for windowing and basic rendering.
    *   Integrate Dear ImGui for a basic UI shell (menu, empty panels).
    *   Embed Lua engine and test basic C-to-Lua and Lua-to-C calls.
    *   *Goal: A running application window with a minimal UI and working scripting.*
*   **Phase 1: Core Data Path & Basic Visualization (2-3 Months)**
    *   Implement core data stream management (data bus, basic buffer structures).
    *   Develop a simple built-in data source (e.g., CSV reader or data generator).
    *   Develop a basic built-in visualization widget (e.g., Line Chart) displaying data from the source.
    *   Basic UI for adding/configuring the source and visualizer.
    *   *Goal: Visualize data from a simple source in real-time.*
*   **Phase 2: Plugin System - Proof of Concept (2 Months)**
    *   Define initial C API for one plugin type (e.g., Data Source).
    *   Implement plugin loading/management system.
    *   Develop a simple example Data Source plugin.
    *   Ensure plugin can register itself and feed data into the core system.
    *   *Goal: Successfully load and run an external C plugin.*
*   **Phase 3: Scripting API - Core Integration (2 Months)**
    *   Expose core application functions (logging, basic UI manipulation, data stream access) to Lua.
    *   Allow Lua scripts to control the basic data source and visualization from Phase 1.
    *   Develop a simple script editor/console panel in the UI.
    *   *Goal: Control core app behavior and basic data flow using Lua scripts.*
*   **Phase 4: Processing Pipeline - Basics (3 Months)**
    *   Design and implement the node-based UI editor.
    *   Develop a few built-in processing nodes (e.g., Math Op, Filter).
    *   Implement the data flow execution logic for the pipeline.
    *   Integrate pipeline output with visualization widgets.
    *   *Goal: Visually construct and run a simple data processing chain.*
*   **Phase 5: Expansion & Polish (Ongoing)**
    *   Implement more built-in data sources, visualizations, processing nodes.
    *   Refine plugin APIs for all types and enable Lua exposure from plugins.
    *   Develop the theming system.
    *   Improve UI/UX based on testing and feedback.
    *   Add project saving/loading.
*   **Phase 6: Documentation & Testing (Ongoing, with dedicated pushes)**
    *   User manual, Plugin developer guide, Scripting API reference.
    *   Unit tests, integration tests, user acceptance testing.
*   **Phase 7: Alpha/Beta Release (Target: End of Year 1 / Start of Year 2, ambitious)**
    *   Feature-freeze for a stable release.
    *   Gather community feedback.

## 8. Future Considerations / Potential Enhancements (Post V1.0)
*   Headless mode for server-side processing/report generation.
*   Advanced networking protocol support (MQTT, OPC-UA, Kafka via plugins).
*   Basic Machine Learning model inference nodes (e.g., ONNX runtime integration).
*   Cloud data source integration.
*   Collaboration features (shared dashboards, remote data access - complex).
*   Advanced 3D visualization capabilities.
*   More sophisticated security models for plugins and scripts.
*   Package manager or online repository for community plugins/scripts.

---