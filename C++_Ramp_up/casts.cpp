#include <cstdio>
#include <iostream>
#include <optional>
#include <span>
using namespace std;

// Reinterpret_cast doesn't do any checks, just reinterpret the memory as the new type

// Dynamic cast works only on polimorphic types
// Used in casts during class hierarchies
// Check the RTTI information to make sure types are compatible

class Entity 
{
public:
    virtual void f() {}
};
class Player : public Entity{};
class Enemy : public Entity{};



int main()
{
    Entity* entity = new Player();

    // Check the RTTI vrom vtable pointed by entity pointer
    //      if typename is compatible with enemy than makes the cast
    //      otherwise returns null
    // If entity points to entity or Enemy than enemy != NULL
    // Otherwise enemy == NULL
    Enemy* enemy = reinterpret_cast<Enemy*>(entity);
    if(enemy != NULL)
    {
        std::cout << "Entity is not a Player type\n";
    }
    else
    {
        std::cout << "Cast failed, entity is a player type\n";
    }

    int a = static_cast<int>(32.3L);
    // int* p = static_cast<int*>(32.1f);  // Error

}

