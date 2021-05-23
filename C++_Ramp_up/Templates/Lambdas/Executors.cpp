#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <functional>
using namespace std;

enum op_type : unsigned int {
    op_add,
    op_multiply
};

template<typename T>
struct hash_function {

    size_t operator()(const T val) const {
        return static_cast<size_t>(val);
    }
};

template<typename T>
using vector_map = unordered_map <op_type, function<T(const T& arg1, const T& arg2)>, hash_function<T> >;

template<typename T>
const vector_map<T> impls {
    {op_type::op_add, [](const T& a, const T& b) { return a + b; }} , 
    {op_type::op_multiply, [](const T& a, const T& b) { return a * b; }}
};

template<typename T>
vector<T> execute(const vector<T>& a, const vector<T>& b, const op_type op)
{
    vector<T> result(a.size());

    auto operation = impls<T>.at(op);
    for(int i=0; i<a.size(); i++)
    {
        result[i] = operation(a[i], b[i]);
    }

    return result;
}


int main()
{
    vector<int> a {1,2,3};
    vector<int> b {4,5,6};

    vector<int> r = execute(a, b, op_type::op_add);
    for(auto it=begin(r); it != end(r); it++)
    {
        cout << (*it) << endl;
    }


    vector<double> da {1.2, 2.2, 3.3};
    vector<double> db {4.2, 5.2, 6.3};
    vector<double> dr = execute (da, db, op_type::op_multiply);
    for(const auto& e : dr)
    {
        cout << e << endl;
    }

    return 0;
}