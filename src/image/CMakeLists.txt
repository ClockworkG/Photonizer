add_library(libimage INTERFACE)

add_library(Photonizer::Image ALIAS libimage)

target_link_libraries(libimage INTERFACE Photonizer::Misc)
