set(OBJLOADER_URL https://github.com/syoyo/tinyobjloader)

include(ExternalProject)
find_package(Git REQUIRED)

set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/3rd_party)

ExternalProject_Add(
    objloader-extern
    GIT_REPOSITORY ${OBJLOADER_URL}
    GIT_TAG v1.0.7
    TIMEOUT 10
    BUILD_COMMAND cmake "${CMAKE_BINARY_DIR}/3rd_party/src/objloader-extern" && make
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(objloader-extern SOURCE_DIR)
ExternalProject_Get_Property(objloader-extern BINARY_DIR)
set(OBJLOADER_INCLUDE_DIR ${SOURCE_DIR} CACHE INTERNAL "Include folder for objloader")

add_library(tinyobjloader STATIC IMPORTED GLOBAL)
set_target_properties(tinyobjloader PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/libtinyobjloader.a)
include_directories(${OBJLOADER_INCLUDE_DIR})
