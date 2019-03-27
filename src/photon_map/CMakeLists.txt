add_library(libphoton STATIC libphoton.cc cli.cc)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-Werror -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

set_target_properties(libphoton PROPERTIES CXX_STANDARD 17)

target_include_directories(libphoton PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(libphoton PUBLIC Photonizer::Misc
                                       Photonizer::Image
                                       Photonizer::Cli
                                       Photonizer::Raytracer
                                       Photonizer::Scene)
add_library(Photonizer::Photon ALIAS libphoton)
