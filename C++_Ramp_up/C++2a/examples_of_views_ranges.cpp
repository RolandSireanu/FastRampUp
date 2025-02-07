#include <array>
#include <ranges>
#include <algorithm>
#include <iostream>
#include <functional>
#include <numeric>
using namespace std;

// template<typename T>
// concept IsRange = requires(T a)
// {
//     { std::begin(a) } -> std::input_iterator;
//     { std::end(a)   } -> std::input_iterator;
// };

template<std::ranges::range T>
void printRange(const T& arg, char del = '\n')
{
    for(const auto& e : arg)
        std::cout << e << del;
    std::cout << "\n";
}

int main()
{
    array<int, 5> lData {9, 18, 36, 0 , 1};
    std::ranges::subrange lViewInData {lData};

    std::ranges::for_each(lData, [](int& arg){arg = arg * arg;});
    printRange(lData);

    bool result = std::ranges::all_of(lViewInData, [](const int& arg) -> bool { return arg >= 0; });
    if(result)
        std::cout << "All elements from subrange are possitive \n";
    
    if(ranges::none_of(lViewInData, std::bind(std::modulus<int>(), std::placeholders::_1, 2)))
        std::cout << "None of them are odd\n";


    std::array<std::string,4> lDate {"2 016 p13 25", "2011/11/22", "2010-03-05", "12 a 22134"};
    result = std::accumulate(lDate.begin(), lDate.end(), true, [](bool acc, const std::string& text){
        bool result = (ranges::find(text, 'p') != text.end() ||
                        ranges::find(text, '/') != text.end() ||
                        ranges::find(text, '-') != text.end());
        return acc && result;
    });
    if(result)
        std::cout << "All string are valid\n";

    // Print only valid elements
    auto valid = [](const std::string& arg) -> bool {
        return (ranges::find(arg, 'p') != arg.end() ||
                ranges::find(arg, '/') != arg.end() ||
                ranges::find(arg, '-') != arg.end());
    };
    auto lSubRange = lDate | std::views::filter(valid);
    for(auto& e : lSubRange)
        std::cout << e << "\n";

    // Create new vector with only valid strings
    auto getDelim = [](const std::string& arg) -> char {
        if(ranges::find(arg, 'p') != arg.end())
            return 'p';
        if(ranges::find(arg, '-') != arg.end())
            return '-';
        if(ranges::find(arg, '/') != arg.end())
            return '/';
    };
    auto trim = [](const std::string& arg) -> std::string {
        auto lSubRange = std::ranges::filter_view(arg, [](char argChr){
            return !std::isspace(argChr);
        });

        std::string lResult{};
        for(const auto& e : lSubRange)
            lResult += e;
        
        return lResult;
    };
    std::vector<std::string> lValidElements;
    for(auto e : lDate  | std::views::filter(valid) | std::views::transform(trim))
    {
        std::string temp {};
        const char delim {getDelim(e)};

        for(const auto& element : e | std::views::split(delim))
        {
            temp += std::string(element.begin(), element.end());
        }

        lValidElements.push_back(temp);
    }
    std::cout << "Vector with only valid values :\n";
    printRange(lValidElements, '\n');

    return 0;
}
