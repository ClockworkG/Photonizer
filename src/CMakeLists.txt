if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "DEBUG" CACHE STRING "Choose the type of build: DEBUG or RELEASE" FORCE)
    message(WARNING "Not build type specified. Falling back to DEBUG.")
endif()

add_executable(photonizer "photonizer.cc")
target_link_libraries(photonizer
    PRIVATE Boost::program_options
            tinyobjloader
            gsl
            Photonizer::Misc)

if (CMAKE_BUILD_TYPE MATCHES "DEBUG")
    target_compile_options(photonizer PRIVATE -Wall -Wextra -pedantic -Werror -g -Og)
elseif (CMAKE_BUILD_TYPE MATCHES "RELEASE")
    target_compile_options(photonizer PRIVATE -Wall -Wextra -pedantic -O3)
endif()

message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode.")

target_compile_definitions(photonizer PRIVATE -DPHOTONIZER_VERSION="${RAYTRACER_VERSION}")
set_target_properties(photonizer PROPERTIES CXX_STANDARD 17)
