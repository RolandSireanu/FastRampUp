#include <iostream>
#include <vector>
using namespace std;


class layer_base {

    public:
        virtual ~layer_base() = default;

};

class fc_layer final : public layer_base {

    public:
};

class conv_layer final : public layer_base {

    public:
    conv_layer() { cout << "conv_layer constructor " << endl; }
    conv_layer(const conv_layer& arg) { cout << "conv_layer copy constructor " << endl; }
    conv_layer(conv_layer&& arg) { cout << "conv_layer move constructor " << endl; }
    conv_layer& operator=(const conv_layer& arg) { 
        cout << "conv_layer copy assigment operator " << endl;
        return *this;
    }

};

template<typename fp>
class Network final 
{
    static_assert(is_floating_point<fp>::value, "Expecting floating point value");

    public:
        template<typename LayerType>
        void add(LayerType&& l);
        
        ~Network() {
            for(auto l : layers) {
                delete l;
            }
        }

    private:
        vector<layer_base*> layers;

        
};

template<typename fp>
template<typename T>
void Network<fp>::add(T&& l) {

    static_assert(is_base_of<layer_base, T>::value, "Network accepts only layers of common base !");
    layers.emplace_back(new T(forward<T>(l)));
}

int main()
{
    Network<float> fnet;
    fnet.add(conv_layer());
    fnet.add(fc_layer());
    
    Network<double> dnet;
    fnet.add(conv_layer());
    fnet.add(fc_layer());
}