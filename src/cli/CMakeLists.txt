add_library(libcli STATIC photonizer-command.cc photonizer-cli.cc)
add_library(Photonizer::Cli ALIAS libcli)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-Werror -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

set_target_properties(libcli PROPERTIES CXX_STANDARD 17)
target_include_directories(libcli PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(libcli PUBLIC Photonizer::Scene
                                          Spdlog
                                          CLI11)
