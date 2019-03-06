add_library(libscene STATIC libscene.cc
                            mesh.cc
                            detail/scene-builder.cc)
add_library(Photonizer::Scene ALIAS libscene)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-Werror -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set_target_properties(libscene PROPERTIES CXX_STANDARD 17)
target_include_directories(libscene PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(libscene PUBLIC Photonizer::Misc
                                      gsl
                                      pthread
                                      stdc++fs
                                      tinyobjloader)
