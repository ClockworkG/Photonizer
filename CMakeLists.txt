cmake_minimum_required(VERSION 3.12...3.13)

set(RAYTRACER_VERSION "0.0.0")

project(Raytracer
        VERSION ${RAYTRACER_VERSION}
        DESCRIPTION "Raytracer with photon mapping extension.")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)

add_custom_target(doc
                  COMMAND doxygen "${CMAKE_SOURCE_DIR}/doc/Doxyfile"
                  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
