
struct Laptop
{
  int id;
  double price;
};

// Lambda init capture list
Laptop tempLaptop;

// ============================================================================================
auto initCapture   = [x=3](){};

class __lambda_42_22
{
  public: 
  inline /*constexpr */ void operator()() const
  {
  }
  
  private: 
  int x;
  
  public:
  __lambda_42_22(const int & _x)
  : x{_x}
  {}
  
};
__lambda_42_22 initCapture = __lambda_42_22{3};


// ============================================================================================
auto initCapture2  = [&laptop = tempLaptop](){};

class __lambda_43_22
{
  public: 
  inline /*constexpr */ void operator()() const
  {
  }
  
  private: 
  Laptop & laptop;
  
  public:
  __lambda_43_22(Laptop & _laptop)
  : laptop{_laptop}
  {}
  
};
__lambda_43_22 initCapture2 = __lambda_43_22{tempLaptop};


// ============================================================================================
auto initCapture3  = [laptop = &tempLaptop](){};

class __lambda_44_22
{
  public: 
  inline /*constexpr */ void operator()() const
  {
  }
  
  private: 
  Laptop * laptop;
  
  public:
  __lambda_44_22(Laptop * _laptop)
  : laptop{_laptop}
  {}
  
};
__lambda_44_22 initCapture3 = __lambda_44_22{&tempLaptop};


// ============================================================================================
auto initCapture4  = [laptop = std::move(tempLaptop)](){};

class __lambda_45_22
{
  public: 
  inline /*constexpr */ void operator()() const
  {
  }
  
  private: 
  Laptop laptop;
  
  public:
  __lambda_45_22(Laptop && _laptop)
  : laptop{std::move(_laptop)}
  {}
  
};
__lambda_45_22 initCapture4 = __lambda_45_22{Laptop(std::move(tempLaptop))};
