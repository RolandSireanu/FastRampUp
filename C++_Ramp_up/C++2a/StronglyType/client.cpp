#include "server.hpp"
#include "user_def_literals.hpp"

int main()
{
    using namespace user_defined_literals;

    Server s{23_port, Protocol::TCP_IP, 0.75_loadFactor, Execution::SYNC};

    return 0;
}