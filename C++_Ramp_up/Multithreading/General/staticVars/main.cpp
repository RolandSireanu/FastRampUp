

// Starting with C++11 initializing static variables inside a function is thread safe

class Singleton
{
public:
    static Singleton& getInstance()
    {
        static Singleton lInstance;
        return lInstance;
    }
};