set(BOOST_VERSION 1.69.0)

set(Boost_USE_STATIC_LIBS      FALSE)
set(Boost_USE_MULTITHREADED    TRUE)
set(Boost_USE_STATIC_RUNTIME   FALSE)
set(Boost_ADDITIONAL_VERSIONS  "${BOOST_VERSION}")
set(Boost_COMPILER             "-clang")

find_package(Boost ${BOOST_VERSION} EXACT REQUIRED
    COMPONENTS program_options)
