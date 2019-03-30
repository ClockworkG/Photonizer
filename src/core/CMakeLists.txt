add_library(libcore INTERFACE)

add_library(Photonizer::Core ALIAS libcore)

target_include_directories(libcore INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(libcore INTERFACE Photonizer::Misc
                                        Photonizer::Scene)
