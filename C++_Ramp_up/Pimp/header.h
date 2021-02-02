

#ifndef HEADER_H
#define HEADER_H

#include <memory>
#include <iostream>

class Container
{
    
    public:
        
        Container();
        ~Container();

        unsigned int GetContainerSize();

    private:
        class impl;    
        std::unique_ptr<impl> pimpl;


};

#endif