//Initialization is split into two categories:
//  1. Static initialization
//     Static initialization occurs before the program starts running and involves values that can be determined at compile time.
    int a {3};
    static int b {5};
//  2. Dynamic initialization
//     Dynamic initialization occurs during runtime and may involve more complex expressions or values that depend on runtime conditions

    static Complex c;
    int result = f();

// Dynamic initialization is discouraged, due to the following risks:
//  - static initialization order fiasco (the order of initialization of static vars in diff translation units is not defined)
//      If one variable initialization depends on the other, the last one can be also uninitialized.
//  - resource leaks

// ========== How is the dynamic initialization problem addresses in c++ ? =======
// Throught constinit and constexpr

// Both constinit and constexprsolves the problem of dynamic initialization, 
// more precise "static initialization order fiasco". The difference between them:
//  1. Regarding variables
//      1.1 constinit doesn't implie const variable
//      1.2 both enforce compile time evaluation
//  2. Regarding functions
//      2.1 constinit applies only to variables, not functions
//      2.2 can run at compile time if given compile-time arguments, enabling compile-time computations.
//          otherwise, at runtime. It doesn't eforce compile time evaluation.


int f() { return 5; }

// Ok, static_storage_var is statically initialized with a compile time constant
constinit int static_storage_var {3};
// constinit int static_storage_var2 = f();     //Fail, doesn't have a constant initializer

constexpr int static_storage_var3 {5};

// constexpr int static_storage_var4 { f() };   //Fail, constexpr variables should be initialized at compile time, "f" is not constexpr


// Function add has the posibility of beeing evaluated at compile if the arguments are provided
// If not, it can also be evaluated at runtime.
constexpr int add(int a, int b) { return a + b; }

int main()
{
    static_storage_var = 5;     // constinit doesn't imply const variable
    // static_storage_var3 = 0;    // Fail, constexpr implies const variable

    add(2,2);
    add(f(), f());

    return 0;
}

// ==============================================================================

// As a rule of thumb, each static storage variables with dynamic initialization
// should be constexpr or constinit