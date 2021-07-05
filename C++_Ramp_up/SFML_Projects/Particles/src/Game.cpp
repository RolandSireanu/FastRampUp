#include <Game.hpp>
#include "GenerateRandomNumbers.hpp"

void Game::HandleInput()
{
    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    // {
    //     sf::Vector2i p = sf::Mouse::getPosition();
    //     std::cout << p.x << " , " << p.y << std::endl;
    // }
    std::optional<Inputs::MouseClickEv> mouseClick = Inputs::getMouseClick();
    if(mouseClick.has_value())
        std::cout << "Mouse click ev";
    
}

void Game::UpdateNumberOfCircles(unsigned int max_nr_of_circles)
{
    while(m_circles.size() < max_nr_of_circles)
    {
        bool exit = false;
        while(exit == false)
        {
            sf::Vector2f position((float)RandomNumbers::generate(0,m_window.GetWindowSize().x-60), 0.0f);
            float radius = (float)RandomNumbers::generate(10,30);
            float speed = (float)RandomNumbers::generate(1,5);
            // std::cout << "position : " << position.x << " radius : " << radius << std::endl;
            bool circleOk = true;
            for(const auto& circle : m_circles)
            {
                std::cout << "Check for overflow currentCicle.x = " << circle.getPos().x << " tempCircle.x = " << position.x << std::endl;
                if(circle.overflows(CircleElement(position, radius)) == true)
                {
                    std::cout << "Overflow ! \n";
                    circleOk = false;
                    break;
                }
                else
                {
                    std::cout << "Not Overflow ! \n";
                }
            }
            if(circleOk == true)
            {
                m_circles.emplace_back(position, radius, speed);
                std::cout << "Circle added  position.x = " << position.x << " position.y = " << position.y << " radius = "<< radius << std::endl;
                exit = true;
            }
                
        }
    }  
}

void Game::MoveCircles()
{
    for(CircleElement& circle : m_circles)
    {
        circle.moveYAxis();
    }
}

void Game::Update()
{
    m_window.Update();
    if(m_circles.size() < MAX_CIRCLES_ON_BOARD)
    {
        UpdateNumberOfCircles(MAX_CIRCLES_ON_BOARD);
    }

    MoveCircles();

}

void Game::Render()
{
    m_window.BeginDraw();
    for(auto& circle : m_circles)
    {
        m_window.Draw(circle);
    }
    m_window.EndDraw();
}

Window& Game::GetWindow()
{
    return m_window;
}

Game::~Game()
{
    
}