#include <iostream>
#include <string>
#include <exception>
using namespace std;

class Car {
    
    public:
        //Compiler will initialize members in the order they appear in class declaration
        //not in initialize_list , (nrOfDors first , model after)
        Car() : nrOfDoors{0}, model{"Default model"} 
        {
            cout << "Default constructor " << endl;
            if(nrOfDoors > 5){
                //Constructor can't return value so the only way it can signal a 
                // problem is by throwing an exception 
                throw runtime_error{"Nr of doors can't be bigger then 5 "};
            }
        }

        //If it would be "explicit" , it couldn't be used as conversion constructor in 
        //copy initialization 
        Car(const char arg[]) {
            cout << "Conversion constructor from char[] to Car" << endl;
        }

        Car(const Car& arg) { cout << "Copy constructor ! " <<endl; }

        Car& operator=(const Car& arg) { cout << "Copy asigment operator " << endl; }

        Car(initializer_list<int> arg) {
            cout << "Conversion constructor with initializer list " << endl;
        }

    private:
        int nrOfDoors;
        string model;
};

int main()
{   
    Car c;              //Default constructor
    Car c2 = "Dacia";   //Copy initialiation , conversion constructor from string to Car called
    Car c3 = c2;
    Car c4(c2);
    c = "Renault";      //Conversion constructor from char[] to C -> Copy asigment operator
    c = {1,3,4};        //Conversion constructor from initializer list -> Copy asigment operator

    return 0;
}