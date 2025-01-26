#include <benchmark/benchmark.h>
#include <vector>
#include <array>
#include <iostream>
#include <thread>
#include <numeric>
#include <atomic>
#include <cassert>

struct alignas(64) AlignedInt32 {
  int32_t value;
};

const size_t lMaxNoThreads {std::thread::hardware_concurrency()};
std::vector<AlignedInt32> lAcc(lMaxNoThreads);
std::array<int32_t, 1024*64> lInData;

template<auto D>
void work(const std::array<int32_t, D>& aData)
{
  constexpr int32_t lExpectedResult = (((D-1) * D) / 2);
  std::vector<std::jthread> lThreads;
  lThreads.reserve(lMaxNoThreads);

  for(int32_t i{0}; i<lMaxNoThreads; ++i)
  {
    lThreads.emplace_back(std::jthread([&aData, i](){
      for(const auto& e : aData)
      {
        lAcc[i].value += e;
      }
    }));
  }

  for(int32_t i{0}; i<lMaxNoThreads; ++i)
  {
    lThreads[i].join();
  }

  for(const auto& e : lAcc)
  {
    if(e.value != lExpectedResult)
      throw std::runtime_error("Error: incorrect result");
  }
}


static void BM_FalseSharing(benchmark::State& state) 
{
  std::iota(lInData.begin(), lInData.end(), 0);

  for (auto _ : state) 
  {
    work(lInData);
  }
}


BENCHMARK(BM_FalseSharing)->UseRealTime()->Unit(benchmark::kMillisecond)->Iterations(1);

BENCHMARK_MAIN();