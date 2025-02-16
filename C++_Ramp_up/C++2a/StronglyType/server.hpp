#ifndef SERVER_HPP
#define SERVER_HPP

#include "types.hpp"

class Server
{
public:
    Server(Port aPort, Protocol aProtocol, LoadFactor aMaxLoadFactor, Execution aIsAsync) {}
};

#endif // SERVER_HPP