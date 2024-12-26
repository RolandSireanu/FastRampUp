#include <benchmark/benchmark.h>

static void BM_Dummy(benchmark::State& state) {
  for (auto _ : state) {
    // Dummy benchmark code
  }
}
BENCHMARK(BM_Dummy);

BENCHMARK_MAIN();
