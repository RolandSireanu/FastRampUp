#include "Game.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <vector>
#include <memory>
#include <SFML/System.hpp>
#include <Inputs.hpp>
#ifdef EnableTests
    #include<gtest/gtest.h>
#endif
using namespace std;

int main(int ac, char** av)
{
    #ifdef EnableTests
        testing::InitGoogleTest(&ac, av);
        return RUN_ALL_TESTS();
    #else

        Game game;
        sf::Clock clock;

        while(game.GetWindow().IsDone() == false)
        {
            clock.restart();    
            game.HandleInput();

            sf::Time elapsed = clock.getElapsedTime();
            cout << " Duration HandleInput : " << elapsed.asMilliseconds() << "us\n";
            clock.restart();

            game.Update();
            elapsed = clock.getElapsedTime();
            cout << " Duration Update : " << elapsed.asMilliseconds() << "us\n";
            clock.restart();

            game.Render();
            elapsed = clock.getElapsedTime();
            cout << " Duration Render : " << elapsed.asMilliseconds() << "us\n";

        }
    #endif



//     sf::RenderWindow window(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "SFML works!");
    
//     // CircleElement circle;
//     // std::vector<CircleElement> circles(10); 
//     // sf::Clock clock;
//     // sf::RenderTexture texture;

//     // if(!texture.create(Constants::WINDOW_WIDTH,Constants::WINDOW_HEIGHT))
//     //     return -1;
    
    
//     // LOG::smart_stream s(std::cout);
//     // s << "Window has been created ! \n";

//     // unsigned int even = 0;
//     while (window.isOpen())
//     {    
//     //     clock.restart();
//     //     circles.emplace_back();
//     //     CircleElement& refCircle = circles.back();
//     //     float newX = static_cast<float>(RandomNumbers::generate(0, Constants::WINDOW_WIDTH));
//     //     float newY = static_cast<float>(RandomNumbers::generate(0, Constants::WINDOW_HEIGHT));
//     //     refCircle.setPos(newX, newY);
//     //     refCircle.increaseRadius(10.0f);
        
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         texture.clear(sf::Color::Black);
        

//     //     std::cout << "Number of circles : " << circles.size() << "\n";
        
//     //     for(CircleElement& c : circles)
//     //     {
//     //         if(even % 2 == 0)
//     //             c.moveXAxis(25.0f);
//     //         else
//     //             c.moveXAxis(-25.0f);
//     //         // window.draw(c);
//     //         texture.draw(c);
//     //     }
        
//     //     texture.display();
//     //     window.clear();

//     //     sf::Sprite sprite(texture.getTexture());
//     //     window.draw(sprite);
//     //     window.display();
//     //     even ++;
//     //     sf::sleep(sf::milliseconds(10));
//     //     sf::Int64 timeAsMili = clock.getElapsedTime().asMilliseconds();
//     //     std::cout << "Framerate : " << 1000 / timeAsMili << " fps\n";
//   //  }

    return 0;
}
