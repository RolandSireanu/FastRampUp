#include <iostream>
#include <memory>
using namespace std;

class Item
{
    public:
        virtual int price() = 0;
};
class Decorated : public Item
{
    public:
        Decorated(unique_ptr<Item> arg) : item{move(arg)} {}
        unique_ptr<Item> item;
        const Item& getItem() const { return *item; }
        Item& getItem() { return *item; }
};
class Book : public Item
{
    public:
        Book(int price) : mPrice{price} {}
        int price() { return mPrice; }
        int mPrice;
};

class Discounted : public Decorated
{
    public:
        Discounted(int arg, unique_ptr<Item> argItem) : Decorated{move(argItem)}, discount{arg} {}
        int price() { return getItem().price() - discount; }

        int discount;
};

int main()
{
    unique_ptr<Item> discountedBook = make_unique<Discounted>(10, make_unique<Book>(150));
    std::cout << discountedBook->price();

    return 0;
}
