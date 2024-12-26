#include <benchmark/benchmark.h>
#include <boost/container/flat_map.hpp>
#include <unordered_map>

template <typename T>
class Map : public benchmark::Fixture {
public:
  void SetUp(::benchmark::State& state) {
    // Create a boost flat_map and insert 1000 random elements
    for (int i = 0; i < mSize; i++) {
      mMap.insert({i, rand()});
    }
  }

  void TearDown(::benchmark::State& state) {
  }

  const int32_t mSize {1000000};
  const int32_t mStep {100};
  T mMap;

};

// Defines and registers `FooTest` using the class `MyFixture`.
BENCHMARK_TEMPLATE_F(Map, FlatMapBenchmark, boost::container::flat_map<int,int>)(benchmark::State& st) {
   for (auto _ : st) {
    for(int32_t i{0}; i<mSize; ++i)
    {
      int32_t lIndex {rand() % mSize};
      (void)mMap.find(lIndex);
    }
  }
}

BENCHMARK_TEMPLATE_F(Map, UnorderedMapBenchmark, std::unordered_map<int,int>)(benchmark::State& st) {
   for (auto _ : st) {
    for(int32_t i{0}; i<mSize; ++i)
    {
      int32_t lIndex {rand() % mSize};
      (void)mMap.find(lIndex);
    }
  }
}

BENCHMARK_MAIN();
