add_library(math INTERFACE)
target_sources(math INTERFACE "math.hh")
target_include_directories(math INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
