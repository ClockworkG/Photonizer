add_executable(sample)
target_sources(sample PRIVATE "sample.cc")
target_link_libraries(sample
    PRIVATE Boost::program_options
            gsl
            math)
target_compile_options(sample PRIVATE
    -Wall -Wextra -pedantic)
set_target_properties(sample PROPERTIES CXX_STANDARD 20)

add_subdirectory(math)
