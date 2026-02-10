#pragma once
#include <SFML/Graphics.hpp>

class About {
public:
    About(sf::RenderWindow& window);
    void draw();
    bool handleInput();

private:
    sf::RenderWindow& mWindow;
    sf::Font mFont;
    sf::Text mTitle;
    sf::Text mInstructions;
    sf::Text mQuitText;
};