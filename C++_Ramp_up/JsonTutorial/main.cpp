#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <tbb/tbb.h>
#include <execution>
#include <algorithm>

int64_t parseTransactions(const std::string& filename) {
    // Create a JSON object
    nlohmann::json jsonData;
    
    // Open the file
    std::ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0;
    }

    // Parse the JSON file
    inputFile >> jsonData;
    
    // Close the file
    inputFile.close();

    int64_t lTotalAmount {0};
    
    // Iterate over the 'transactions' array
    if (jsonData.contains("transactions")) {
        for (const auto& transaction : jsonData["transactions"]) {
            // std::string name = transaction.value("name", "Unknown");
            // bool vip = transaction.value("vip", false);
            int64_t amount = transaction.value("amount", 0);
            lTotalAmount += amount;
            
        }
    } else {
        std::cerr << "'transactions' key not found in the JSON data." << std::endl;
    }

    return lTotalAmount;
}

int64_t parseTransactionsParallel(const std::string& filename) {
    // Create a JSON object
    nlohmann::json jsonData;
    
    // Open the file
    std::ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0.0;
    }

    // Parse the JSON file
    inputFile >> jsonData;
    
    // Close the file
    inputFile.close();
    
    int64_t totalAmount = 0;

    // Check if 'transactions' key exists in the JSON data
    if (jsonData.contains("transactions")) {
        const auto& transactions = jsonData["transactions"];
        
        // Use TBB to parallelize the summing of amounts
        totalAmount = tbb::parallel_reduce(
            tbb::blocked_range<size_t>(0, 10000000),
            0,
            [&](const tbb::blocked_range<size_t>& r, int64_t localSum) -> int64_t{
                for (size_t i = r.begin(); i != r.end(); ++i) {
                    localSum += transactions[i].value("amount", 0);
                }
                return localSum;
            },
            std::plus<int64_t>()  // Combine the partial results
        );
    } else {
        std::cerr << "'transactions' key not found in the JSON data." << std::endl;
    }

    return totalAmount;
}


int64_t parseTransactionsStdParallel(const std::string& filename) {
    // Create a JSON object
    nlohmann::json jsonData;
    
    // Open the file
    std::ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0; // Return 0 in case of error
    }

    // Parse the JSON file
    inputFile >> jsonData;

    // Close the file
    inputFile.close();
    
    int64_t totalAmount = 0;

    // Check if 'transactions' key exists in the JSON data
    if (jsonData.contains("transactions")) {
        const auto& transactions = jsonData["transactions"];
        
        // Use std::reduce with parallel execution to sum the amounts directly from 'transactions'
        totalAmount = std::reduce(std::execution::par, transactions.begin(), transactions.end(), int64_t(0),
            [](int64_t sum, const nlohmann::json& transaction) {
                return sum + transaction.value("amount", int64_t(0));
            });
    } else {
        std::cerr << "'transactions' key not found in the JSON data." << std::endl;
    }

    return totalAmount;
}

int main()
{
    std::cout << "Total amount = " << parseTransactionsStdParallel("../dataset/transactions.json");
    return 0;
}