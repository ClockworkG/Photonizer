
if (ENABLE_TESTING)
    include(GoogleTest)
    add_executable(tests)
    target_sources(tests PRIVATE main.cc kd-tree.cc)
    target_link_libraries(tests GTest::GTest GTest::Main Photonizer::Photon)
    set_target_properties(tests PROPERTIES CXX_STANDARD 17)
    gtest_discover_tests(tests TEST_PREFIX photon:)
endif()
