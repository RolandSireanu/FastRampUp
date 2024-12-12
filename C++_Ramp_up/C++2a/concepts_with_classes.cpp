// ============================ C++ concepts with classes ====================

template<typename T>
concept Number = std::integral<T> || std::floating_point<T>;


//  1. The requires clause
        template<typename T>
        requires Number<T>
        class BigInt
        {
        public:
            BigInt(const T& aValue) : mValue{aValue} {}

            T mValue;
        };

//  2. Constrained template parameters
        template<Number T>
        class SmallInt
        {
        public:
            SmallInt(const T& aValue) : mValue{aValue} {}

            T mValue;
        };

int main()
{
    BigInt lLocal{23};
    SmallInt lSmall{98};
    
    return 0;
}