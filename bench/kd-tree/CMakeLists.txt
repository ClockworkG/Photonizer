add_executable(kd-tree-bench bench.cc)
set_target_properties(kd-tree-bench PROPERTIES CXX_STANDARD 17)
target_link_libraries(kd-tree-bench PUBLIC benchmark benchmark_main Photonizer::Photon pthread)
