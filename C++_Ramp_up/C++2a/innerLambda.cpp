

auto lambda1 = [](int a, int b) {
    auto innerLambda = [a, b](){ return a + b; };
    return innerLambda();
 };

 // ====> Translates to


class __lambda_18_16
{
  public: 
  inline /*constexpr */ int operator()(int a, int b) const
  {
        
    class __lambda_19_24
    {
      public: 
      inline /*constexpr */ int operator()() const
      {
        return a + b;
      }
      
      private: 
      int a;
      int b;
      
      public:
      __lambda_19_24(int & _a, int & _b)
      : a{_a}
      , b{_b}
      {}
      
    };
    
    __lambda_19_24 innerLambda = __lambda_19_24{a, b};
    return innerLambda.operator()();
  }
  
  using retType_18_16 = int (*)(int, int);
  inline constexpr operator retType_18_16 () const noexcept
  {
    return __invoke;
  };
  
  private: 
  static inline /*constexpr */ int __invoke(int a, int b)
  {
    return __lambda_18_16{}.operator()(a, b);
  }
  
  
  public:
  // /*constexpr */ __lambda_18_16() = default;
  
};

__lambda_18_16 lambda1 = __lambda_18_16{};