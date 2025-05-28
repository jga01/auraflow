# This CMakeLists.txt is included if AURKAFLOW_ENABLE_TESTS is ON in the root CMakeLists.txt

# CTest module is already included by root if tests are enabled.
# include(CTest)

# Example: Add a unit test executable
# add_executable(core_utils_tests unit/test_core_utils.c ${CMAKE_SOURCE_DIR}/src/core/utils.c) # Assuming utils.c exists
# target_link_libraries(core_utils_tests PRIVATE AuraFlow) # Link against your main app if needed, or specific components
# add_test(NAME CoreUtilsTest COMMAND core_utils_tests)

# Example: Add an integration test
# add_executable(pipeline_simple_tests integration/test_pipeline_simple.c)
# target_link_libraries(pipeline_simple_tests PRIVATE AuraFlow)
# add_test(NAME PipelineSimpleTest COMMAND pipeline_simple_tests)

message(STATUS "tests/CMakeLists.txt processed. Add your test targets here.")
