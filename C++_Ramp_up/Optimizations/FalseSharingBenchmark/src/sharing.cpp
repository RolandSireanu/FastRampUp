#include <benchmark/benchmark.h>
#include <vector>
#include <array>
#include <thread>
#include <numeric>

namespace WorkerNamespace
{

enum class CHECK_OPTION
{
    NO_CHECK,
    CHECK_RESULT
};


struct alignas(64) AlignedInt32 {
    int32_t value;

    AlignedInt32& operator+=(int32_t rhs) {
        value += rhs;
        return *this;
    }

    bool operator!=(int32_t rhs) const {
        return value != rhs;
    }
};

std::ostream& operator<<(std::ostream& os, const AlignedInt32& obj) {
    os << obj.value;
    return os;
}

template<typename T, CHECK_OPTION CHECK = CHECK_OPTION::NO_CHECK>
class Worker
{

public:

    Worker() : lMaxNoThreads{std::thread::hardware_concurrency()}, lAcc(lMaxNoThreads, T{0}) {}

    template<auto D>
    void work(const std::array<int32_t, D>& aData)
    {        
        std::vector<std::jthread> lThreads;
        lThreads.reserve(lMaxNoThreads);    

        for(int32_t i{0}; i<lMaxNoThreads; ++i)
        {
            lThreads.emplace_back(std::jthread([&aData, i, this](){
            for(const auto& e : aData)
            {
                lAcc[i] += e;
            }
            }));
        }

        if constexpr(CHECK == CHECK_OPTION::CHECK_RESULT)
        {
            for(int32_t i{0}; i<lMaxNoThreads; ++i)
            {
                lThreads[i].join();
            }

            constexpr int32_t lExpectedResult = (((D-1) * D) / 2);        
            for(const auto& e : lAcc)
            {
                if(e != lExpectedResult)
                {
                    throw std::runtime_error("Error: incorrect result");
                }
            }
        }
    }

private:
    const size_t lMaxNoThreads;
    std::vector<T> lAcc;
    
};  // class Worker
}   // namespace WorkerNamespace


template<typename T>
static void BM_Sharing(benchmark::State& state) 
{
    std::array<int32_t, 1024*1024> lInData;
    std::iota(lInData.begin(), lInData.end(), 0);
    
    for (auto _ : state) 
    {
        T lWorker;
        lWorker.work(lInData);
    }
}


BENCHMARK_TEMPLATE(BM_Sharing, WorkerNamespace::Worker<WorkerNamespace::AlignedInt32>)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_Sharing, WorkerNamespace::Worker<int32_t>)->UseRealTime()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();