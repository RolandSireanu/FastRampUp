#include <benchmark/benchmark.h>
#include <boost/container/flat_map.hpp>
#include <unordered_map>
#include <map>
#include <iostream>

enum class MapOperation
{
    Insert,
    Find,
    Erase
};

template<typename T, MapOperation OP>
void BM_RandomInsertion(benchmark::State& state) {
  const int32_t lNoElements = state.range(0);
  T lMap;

  for(int32_t index{0}; index < lNoElements; ++index)
  {
    benchmark::DoNotOptimize(lMap.insert(std::make_pair(index, rand())));
  }

  if(lMap.size() != lNoElements)
      throw std::runtime_error("BM_RandomInsertion::Not all elements have been inserted into map!\n");
  
  int32_t lCurrentIt {0};
  for (auto _ : state) {  
    for(int32_t i{0}; i<10000; ++i)
    {
      if constexpr(OP == MapOperation::Insert)
        benchmark::DoNotOptimize(lMap.insert(std::make_pair(rand(), rand())));
      else if constexpr(OP == MapOperation::Find)
        benchmark::DoNotOptimize(lMap.find(rand() % lNoElements));
      else if constexpr(OP == MapOperation::Erase)
        benchmark::DoNotOptimize(lMap.erase(lCurrentIt*10000 + i));
    }
    lCurrentIt++;
  }
}

BENCHMARK_TEMPLATE(BM_RandomInsertion,  boost::container::flat_map<int, int>, MapOperation::Insert)->Unit(benchmark::kMillisecond)->Arg({1024*256})->Arg({1024*1024})->Arg({1024*1024*4})->Arg({1024*1024*16})->Arg({1024*1024*64});
BENCHMARK_TEMPLATE(BM_RandomInsertion,  std::map<int, int>, MapOperation::Insert)->Unit(benchmark::kMillisecond)->Arg({1024*256})->Arg({1024*1024})->Arg({1024*1024*4})->Arg({1024*1024*16})->Arg({1024*1024*64});
BENCHMARK_TEMPLATE(BM_RandomInsertion,  std::unordered_map<int, int>, MapOperation::Insert)->Unit(benchmark::kMillisecond)->Arg({1024*256})->Arg({1024*1024})->Arg({1024*1024*4})->Arg({1024*1024*16})->Arg({1024*1024*64});

BENCHMARK_TEMPLATE(BM_RandomInsertion,  boost::container::flat_map<int, int>, MapOperation::Find)->Unit(benchmark::kMillisecond)->Arg({1024*256})->Arg({1024*1024})->Arg({1024*1024*4})->Arg({1024*1024*16})->Arg({1024*1024*64});
BENCHMARK_TEMPLATE(BM_RandomInsertion,  std::map<int, int>, MapOperation::Find)->Unit(benchmark::kMillisecond)->Arg({1024*256})->Arg({1024*1024})->Arg({1024*1024*4})->Arg({1024*1024*16})->Arg({1024*1024*64});
BENCHMARK_TEMPLATE(BM_RandomInsertion,  std::unordered_map<int, int>, MapOperation::Find)->Unit(benchmark::kMillisecond)->Arg({1024*256})->Arg({1024*1024})->Arg({1024*1024*4})->Arg({1024*1024*16})->Arg({1024*1024*64});

BENCHMARK_TEMPLATE(BM_RandomInsertion,  boost::container::flat_map<int, int>, MapOperation::Erase)->Unit(benchmark::kMillisecond)->Arg({1024*256})->Arg({1024*1024})->Arg({1024*1024*4})->Arg({1024*1024*16})->Arg({1024*1024*64});
BENCHMARK_TEMPLATE(BM_RandomInsertion,  std::map<int, int>, MapOperation::Erase)->Unit(benchmark::kMillisecond)->Arg({1024*256})->Arg({1024*1024})->Arg({1024*1024*4})->Arg({1024*1024*16})->Arg({1024*1024*64});
BENCHMARK_TEMPLATE(BM_RandomInsertion,  std::unordered_map<int, int>, MapOperation::Erase)->Unit(benchmark::kMillisecond)->Arg({1024*256})->Arg({1024*1024})->Arg({1024*1024*4})->Arg({1024*1024*16})->Arg({1024*1024*64});


BENCHMARK_MAIN();
