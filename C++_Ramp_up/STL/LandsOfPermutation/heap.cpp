#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

namespace utilities
{
    
    template<typename T>
    void show(const T& arg)
    {
        for(const auto& e : arg)
            cout << e << " ";
        cout << endl;
    }
    
    void va_print()
    {
        cout << endl;
    }

    template<typename T , typename ...Args>
    void va_print(T arg, Args... args)
    {
        cout << arg << " ";
        va_print(args ...);
    }

    void out(const auto& what, int n = 1) {
        while (n-- > 0)
            std::cout << what;
    }

    void print(auto rem, auto const& v) {
        out(rem);
        for (auto e : v) { out(e), out(' '); }
        out('\n');
    }

    void draw_heap(auto const& v)
    {
        auto bails = [](int n, int w) {
            auto b = [](int w) { out("┌"), out("─", w), out("┴"), out("─", w), out("┐"); };
            if (!(n /= 2)) return;
            for (out(' ', w); n-- > 0; ) b(w), out(' ', w + w + 1);
            out('\n');
        };
        auto data = [](int n, int w, auto& first, auto last) {
            for(out(' ', w); n-- > 0 && first != last; ++first)
                out(*first), out(' ', w + w + 1);
            out('\n');
        };
        auto tier = [&](int t, int m, auto& first, auto last) {
            const int n {1 << t};
            const int w {(1 << (m - t - 1)) - 1};
            bails(n, w), data(n, w, first, last);
        };
        const int m {static_cast<int>(std::ceil(std::log2(1 + v.size())))};
        auto first {v.cbegin()};
        for (int i{}; i != m; ++i) { tier(i, m, first, v.cend()); }
    }

};

namespace heap_algos
{
    using namespace utilities;
    vector<int> test { 4,3,9,1,17,29,11 };

    void build_heap()
    {
        make_heap(test.begin(), test.end());
        utilities::show(test);
        utilities::va_print("Pop from heap:");

        //Move largest element to the end
        pop_heap(test.begin(), test.end());
        va_print("Largest element was : " , test.back());
        //Remove largest element 
        test.pop_back();

        va_print("After pop:");
        show(test);
        draw_heap(test);

        va_print("Adding value 8 to heap :");
        test.push_back(8);
        push_heap(test.begin(), test.end());
        draw_heap(test);

        //Checking if the given range is a max heap 
        if(is_heap(test.begin(), test.end()))
            va_print("Given range is a max heap ");

    }
};


int main()
{

    heap_algos::build_heap();

    return 0;
}

