
#include "CircleElement.hpp"
#include <iostream>

CircleElement::CircleElement()
{
    m_circle.setRadius(m_default_radius);
    m_circle.setFillColor(m_color);
    m_circle.setPosition(sf::Vector2f(m_default_x, m_default_y));
}

CircleElement::CircleElement(sf::Vector2f arg_pos, float arg_radius, float arg_speed)
{
    m_circle.setRadius(arg_radius);    
    m_circle.setFillColor(m_color);
    m_circle.setPosition(arg_pos);
    m_defaultSpeedY = arg_speed;
}


void CircleElement::moveXAxis(float distance)
{
    sf::Vector2f temp = m_circle.getPosition();
    temp.x += distance;
    m_circle.setPosition(temp);
}

void CircleElement::moveYAxis()
{
    sf::Vector2f temp = m_circle.getPosition();
    temp.y += m_defaultSpeedY;
    m_circle.setPosition(temp);
}

void CircleElement::increaseRadius(float newRadius)
{
    float temp_radius = m_circle.getRadius();
    temp_radius += newRadius;
    m_circle.setRadius(temp_radius);
}

void CircleElement::changeColor(const sf::Color& color)
{
    this->m_color = color;
}

void CircleElement::setPos(float arg_x, float arg_y)
{
    m_circle.setPosition(sf::Vector2f(arg_x, arg_y));
}

float CircleElement::getRad() const
{
    return m_circle.getRadius();
}

sf::Vector2f CircleElement::getPos() const
{
    return m_circle.getPosition();
}

void CircleElement::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_circle);
}

bool CircleElement::overflows(const CircleElement& arg_circle) const
{
    float startX = m_circle.getPosition().x;
    float endX = startX + (m_circle.getRadius() * 2);
    float startX_temp = arg_circle.getPos().x;
    float endX_temp = (arg_circle.getPos().x + arg_circle.getRad()*2);
    
    printf("%f >= %f && %f <= %f",endX_temp, startX, endX_temp, endX);
    if(endX_temp >= startX && endX_temp <= endX)
    {
        std::cout << " Return overflow true \n";
        return true;
    }
    
    printf("%f >= %f && %f <= %f",startX_temp, startX, startX_temp, endX);
    if(startX_temp >= startX && startX_temp <= endX)
    {
        std::cout << " Return overflow true \n";
        return true;
    }
    
    printf("%f >= %f && %f <= %f",startX_temp, startX, endX_temp, endX);
    if(startX_temp <= startX && endX_temp >= endX)
    {
        std::cout << " Return overflow true \n";
        return true;
    }

    std::cout << "Good circle startX = " << startX << " endX = " << endX << " startX_temp = "<< startX_temp << " endX_temp = " << endX_temp << std::endl;

    return false;
}