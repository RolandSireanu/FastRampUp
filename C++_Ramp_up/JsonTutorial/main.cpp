#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <tbb/tbb.h>
#include <execution>
#include <algorithm>
#include <thread>


using namespace std;

template<typename T>
void ComputeSum(int32_t argBeg, int32_t argEnd, const T& argTran, int64_t& argSum )
{
    for(int32_t i{argBeg}; i<argEnd; ++i)
    {
        argSum += argTran[i].value("amount", int64_t(0));
    }
}


enum class ExecPolicy
{
    SEQUENCIAL,
    PARALLEL_TBB,
    PARALLEL_STD,
    PARALLEL_CUSTOM
};

template<ExecPolicy T>
int64_t sumTransactions(const std::string& argFilename) {
    nlohmann::json jsonData;
    int64_t lTotalAmount {0};
    
    // Open the file
    std::ifstream inputFile(argFilename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << argFilename << std::endl;
        return 0;
    }
    // Parse the JSON file
    inputFile >> jsonData;
    // Close the file
    inputFile.close();
    
    // Iterate over the 'transactions' array
    if (jsonData.contains("transactions")) 
    {
        if constexpr (T == ExecPolicy::SEQUENCIAL) 
        {
            for (const auto& transaction : jsonData["transactions"]) 
            {
                int64_t amount = transaction.value("amount", 0);
                lTotalAmount += amount;
            }
        } 
        else if constexpr (T == ExecPolicy::PARALLEL_TBB) 
        {
            const auto& transactions = jsonData["transactions"];
            
            // Use TBB to parallelize the summing of amounts
            lTotalAmount = tbb::parallel_reduce(
                tbb::blocked_range<size_t>(0, 1000000),
                0,
                [&](const tbb::blocked_range<size_t>& r, int64_t localSum) -> int64_t{
                    for (size_t i = r.begin(); i != r.end(); ++i) 
                    {
                        localSum += transactions[i].value("amount", 0);
                    }
                    return localSum;
                },
                std::plus<int64_t>()  // Combine the partial results
            );

        } 
        else if constexpr (T == ExecPolicy::PARALLEL_STD) 
        {
            const auto& transactions = jsonData["transactions"];
            
            // Use std::reduce with parallel execution to sum the amounts directly from 'transactions'
            lTotalAmount = std::reduce(std::execution::par, transactions.begin(), transactions.end(), int64_t(0),
                [](int64_t sum, const nlohmann::json& transaction) 
                {
                    return sum + transaction.value("amount", int64_t(0));
                });
        } 
        else if constexpr (T == ExecPolicy::PARALLEL_CUSTOM) 
        {
            const auto& transactions = jsonData["transactions"];
            constexpr int32_t lMaxElements {10};
            const int32_t lMaxSize {jsonData["transactions"].size()};
            const int32_t lStep = lMaxSize / lMaxElements;
            std::array<int, lMaxElements> lPartialSums {};
            std::thread lThreads[lMaxElements];

            for(int32_t i{0}; i<lMaxElements; ++i)
                // lThreads[i] = thread(&ComputeSum<decltype(transactions)>, i*lStep, (i*lStep) + lStep, transactions, std::ref(lPartialSums[i]));
                lThreads[i] = thread([&transactions, start=i*lStep, end=(i*lStep)+lStep, &lPartialSums, i]() mutable{
                    int64_t lPartialSum {};
                    for(int32_t i{start}; i<end; ++i)
                    {
                        lPartialSum += transactions[i].value("amount", int64_t(0));
                    }
                    lPartialSums[i] = lPartialSum;
                });
            
            for(int32_t i{0}; i<lMaxElements; ++i)
                lThreads[i].join();

            lTotalAmount = std::reduce(lPartialSums.begin(), lPartialSums.end(), 0);
        }
    }

    return lTotalAmount;
}


int main()
{
    const std::string lFileName {"../dataset/transactions.json"};
    #if defined(SEQ)    
    std::cout << "Total ammount = " << sumTransactions<ExecPolicy::SEQUENCIAL>(lFileName) << "\n";
    #elif defined(PAR_TBB)
    std::cout << "Total ammount " << sumTransactions<ExecPolicy::PARALLEL_TBB>(lFileName) << "\n";
    #elif defined(PAR_STD)
    std::cout << "Total ammount = " << sumTransactions<ExecPolicy::PARALLEL_STD>(lFileName) << "\n";
    #elif defined(PAR_CUSTOM)
    std::cout << "Total ammount = " << sumTransactions<ExecPolicy::PARALLEL_CUSTOM>(lFileName) << "\n";
    #endif
    return 0;   
}