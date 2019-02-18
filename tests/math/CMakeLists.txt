add_executable(tests)
target_sources(tests PRIVATE main.cc math-tests.cc)
target_link_libraries(tests GTest::GTest GTest::Main math)
set_target_properties(tests PROPERTIES CXX_STANDARD 20)
