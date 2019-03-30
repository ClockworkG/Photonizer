if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "DEBUG" CACHE STRING "Choose the type of build: DEBUG or RELEASE" FORCE)
    message(WARNING "Not build type specified. Falling back to DEBUG.")
endif()

add_subdirectory(cli)
add_subdirectory(core)
add_subdirectory(image)
add_subdirectory(scene)
add_subdirectory(photon_map)
add_subdirectory(raytracer)

add_executable(photonizer "photonizer.cc")
target_link_libraries(photonizer
    PRIVATE Boost::program_options
            CLI11
            Spdlog
            Photonizer::Cli
            Photonizer::Scene
            Photonizer::Image
            Photonizer::Raytracer
            Photonizer::Photon)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-Werror -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode.")

target_compile_definitions(photonizer PRIVATE -DPHOTONIZER_VERSION="${PHOTONIZER_VERSION}")
target_include_directories(photonizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(photonizer PROPERTIES CXX_STANDARD 17)
