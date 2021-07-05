#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
//Builder design pattern is used especially when the initialization
//is very complex, usually the object is build pice by pice by calling
//a sequence or function or by setting multiple fields in one way
//or another
using namespace std;

using area = pair<size_t, size_t>;

namespace layer
{

struct base { virtual ~base() = default; };

struct dense final: base { dense(size_t const neurons) {} };
struct conv final: base { conv(size_t const kernels, area const dims) {} };
struct max_pool final: base { max_pool(area const stride, area const dims) {} };

}

class NetworkBuilder;

class Network {
        friend class NetworkBuilder;
    public:
        static NetworkBuilder make(const string_view arg);
    private:
        Network(const string_view arg) { cout << "Default constructor \n"; }
        Network(const Network& ) { cout << "Copy constructor \n"; }
        Network(Network&&) { cout << "Move constructor \n"; }

        template<typename T>    
        void add(T&& l) {
            layers.push_back(make_unique<T>(move(l)));
        }

        vector<unique_ptr<layer::base> > layers;
};

class NetworkBuilder {

    public:
        friend class Network;

        template<typename T>
        NetworkBuilder& add(T&& arg) 
        { 
            n.add(move(arg)); 
            return *this;
        }

        Network compile() 
        {
            return move(n);
        }
    private:
        NetworkBuilder(const NetworkBuilder&) = delete;
        NetworkBuilder(NetworkBuilder&& ) = delete;
        NetworkBuilder& operator=(const NetworkBuilder&) = delete;
        NetworkBuilder& operator=(NetworkBuilder&&) = delete;
        NetworkBuilder(const string_view arg) : n(arg) {}

        Network n;

};

NetworkBuilder Network::make(const string_view arg) {
    return NetworkBuilder(arg);
}

int main()
{
    Network net2 { 
        Network::make("VGG").add(layer::dense(32))
                            .add(layer::dense(48))
                            .compile()
    };    


    return 0;
}