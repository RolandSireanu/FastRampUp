#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "CircleElement.hpp"
#include <optional>
#include "Inputs.hpp"
#include <vector>

class Game
{
    public:
        Game() : m_window("Game window", {800, 600}) 
        {
            m_circles.reserve(16);
        }
        ~Game();
        void HandleInput();
        void Update();
        void Render();
        
        Window& GetWindow();
    private:
        Window m_window;
        CircleElement m_circle;
        std::vector<CircleElement> m_circles;
        const unsigned int MAX_CIRCLES_ON_BOARD = 4;

        void UpdateNumberOfCircles(unsigned int max_nr_of_circles);
        void MoveCircles();
        


};


#endif