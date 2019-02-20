add_library(libmisc INTERFACE)

add_library(Photonizer::Misc ALIAS libmisc)

target_include_directories(libmisc INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
