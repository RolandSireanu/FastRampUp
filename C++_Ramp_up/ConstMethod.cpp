#include <iostream>
using namespace std;

class TestConst 
{
    public:

        //This method can't be called by const objects of TestConst because 
        //it doesn't guarantee that the object will not be change inside.
        int getMember() 
        {
            cout << "Non-const method called ! \n";
            return number;
        }

        //By marking const , you guarantee that the internal state of the object
        //will not be changed => also const objects can call this method. 
        int getMember() const 
        {
            cout << "Const method called ! \n"; 
            return number;
        }

    private:
        int number = 25;
};


int main()
{
    TestConst tc;
    const TestConst ctc;
    cout << tc.getMember() << endl;
    cout << ctc.getMember() << endl;

    return 0;
}
