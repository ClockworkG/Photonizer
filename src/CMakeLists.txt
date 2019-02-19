if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "DEBUG" CACHE STRING "Choose the type of build: DEBUG or RELEASE" FORCE)
    message(WARNING "Not build type specified. Falling back to DEBUG.")
endif()

add_executable(raytracer "raytracer.cc")
target_link_libraries(raytracer
    PRIVATE Boost::program_options
            tinyobjloader
            gsl)

if (CMAKE_BUILD_TYPE MATCHES "DEBUG")
    target_compile_options(raytracer PRIVATE -Wall -Wextra -pedantic -Werror -g -Og)
elseif (CMAKE_BUILD_TYPE MATCHES "RELEASE")
    target_compile_options(raytracer PRIVATE -Wall -Wextra -pedantic -O3)
endif()

message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode.")

target_compile_definitions(raytracer PRIVATE -DRAYTRACER_VERSION="${RAYTRACER_VERSION}")
set_target_properties(raytracer PROPERTIES CXX_STANDARD 17)

add_subdirectory(math)
