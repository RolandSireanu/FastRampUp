#ifndef CIRCLE_ELEMENT_H
#define CIRCLE_ELEMENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class CircleElement : public sf::Drawable, public sf::Transformable
{
    public:

        CircleElement();
        CircleElement(sf::Vector2f, float, float arg_speed = 5.0f);
        // CircleElement(const CircleElement&) = default;
        // CircleElement(CircleElement&&) = default;
        // CircleElement& operator=(const CircleElement&) = default;
        // CircleElement& operator=(CircleElement&&) = default;

        void moveXAxis(float distance = 1.0f);
        void moveYAxis();
        void increaseRadius(float newRadius = 1.0f);
        void setPos(float arg_x, float arg_y);
        sf::Vector2f getPos() const;
        float getRad() const;
        void changeColor(const sf::Color& color);

        bool overflows(const CircleElement& arg_circle) const;

    private:
        sf::CircleShape m_circle;
        sf::Color m_color = sf::Color::Green;
        const float m_default_radius = 10.0f;
        const float m_default_x = 0.0f;
        const float m_default_y = 0.0f;
        float m_defaultSpeedY = 5.0f;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


#endif