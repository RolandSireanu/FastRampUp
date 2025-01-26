#include <benchmark/benchmark.h>
#include <unordered_map>
#include <map>
#include <iostream>
#include <thread>
#include <utility>

template<int32_t D>
void work(const std::array<int32_t, D>& aData)
{
  const size_t lMaxNoThreads {std::thread::hardware_concurrency()};
  std::array<std::jthread, lMaxNoThreads> lThreads;
}

static void BM_FalseSharing(benchmark::State& state) 
{



  for (auto _ : state) 
  {}
}


BENCHMARK(BM_FalseSharing)->UseRealTime()->Unit(benchmark::kMillisecond)->Iterations(1000);

BENCHMARK_MAIN();