#include <ctime>
#include <cstdlib>

#include <benchmark/benchmark.h>

#include "kd-tree.hh"
#include "vector3.hh"

template <typename ValueType>
ValueType generate();

template<>
Vector3f generate()
{
    return Vector3f{static_cast<float>(std::rand() % 500) - 500,
                    static_cast<float>(std::rand() % 500) - 500,
                    static_cast<float>(std::rand() % 500) - 500};
}

template <typename ValueType>
static void BM_BrownAlgorithm(benchmark::State& state)
{
    std::srand(std::time(0));

    std::vector<ValueType> values(state.range(0));
    for (auto& val : values)
        val = generate<ValueType>();

    for (auto _ : state)
    {
        [[maybe_unused]]
        auto tree = photon::KDTree<ValueType>(std::begin(values),
                                              std::end(values));
    }
}

template <typename ValueType>
static void BM_NearestPoints(benchmark::State& state)
{
    std::srand(std::time(0));

    std::vector<ValueType> values(state.range(0));
    for (auto& val : values)
        val = generate<ValueType>();

    auto tree = photon::KDTree<ValueType>(std::begin(values),
                                          std::end(values));

    for (auto _ : state)
        tree.nearest(Vector3f(0, 0, 0), 300, 500);
}

BENCHMARK_TEMPLATE(BM_BrownAlgorithm, Vector3f)->Arg(1)
                                               ->Arg(5)
                                               ->Arg(10)
                                               ->Arg(50)
                                               ->Arg(100)
                                               ->Arg(500)
                                               ->Arg(1000)
                                               ->Arg(5000)
                                               ->Arg(10000)
                                               ->Arg(15000)
                                               ->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(BM_NearestPoints, Vector3f)->Arg(1)
                                              ->Arg(5)
                                              ->Arg(10)
                                              ->Arg(50)
                                              ->Arg(100)
                                              ->Arg(500)
                                              ->Arg(1000)
                                              ->Arg(5000)
                                              ->Arg(10000)
                                              ->Arg(15000)
                                              ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
