#include <boost/circular_buffer.hpp>
#include "boost/container/vector.hpp"
#include <iostream>

int main()
{
    boost::circular_buffer<int> cb(3);
    // Insert three elements into the buffer.
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);

    std::cout << "Circular buffer capacity = " << cb.capacity() << "\n";

    std::cout << cb[0] << " , " << cb[1] << " , " << cb[2] << std::endl;

    boost::container::vector<int> v;
    v.push_back(21);
    std::cout << v[0] << "\n";

    return 0;
}