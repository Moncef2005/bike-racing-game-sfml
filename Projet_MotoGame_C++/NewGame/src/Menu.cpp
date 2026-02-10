#include "Menu.hpp"
#include "Constants.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow& window) : 
    mWindow(window), 
    mSelectedItemIndex(0) 
{
    if (!mFont.loadFromFile("assets/fonts/Anton-Regular.ttf")) {
        throw std::runtime_error("Failed to load menu font");
    }

    mTitle.setFont(mFont);
    mTitle.setString("MOTO GAME");
    mTitle.setCharacterSize(60);
    mTitle.setFillColor(sf::Color::Red);
    mTitle.setPosition(
        Constants::WINDOW_WIDTH/2 - mTitle.getGlobalBounds().width/2, 
        100
    );

    std::vector<std::string> items = {"Jouer", "Scores", "A Propos", "Quitter"};
    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text item;
        item.setFont(mFont);
        item.setString(items[i]);
        item.setCharacterSize(40);
        item.setPosition(
            Constants::WINDOW_WIDTH/2 - item.getGlobalBounds().width/2, 
            250 + i*80
        );
        mMenuItems.push_back(item);
    }
    mMenuItems[mSelectedItemIndex].setFillColor(sf::Color::Red);
}

int Menu::handleInput() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            return 3;
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                mMenuItems[mSelectedItemIndex].setFillColor(sf::Color::White);
                mSelectedItemIndex = (mSelectedItemIndex - 1 + mMenuItems.size()) % mMenuItems.size();
                mMenuItems[mSelectedItemIndex].setFillColor(sf::Color::Red);
            }
            else if (event.key.code == sf::Keyboard::Down) {
                mMenuItems[mSelectedItemIndex].setFillColor(sf::Color::White);
                mSelectedItemIndex = (mSelectedItemIndex + 1) % mMenuItems.size();
                mMenuItems[mSelectedItemIndex].setFillColor(sf::Color::Red);
            }
            else if (event.key.code == sf::Keyboard::Return) {
                return mSelectedItemIndex;
            }
        }
    }
    return -1;
}

void Menu::draw() {
    mWindow.clear();
    mWindow.draw(mTitle);
    for (const auto& item : mMenuItems) {
        mWindow.draw(item);
    }
    mWindow.display();
}

void Menu::update() {
    // Peut être utilisé pour des animations
}