#include <thread>

int gVar{0};

void inc(int arg)
{
    gVar++;
}


int main()
{
    std::thread t1(inc, 1);
    std::thread t2(inc, 1);

    while(1);

    t1.join();
    t2.join();

    return 0;
}