if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "DEBUG" CACHE STRING "Choose the type of build: DEBUG or RELEASE" FORCE)
    message(WARNING "Not build type specified. Falling back to DEBUG.")
endif()

add_subdirectory(scene)

add_executable(photonizer "photonizer.cc")
target_link_libraries(photonizer
    PRIVATE Boost::program_options
            tinyobjloader
            Photonizer::Scene
            gsl
            Photonizer::Misc)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-Werror -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode.")

target_compile_definitions(photonizer PRIVATE -DPHOTONIZER_VERSION="${RAYTRACER_VERSION}")
set_target_properties(photonizer PROPERTIES CXX_STANDARD 17)
