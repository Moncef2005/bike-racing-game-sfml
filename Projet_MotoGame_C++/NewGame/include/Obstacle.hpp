#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
public:
    Obstacle();
    
    void update(float speed);
    void draw(sf::RenderWindow& window) const;
    void setPosition(float x, float y);
    void setHeight(float height);
    sf::Vector2f getPosition() const;  // Added this line
    sf::FloatRect getGlobalBounds() const;
    float getWidth() const;
    float getHeight() const;
    
private:
    sf::RectangleShape mShape;
    static const float WIDTH;
    static const float HEIGHT ; // Default height
};