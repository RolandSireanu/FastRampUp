#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Clock.hpp>
#include <logger.h>
#include <CircleElement.hpp>
#include <GenerateRandomNumbers.hpp>
#include <Constants.hpp>
#include <string>

class Window{
    public:
        Window();
        Window(const std::string& l_title,const sf::Vector2u& l_size);
        ~Window();
        void BeginDraw(); // Clear the window.
        void EndDraw(); // Display the changes.
        void Update();
        bool IsDone();
        bool IsFullscreen();
        sf::Vector2u GetWindowSize();
        void Draw(sf::Drawable& l_drawable);
    private:
        void Setup(const std::string& l_title, const sf::Vector2u& l_size);
        void Destroy();
        sf::RenderWindow m_window;
        sf::Vector2u m_windowSize;
        const sf::Vector2u m_defaultWindowSize {400, 400};
        std::string m_windowTitle;
        bool m_isDone;
        bool m_isFullscreen;
};

#endif