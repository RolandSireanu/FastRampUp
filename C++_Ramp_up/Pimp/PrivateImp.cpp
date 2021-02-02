#include "header.h"

class Container::impl
{
    public:

        impl() = default;

        unsigned int getSize() { return 10; }
        void doInternalWork() {}
};


Container::Container() : pimpl(std::make_unique<impl>())
{

}

Container::~Container() = default;

unsigned int Container::GetContainerSize() 
{
    pimpl->doInternalWork();
    pimpl->getSize();
}
