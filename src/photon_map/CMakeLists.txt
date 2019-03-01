add_library(libphoton INTERFACE)
target_include_directories(libphoton INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(libphoton INTERFACE Photonizer::Misc)
add_library(Photonizer::Photon ALIAS libphoton)
