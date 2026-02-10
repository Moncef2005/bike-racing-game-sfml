// Scores.cpp
#include "Scores.hpp"
#include "Constants.hpp"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

Scores::Scores(sf::RenderWindow& window) : mWindow(window) {
    if (!mFont.loadFromFile("assets/fonts/Anton-Regular.ttf")) {
        throw std::runtime_error("Failed to load scores font");
    }

    mTitle.setFont(mFont);
    mTitle.setString("MEILLEURS SCORES");
    mTitle.setCharacterSize(50);
    mTitle.setFillColor(sf::Color::Yellow);
    mTitle.setPosition(Constants::WINDOW_WIDTH/2 - mTitle.getGlobalBounds().width/2, 50);

    mBackText.setFont(mFont);
    mBackText.setString("Retour (Echap)");
    mBackText.setCharacterSize(24);
    mBackText.setPosition(20, Constants::WINDOW_HEIGHT - 50);

    loadScores();
}

void Scores::draw() {
    mWindow.clear();
    mWindow.draw(mTitle);
    mWindow.draw(mBackText);
    
    for (const auto& item : mScoreItems) {
        mWindow.draw(item);
    }
    
    mWindow.display();
}

bool Scores::handleInput() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed || 
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            return true;
        }
    }
    return false;
}

void Scores::loadScores() {
    mScores.clear();
    mScoreItems.clear();
    
    // Charger depuis un fichier (simplifié ici)
    // En réalité, vous devriez lire depuis un fichier
    mScores = { 120.5f, 115.2f, 98.7f, 85.3f, 72.1f }; // Exemple
    
    // Trier par ordre décroissant
    std::sort(mScores.rbegin(), mScores.rend());
    
    // Créer les éléments d'affichage
    for (size_t i = 0; i < mScores.size() && i < 5; ++i) {
        sf::Text item;
        item.setFont(mFont);
        
        std::stringstream ss;
        ss << i+1 << ". " << std::fixed << std::setprecision(1) << mScores[i] << " sec";
        
        item.setString(ss.str());
        item.setCharacterSize(30);
        item.setPosition(Constants::WINDOW_WIDTH/2 - 100, 150 + i*50);
        mScoreItems.push_back(item);
    }
}

void Scores::addScore(float elapsedTime) {
    mScores.push_back(elapsedTime);
    // Sauvegarder dans un fichier
    loadScores(); // Recharger pour trier et afficher
}