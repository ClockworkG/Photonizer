add_library(spdlog INTERFACE)

add_library(Spdlog ALIAS spdlog)

target_include_directories(spdlog INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
