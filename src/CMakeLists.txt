add_executable(sample)
target_sources(sample PRIVATE "sample.cc")
target_link_libraries(sample
    PRIVATE Boost::program_options
            gsl
            math)

add_subdirectory(math)
