#include <boost/circular_buffer.hpp>
#include <iostream>

int main()
{
    boost::circular_buffer<int> cb(3);
    // Insert three elements into the buffer.
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);

    std::cout << cb[0] << " , " << cb[1] << " , " << cb[2] << std::endl;

    return 0;
}