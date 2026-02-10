#include "Obstacle.hpp"
#include "Constants.hpp"

const float Obstacle::WIDTH = 50.f;
const float Obstacle::HEIGHT = 50.f;


Obstacle::Obstacle() {
    mShape.setSize(sf::Vector2f(WIDTH, HEIGHT));
    mShape.setFillColor(sf::Color::Red);
}

void Obstacle::update(float speed) {
    mShape.move(-speed, 0);
}

void Obstacle::draw(sf::RenderWindow& window) const {
    window.draw(mShape);
}

void Obstacle::setPosition(float x, float y) {
    mShape.setPosition(x, y);
}

sf::Vector2f Obstacle::getPosition() const {  // Added this method
    return mShape.getPosition();
}

sf::FloatRect Obstacle::getGlobalBounds() const {
    return mShape.getGlobalBounds();
}

float Obstacle::getWidth() const {
    return WIDTH;
}

float Obstacle::getHeight() const {
    return HEIGHT;
}