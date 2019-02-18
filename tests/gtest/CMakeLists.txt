set(GTest_COMPILER "-clang")

find_package(GTest REQUIRED)

if (GTest_FOUND)
    set_target_properties(GTest::GTest
                          GTest::Main
        PROPERTIES IMPORTED_GLOBAL TRUE)
endif()
