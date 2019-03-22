add_library(cli11 INTERFACE)

add_library(CLI11 ALIAS cli11)

target_include_directories(cli11 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
