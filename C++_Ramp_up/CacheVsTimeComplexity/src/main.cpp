#include <benchmark/benchmark.h>
#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <random>
#include <ranges>
#include <algorithm>

namespace Resources
{
    constexpr int32_t noElements = 10'000'000;
    // const int32_t target = -5;
    // std::vector<int32_t> numbers(noElements);

    // void InitResources()
    // {
    //     std::ranges::generate(numbers, []() {
    //         static std::mt19937 gen{std::random_device{}()};
    //         static std::uniform_int_distribution<int> dist(0, 100);
    //         return dist(gen);
    //     });

    //     // Given the worst case scenario
    //     numbers[10'000] = -2;
    //     numbers[10'001] = -3;
    // }
}

static void BM_UsingAMap(benchmark::State& state) 
{
    std::vector<int32_t> lNumbers;
    for(int32_t i{0}; i<Resources::noElements; ++i)
    {
        lNumbers.push_back(i);
    }

    lNumbers.clear();
    lNumbers.shrink_to_fit();

    for (auto _ : state)
    {     
        for(int32_t i{0}; i<Resources::noElements; ++i)
        {
            lNumbers.push_back(i);
        }        
    }

    benchmark::DoNotOptimize(lNumbers);
}

static void BM_BruteForce(benchmark::State& state)
{
    std::vector<int32_t> lNumbers;
    for(int32_t i{0}; i<Resources::noElements; ++i)
    {
        lNumbers.push_back(i);
    }

    lNumbers.clear();
    lNumbers.shrink_to_fit();
    lNumbers.reserve(Resources::noElements);


    for (auto _ : state)
    {
       for(int32_t i{0}; i<Resources::noElements; ++i)
       {
           lNumbers.push_back(i);
       }
    }
    
    benchmark::DoNotOptimize(lNumbers);    
}

BENCHMARK(BM_UsingAMap);
BENCHMARK(BM_BruteForce);

// Register the function as a benchmark
int main(int argc, char** argv)
{
//    Resources::InitResources();
   ::benchmark::Initialize(&argc, argv);
   ::benchmark::RunSpecifiedBenchmarks();
}

