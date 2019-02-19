add_library(libscene STATIC libscene.cc)
add_library(Photonizer::Scene ALIAS libscene)

set_target_properties(libscene PROPERTIES CXX_STANDARD 17)
