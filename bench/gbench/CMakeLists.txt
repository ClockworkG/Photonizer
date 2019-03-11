set(GBENCH_URL https://github.com/google/benchmark.git)

include(ExternalProject)
find_package(Git REQUIRED)

set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/3rd_party)

ExternalProject_Add(
    gbench-extern
    GIT_REPOSITORY ${GBENCH_URL}
    TIMEOUT 10
    BUILD_COMMAND cmake -DCMAKE_BUILD_TYPE=RELEASE -DBENCHMARK_ENABLE_GTEST_TESTS=OFF "${CMAKE_BINARY_DIR}/3rd_party/src/gbench-extern" && make
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(gbench-extern SOURCE_DIR)
ExternalProject_Get_Property(gbench-extern BINARY_DIR)
set(gbench_INCLUDE_DIR ${SOURCE_DIR} CACHE INTERNAL "Include folder for gbench")

add_library(benchmark STATIC IMPORTED GLOBAL)
set_target_properties(benchmark PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/libbenchmark.a)
include_directories(${GBENCH_INCLUDE_DIR})

add_library(benchmark_main STATIC IMPORTED GLOBAL)
set_target_properties(benchmark_main PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/libbenchmark_main.a)
include_directories(${GBENCH_INCLUDE_DIR})
