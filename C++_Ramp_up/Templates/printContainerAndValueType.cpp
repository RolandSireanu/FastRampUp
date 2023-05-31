// Example app for printing any container and the importance of "value_type"


//Version 1.0 of print function
//Why value_type alias is important?
//  By using value_type, you can write generic code that can work with different container types without explicitly specifying the element type. 
//  It provides a convenient way to abstract the container's element type and make your code more flexible and reusable.
template <typename Container>
void printContainer(const Container& container) {
  typename Container::value_type element;
  
  for (const auto& item : container) {
    element = item;
    std::cout << element << " ";
  }
  
  std::cout << std::endl;
}

//What if value_type wouldn't exists
//Same functionality of printContainer but without value_type
template <typename Container>
void printContainer(const Container& container) {
  typename std::remove_reference<decltype(*std::begin(container))>::type element;

  for (const auto& item : container) {
    element = item;
    std::cout << element << " ";
  }

  std::cout << std::endl;
}


//Another version of printContainer function, again without value_type
template <template<typename...> class Container, typename ElementType>
void printContainer(const Container<ElementType>& container) {
  ElementType element;

  for (const auto& item : container) {
    element = item;
    std::cout << element << " ";
  }

  std::cout << std::endl;
}