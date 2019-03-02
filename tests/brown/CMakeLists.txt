add_executable(brown)
target_sources(brown PRIVATE main.cc)
target_link_libraries(brown Photonizer::Photon)
set_target_properties(brown PROPERTIES CXX_STANDARD 17)
