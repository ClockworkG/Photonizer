add_executable(raytracer)
target_sources(raytracer PRIVATE "raytracer.cc")
target_link_libraries(raytracer
    PRIVATE Boost::program_options
            gsl)
target_compile_options(raytracer PRIVATE
    -Wall -Wextra -pedantic -DRAYTRACER_VERSION="${RAYTRACER_VERSION}")
set_target_properties(raytracer PROPERTIES CXX_STANDARD 20)

add_subdirectory(math)
