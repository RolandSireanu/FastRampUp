#ifndef HEADER_FILE
#define HEADER_FILE

// ============= Inline variables ========================
// The inline keyword in this context indicates that there can be multiple definitions of the variable 
// across different translation units, but they all refer to the same entity. 
// This feature is particularly useful for ensuring that a variable 
// with the same name and type initialized with the same value is only instantiated once.

// What type of linkage does each variable have?
// namespace MyNamespace
// {
//     constexpr int myVariable = 3;       // Internal linkage
//     const int myVariable2    = 3;       // Internal linkage
//     static int myVariable3   = 3;       // Internal linkage
//     int myVariable4          = 3;       // External linkage 
//     inline int myVariable5   = 3;       // External linkage
// }
// Anything that has internal linkage respect the ODR when included in multiple
// translation units

#define CONST           1       // Internal linkage, duplicated in each TU
#define CONSTEXPR       0       // Internal linkage, duplicated in each TU
#define STATIC          0       // Internal linkage, duplicated in each TU
#define INLINE          0       // External linkage, not duplicated 
#define CONST_INLINE    0       // External linkage, not duplicated

#if CONST
namespace Utils
{
    const int a = 5;
    const int b = 6;
    const int c = 7;
    const int d = 8;
}
#if CONST_INLINE
namespace Utils
{
    const inline int a = 5;
    const inline int b = 6;
    const inline int c = 7;
    const inline int d = 8;
}
#elif CONSTEXPR
namespace Utils
{
    constexpr int a = 5;
    constexpr int b = 6;
    constexpr int c = 7;
    constexpr int d = 8;
}
#elif STATIC
namespace Utils
{
    static int a = 5;
    static int b = 6;
    static int c = 7;
    static int d = 8;
}
#elif INLINE
namespace Utils
{
    inline a = 5;
    inline b = 6;
    inline c = 7;
    inline d = 8;
}
#endif

#endif