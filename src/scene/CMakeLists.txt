add_library(libscene STATIC libscene.cc
                            detail/scene-builder.cc)
add_library(Photonizer::Scene ALIAS libscene)

set_target_properties(libscene PROPERTIES CXX_STANDARD 17)
target_include_directories(libscene PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
