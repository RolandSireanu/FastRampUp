

#include <Window.h>


void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size)
{
    m_windowSize = l_size;
    m_windowTitle = l_title;
    m_isFullscreen = false;
    m_isDone = false;
    m_window.create(sf::VideoMode(l_size.x, l_size.y), l_title);
    m_window.setFramerateLimit(60);
}

void Window::Destroy()
{
    m_window.close();
}

Window::Window()
{
    Setup("Game window", m_defaultWindowSize);
}

Window::Window(const std::string& l_title,const sf::Vector2u& l_size)
{
    Setup(l_title, l_size);
}

void Window::BeginDraw()
{
    m_window.clear(sf::Color::Black);
}

void Window::EndDraw()
{
    m_window.display();
}

bool Window::IsDone()
{
    return m_isDone;
}

bool Window::IsFullscreen()
{
    return m_isFullscreen;
}

void Window::Update()
{
        sf::Event event;
        while(m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
               m_isDone = true;
        }
}

void Window::Draw(sf::Drawable& l_drawable)
{
    m_window.draw(l_drawable);
}

Window::~Window()
{
    m_window.close();
}

sf::Vector2u Window::GetWindowSize()
{
    return m_windowSize;
}