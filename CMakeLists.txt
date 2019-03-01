cmake_minimum_required(VERSION 3.10...3.13)

set(PHOTONIZER_VERSION "0.3.1")

project(Photonizer
        VERSION ${PHOTONIZER_VERSION}
        DESCRIPTION "Raytracer with photon mapping extension.")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(CTest)
if (ENABLE_TESTING)
    enable_testing()
endif()

add_subdirectory(lib)
include(lib/boost/CMakeLists.txt)
include(lib/objloader/CMakeLists.txt)

add_subdirectory(src)
add_subdirectory(tests)

add_custom_target(doc
                  COMMAND doxygen "${CMAKE_SOURCE_DIR}/doc/Doxyfile"
                  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
