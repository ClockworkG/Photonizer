add_library(libimage INTERFACE)

add_library(Photonizer::Image ALIAS libimage)

target_include_directories(libimage INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(libimage INTERFACE Photonizer::Misc)
