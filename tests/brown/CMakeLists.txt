add_executable(brown main.cc)
target_link_libraries(brown Photonizer::Photon pthread)
set_target_properties(brown PROPERTIES CXX_STANDARD 17)
