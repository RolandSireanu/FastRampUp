#include <iostream>
enum class Axis {
  UNKNOWN = 0,
  CHANNELS = 1,
  INPUT_CHANNELS = 2,
  OUTPUT_CHANNELS = 3,
  HEIGHT = 4,
  WIDTH = 5,
  BATCH = 6,
  VALUE = 7,
  DEPTH = 8,
};


template <int N, Axis... As>
struct StrongShapeImpl{};

template <int N>
struct StrongShapeImpl<N> 
{
	void howMany() { std::cout<< N << std::endl; }
};


template <int N, Axis A, Axis... As>
struct StrongShapeImpl<N, A, As...> : public StrongShapeImpl<N + 1, As...>
{

};


int main()
{
    StrongShapeImpl<0, Axis::INPUT_CHANNELS, Axis::OUTPUT_CHANNELS, Axis::HEIGHT, Axis::WIDTH, Axis::VALUE> s{};
    s.howMany();

    return 0;
}