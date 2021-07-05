#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <tuple>
#include <vector>
#include <initializer_list>
using namespace std;

template<typename T>
class Tensor;

namespace TensorFactory {
    template<typename T>
    Tensor<T> make_tensor(initializer_list<unsigned> shape);
};


template<typename T>
class Tensor {
    
    template<typename TT>
    friend Tensor<TT> TensorFactory::make_tensor(initializer_list<unsigned>);
    public:
        Tensor(Tensor&& arg) = default;

    private:
        Tensor(initializer_list<unsigned> shape)
        {
            vector<int> vShape;
            for(auto s : shape)
                vShape.push_back(s);

            unsigned int counter = 0;
            for(auto d : vShape) {
                if(counter == 0)
                {
                    weights.resize(d);
                }
                if(counter == 1)
                {
                    for(int i=0; i<vShape[0]; ++i) {
                        weights[i].resize(d);
                    }
                }
                if(counter == 2)
                {
                    for(int i=0; i<vShape[0]; i++)
                        for(int j=0; j<vShape[1]; j++)
                            weights[i][j].resize(d);
                }
                ++counter;   
            }
                
        }
        vector< vector< vector <T> > > weights;

        Tensor(const Tensor& arg);
        Tensor& operator=(const Tensor& arg);
        Tensor& operator=(Tensor&& arg);

        //Non static member initialization
        //With multiple constructors you don't have to specify default values
        //for each of them
        std::array<int, 3> shape {0};
};

template<typename T>
Tensor<T> TensorFactory::make_tensor(initializer_list<unsigned> shape) {
    return Tensor<T>(shape);
}


int main()
{
    Tensor<uint64_t> t = TensorFactory::make_tensor<uint64_t>({64,32,3});
    Tensor<uint32_t> t2 = TensorFactory::make_tensor<uint32_t>({64,32,3});
    // Tensor t({64,32,4});
    // t.weights[0][0][0] = 23;
    // t.weights[63][31][3] = 0xFF;
    // cout << t.weights[63][31][3] << endl;

    return 0;
}
