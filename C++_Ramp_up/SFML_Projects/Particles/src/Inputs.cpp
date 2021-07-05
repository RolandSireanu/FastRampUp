#include <Inputs.hpp>
#include <vector>
#include <thread>
#include <queue>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace Inputs
{

    std::optional<Inputs::MouseClickEv> getMouseClick()
    {
        MouseClickEv tempEv;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            
            sf::Vector2i p = sf::Mouse::getPosition();
            tempEv.x = p.x;
            tempEv.y = p.y;
            tempEv.leftClick = true;  
            return std::optional<Inputs::MouseClickEv>{tempEv};  
        }
        else
        {
            sf::Vector2i p = sf::Mouse::getPosition();
            tempEv.x = p.x;
            tempEv.y = p.y;
            tempEv.leftClick = true;                    
            return std::optional<Inputs::MouseClickEv>{tempEv};  
        }

        return std::optional<Inputs::MouseClickEv>{};
        // std::cout << "Ev q size : " << eventsQ.size() << std::endl;
        // if(eventsQ.size() > 0)
        // {
        //     Inputs::MouseClickEv temp = eventsQ.front();
        //     std::lock_guard<std::mutex> guard(myMutex);
        //     eventsQ.pop();
        //     return std::optional<Inputs::MouseClickEv>(temp);
        // }
        // else
        // {
            // return std::optional<Inputs::MouseClickEv>{};
        // }

    }

};