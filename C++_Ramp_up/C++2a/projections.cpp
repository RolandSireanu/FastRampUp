#include <vector>
#include <iostream>
#include <algorithm>

class Player {
public:
  Player(std::string Name) : Name(Name) {};
  std::string GetName() const { return Name; }

private:
  std::string Name;
};

int main() 
{
    using std::string, std::cout;
    {
        std::vector Party {
            Player{"Legolas"},
            Player{"Gimli"},
            Player{"Gandalf"}
        };

        std::ranges::sort(Party, {}, &Player::GetName);

        for (const auto& P : Party) 
        {
            std::cout << P.GetName() << '\n';
        }
    }

    {
        std::vector Party {
            Player{"Legolas"},
            Player{"Gimli"},
            Player{"Gandalf"}
        };

        std::ranges::sort(Party, {}, [](const Player& p){ return p.GetName();});

        for (const auto& P : Party) 
        {
            std::cout << P.GetName() << '\n';
        }
    }
        cout << "Soring based on name length : \n";
        {
        std::vector Party {
            Player{"Legolas"},
            Player{"Gimli"},
            Player{"Gandalf"}
        };

        std::ranges::sort(Party, [](const string& argL, const string& argR)
                                   { return argL.size() < argR.size(); }, 
                                [](const Player& p)
                                   { return p.GetName();});

        for (const auto& P : Party) 
        {
            std::cout << P.GetName() << '\n';
        }
    }

}