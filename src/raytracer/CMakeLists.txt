add_library(libraytracer STATIC ray-tracer.cc cli.cc density-tracer.cc)
add_library(Photonizer::Raytracer ALIAS libraytracer)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-Werror -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

set_target_properties(libraytracer PROPERTIES CXX_STANDARD 17)
target_include_directories(libraytracer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(libraytracer PUBLIC Photonizer::Scene
                                          Spdlog
                                          Photonizer::Photon
                                          Photonizer::Core
                                          Photonizer::Image)
