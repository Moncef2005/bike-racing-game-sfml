#include "About.hpp"
#include "Constants.hpp"
#include <iostream>

About::About(sf::RenderWindow& window) : mWindow(window) {
    if (!mFont.loadFromFile("assets/fonts/Anton-Regular.ttf")) {
        throw std::runtime_error("Failed to load about font");
    }

    mTitle.setFont(mFont);
    mTitle.setString("A PROPOS");
    mTitle.setCharacterSize(50);
    mTitle.setFillColor(sf::Color::Yellow);
    mTitle.setPosition(
        Constants::WINDOW_WIDTH/2 - mTitle.getGlobalBounds().width/2, 
        50
    );

    mInstructions.setFont(mFont);
    mInstructions.setString(
        "Instructions:\n"
        "- Utilisez les fleches gauche/droite pour vous deplacer\n"
        "- Espace pour sauter\n"
        "- Evitez les obstacles\n"
        "- Terminez le parcours en 60 secondes"
    );
    mInstructions.setCharacterSize(30);
    mInstructions.setFillColor(sf::Color::White);
    mInstructions.setPosition(50, 150);

    mQuitText.setFont(mFont);
    mQuitText.setString("Quitter\nAppuyez sur Echap pour revenir au menu");
    mQuitText.setCharacterSize(24);
    mQuitText.setFillColor(sf::Color::White);
    mQuitText.setPosition(
        Constants::WINDOW_WIDTH/2 - mQuitText.getGlobalBounds().width/2,
        Constants::WINDOW_HEIGHT - 100
    );
}

void About::draw() {
    mWindow.clear();
    mWindow.draw(mTitle);
    mWindow.draw(mInstructions);
    mWindow.draw(mQuitText);
    mWindow.display();
}

bool About::handleInput() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed || 
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            return true;
        }
    }
    return false;
}