#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace LOG 
{
    enum class level : unsigned char 
    {
        INFO,
        WARNING,
        ERROR
    };

    class smart_stream
    {
        public:
            smart_stream() = default;
            smart_stream(std::ostream& argStream) : ptrStream{&argStream}
            {
            }

            template<typename T>
            smart_stream& operator << (const T& arg)
            {
                if(ptrStream != nullptr) 
                    (*ptrStream) << arg << std::endl;
                return *this;
            }   

        private:
            std::ostream* ptrStream;

    };
};

#endif