#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

class text
{
    public:
        text(std::string value): rep { std::move(value) } {}
        virtual ~text() = default;

        virtual operator std::string() const { return rep; }

    private:
        std::string rep;
};

template<typename t>
class bold : public t
{
    static_assert(is_base_of<text, t>::value);

    public:
        using t::t;
        operator string() const override 
        {
            return "\x1b[1m" + t::operator std::string() + "\x1b[0m";
        }

};

template<typename t>
class colored : public t 
{
    static_assert(is_base_of<text, t>::value);

    public:
        using t::t;

        template<typename ...Args>
        colored(unsigned int color_code, Args&&... args) : color_code{color_code} ,
            t(forward<Args>(args) ... )
        {

        }


        operator string() const override 
        {
            return "\x1b[" +to_string(color_code) +"m"+ t::operator string() + "\x1b[0m";
        }

    private:
        unsigned int color_code;

};


int main()
{
    
    text t("Hello world !");
    colored<bold<text>> cbt {35,"Hello world !"};
    cout << static_cast<string>(cbt) << endl;


    return 0;
}
