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

//  3. Constraints on member functions
        template<typename T>
        class MyInt
        {

        }

//  4. Constraints on member functions
        template<typename T>
        class MyInt
        {
        public:
            // I am going to generate a specialization for any type that is integral || floating point
            // For any other type, no specialization will be defined, only definition.
            bool isZero() const requires std::integral<T> || std::floating_point<T>
            {
                return true;
            }
        };

int main()
{
    BigInt lLocal{23};
    SmallInt lSmall{98};
    
    return 0;
}