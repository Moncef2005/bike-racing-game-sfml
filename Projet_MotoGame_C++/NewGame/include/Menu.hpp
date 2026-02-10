#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void draw();
    int handleInput();
    void update();
    int getSelectedItem() const { return mSelectedItemIndex; }

private:
    sf::RenderWindow& mWindow;
    sf::Font mFont;
    std::vector<sf::Text> mMenuItems;
    int mSelectedItemIndex;
    sf::Text mTitle;
};