
// Starting with C++2a you can use auto in function param
// The following code will instantiate:
// int sum<int, int>(int a,int b)

auto sum(auto a, auto b)
{
    return a + b;
}

int main()
{
    int lValue{5};
    sum(lValue, lValue);

    return 0;
}